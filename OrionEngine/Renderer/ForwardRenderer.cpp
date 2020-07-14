#include "ForwardRenderer.h"
#include "../Core/Debug.h"
#include "../Core/StringUtils.h"

namespace oe {

const char *gStaticMeshVS = R"(
#version 430 core

layout(location = 0) in vec3 vsPosition;
layout(location = 1) in vec3 vsNormal;
layout(location = 2) in vec2 vsTexCoord;

out vec3 psPosition;
out vec3 psNormal;
out vec2 psTexCoord;

uniform mat4 gViewProjMat, gWorldMat;

void main() {
    psPosition = vec3(gWorldMat*vec4(vsPosition, 1.0));
    gl_Position = gViewProjMat*vec4(psPosition, 1.0);
    psNormal = normalize(gWorldMat*vec4(vsNormal, 0.0)).xyz;
    psTexCoord = vsTexCoord;
}
)";

const char *gStaticMeshPS = R"(
#version 430 core
in vec3 psPosition;
in vec3 psNormal;
in vec2 psTexCoord;

out vec4 psResult;

struct Light {
    vec3 position, direction;
    vec3 ambient, diffuse, specular;
    vec3 attenuation; // not used for dir light
    vec2 spotAngles; // not used for dir light
    int type;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float specPower;
};

layout(std140, binding = 0) uniform LightBlock {
    Light gLights[MAX_LIGHTS];
};

layout(std140, binding = 1) uniform MaterialBlock {
    Material gMaterial;
};

uniform int gLightsCount;
uniform vec3 gCamPos;
layout(binding = 0) uniform sampler2D gDiffuseMap;
layout(binding = 1) uniform sampler2D gSpecularMap;

vec3 CalcDirLight(in int i) {
    vec3 toLightDir = normalize(-gLights[i].direction);
    vec3 fromCamToPixel = normalize(psPosition - gCamPos);
    vec3 ambient = gMaterial.ambient*gLights[i].ambient;
    vec3 diffuse = gMaterial.diffuse*gLights[i].diffuse*max(0.0, dot(psNormal, toLightDir));
    vec3 specular = gMaterial.specular*gLights[i].specular*pow(max(0.0, dot(fromCamToPixel, reflect(-fromCamToPixel, psNormal))), gMaterial.specPower)*texture(gSpecularMap, psTexCoord).xyz;
    return ambient + diffuse + specular;
}

vec3 CalcPointLight(in int i) {
    vec3 toLightDir = normalize(gLights[i].position - psPosition);
    vec3 fromCamToPixel = normalize(psPosition - gCamPos);
    vec3 ambient = gMaterial.ambient*gLights[i].ambient;
    vec3 diffuse = gMaterial.diffuse*gLights[i].diffuse*max(0.0, dot(psNormal, toLightDir));
    vec3 specular = gMaterial.specular*gLights[i].specular*pow(max(0.0, dot(fromCamToPixel, reflect(-fromCamToPixel, psNormal))), gMaterial.specPower)*texture(gSpecularMap, psTexCoord).xyz;
    float dist = distance(gLights[i].position, psPosition);
    float attenuation = 1.0 / (gLights[i].attenuation.x + gLights[i].attenuation.y*dist + gLights[i].attenuation.z*dist*dist);
    return ambient + attenuation*(diffuse + specular);
}

vec3 CalcSpotLight(in int i) {
    vec3 toLightDir = normalize(gLights[i].position - psPosition);
    vec3 fromCamToPixel = normalize(psPosition - gCamPos);
    vec3 ambient = gMaterial.ambient*gLights[i].ambient;
    vec3 diffuse = gMaterial.diffuse*gLights[i].diffuse*max(0.0, dot(psNormal, toLightDir));
    vec3 specular = gMaterial.specular*gLights[i].specular*pow(max(0.0, dot(fromCamToPixel, reflect(-fromCamToPixel, psNormal))), gMaterial.specPower)*texture(gSpecularMap, psTexCoord).xyz;
    float dist = distance(gLights[i].position, psPosition);
    float attenuation = 1.0 / (gLights[i].attenuation.x + gLights[i].attenuation.y*dist + gLights[i].attenuation.z*dist*dist);
    float theta = dot(-toLightDir, normalize(gLights[i].direction));
	//float cosCutOff = cos(gLights[i].spotAngles.x);
	//float cosOuterCutOff = cos(gLights[i].spotAngles.y);
    vec2 cosSpotAngles = cos(gLights[i].spotAngles);
	float epsilon = cosSpotAngles.x - cosSpotAngles.y;
	float intensity = clamp((theta - cosSpotAngles.y)/epsilon, 0.0, 1.0);    
    return ambient + intensity*attenuation*(diffuse + specular);
}

void main() {
    vec3 lightResult = vec3(0, 0, 0);
    for (int i = 0; i < gLightsCount; i++) {
        switch (gLights[i].type) {
            case DIR_LIGHT:
                lightResult += CalcDirLight(i);
                break;
            case POINT_LIGHT:
                lightResult += CalcPointLight(i);
                break;
            case SPOT_LIGHT:
                lightResult += CalcSpotLight(i);
                break;
        }
    }
    psResult = vec4(lightResult, 1.0)*texture(gDiffuseMap, psTexCoord);
}
)";

ForwardRenderer::ForwardRenderer(RenderWindow * window, Graphics * graphics) : mWindow(window), mGraphics(graphics) {
    mSamplerState = new SamplerState(SamplerFilter::Anisotropic, 16);
    mLightConstantBuffer = new ConstantBuffer(nullptr, sizeof(Light)*mMaxLights, true);
    mMaterialConstantBuffer = new ConstantBuffer(nullptr, sizeof(Material), true);
    std::string defs = "";
    defs += StringUtils::Format("MAX_LIGHTS %d;", mMaxLights);
    defs += StringUtils::Format("DIR_LIGHT %d;", LightType::Dir);
    defs += StringUtils::Format("POINT_LIGHT %d;", LightType::Point);
    defs += StringUtils::Format("SPOT_LIGHT %d", LightType::Spot);
    mStaticMeshProgram = new Program(gStaticMeshVS, gStaticMeshPS, defs);
    mStaticMeshProgramViewProjMatID = mStaticMeshProgram->GetConstantID("gViewProjMat");
    mStaticMeshProgramWorldMatID = mStaticMeshProgram->GetConstantID("gWorldMat");
    mStaticMeshProgramCamPosID = mStaticMeshProgram->GetConstantID("gCamPos");
    mStaticMeshProgramLightsCountID = mStaticMeshProgram->GetConstantID("gLightsCount");
    mStaticMeshVertexFormat = new VertexFormat({
        VertexAttrib(0, 0, 0, AttribType::Float3, false, 0),
        VertexAttrib(0, 1, 12, AttribType::Float3, false, 0),
        VertexAttrib(0, 2, 24, AttribType::Float2, false, 0)
    });
}

ForwardRenderer::~ForwardRenderer() {
    OE_SAFE_DELETE(mStaticMeshVertexFormat);
    OE_SAFE_DELETE(mStaticMeshProgram);
    OE_SAFE_DELETE(mMaterialConstantBuffer);
    OE_SAFE_DELETE(mLightConstantBuffer);
    OE_SAFE_DELETE(mSamplerState);
}

void ForwardRenderer::Begin(const glm::mat4 & viewProjMat, const glm::vec3 & camPos, const Light * lights, uint lightsCount) {
    mViewProjMat = viewProjMat;
    mCamPos = camPos;
    if (lightsCount > mMaxLights) {
        OE_LOG_ERROR("Light sources count can't be greater than %d", mMaxLights);
    }
    else {
        memcpy(mLights, lights, sizeof(Light)*lightsCount);
        mLightsCount = lightsCount;
    }
    mRenderOps.clear();
}

void ForwardRenderer::Draw(const StaticMesh * mesh, const glm::mat4 & worldMat) {
    RenderOp rop;
    rop.staticMesh = mesh;
    rop.worldMat = worldMat;
    mRenderOps.push_back(rop);
}

void ForwardRenderer::End() {
    mGraphics->SetSamplerState(mSamplerState, 0);
    mGraphics->SetSamplerState(mSamplerState, 1);

    mGraphics->SetDepthState(true, CompareFunc::Less, true);
    mGraphics->SetRasterizerState(CullFace::Back, FillMode::Solid, FrontFace::CCW, PolygonOffset());
    mGraphics->SetBlendState(BlendMode::Replace, ColorMask(true));

    mGraphics->SetVertexFormat(mStaticMeshVertexFormat);
    mGraphics->SetProgram(mStaticMeshProgram);
    mGraphics->SetConstant(mStaticMeshProgramViewProjMatID, mViewProjMat);
    mGraphics->SetConstant(mStaticMeshProgramCamPosID, mCamPos);
    mGraphics->SetConstant(mStaticMeshProgramLightsCountID, mLightsCount);
    mGraphics->SetConstantBuffer(mLightConstantBuffer, 0);
    mGraphics->SetConstantBuffer(mMaterialConstantBuffer, 1);
    mLightConstantBuffer->SetData(mLights);
    for (const auto &rop : mRenderOps) {
        mGraphics->SetConstant(mStaticMeshProgramWorldMatID, rop.worldMat);
        for (const auto &subMesh : rop.staticMesh->GetSubMeshes()) {
            mMaterialConstantBuffer->SetData(&subMesh->GetMaterial());
            mGraphics->SetVertexBuffer(subMesh->GetVertexBuffer(), 0, 0, sizeof(StaticVertex));
            mGraphics->SetIndexBuffer(subMesh->GetIndexBuffer());
            mGraphics->SetTexture2D(subMesh->GetDiffuseMap(), 0);
            mGraphics->SetTexture2D(subMesh->GetSpecularMap(), 1);
            mGraphics->DrawIndexed(PrimitiveType::Triangles, subMesh->GetIndices().size(), 0, IndexType::Uint);
        }
    }
}

}
