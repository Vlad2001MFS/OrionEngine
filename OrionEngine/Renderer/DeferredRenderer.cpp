#include "DeferredRenderer.h"

namespace oe {

/**** Geometry program for static mesh ****/

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
    psNormal = vec3(gWorldMat*vec4(vsNormal, 0.0));
    psTexCoord = vsTexCoord;
}
)";
const char *gStaticMeshPS = R"(
#version 430 core

in vec3 psPosition;
in vec3 psNormal;
in vec2 psTexCoord;

layout(location = 0) out vec3 psPositionMap;
layout(location = 1) out vec3 psNormalMap;
layout(location = 2) out vec3 psDiffuseMap;

uniform sampler2D gDiffuseMap;

void main() {
    psPositionMap = psPosition;
    psNormalMap = normalize(psNormal);
    psDiffuseMap = texture(gDiffuseMap, psTexCoord).xyz;
}
)";

/**** Output program for fullscreen quad ****/

const char *gOutputVS = R"(
#version 430 core

layout(location = 0) in vec3 vsPosition;
layout(location = 1) in vec2 vsTexCoord;

out vec2 psTexCoord;

void main() {
	gl_Position = vec4(vsPosition, 1.0);
    psTexCoord = vsTexCoord;
}
)";
const char *gOutputPS = R"(
#version 430 core

in vec2 psTexCoord;

out vec4 psResult;

layout(binding = 0) uniform sampler2D gPositionMap;
layout(binding = 1) uniform sampler2D gNormaMap;
layout(binding = 2) uniform sampler2D gDiffuseMap;
layout(binding = 3) uniform sampler2D gLightMap;

void main() {
    psResult = texture(gDiffuseMap, psTexCoord)*texture(gLightMap, psTexCoord);
}
)";

/**** Directional light program ****/

const char *gDirLightVS = R"(
#version 430 core

layout(location = 0) in vec3 vsPosition;
layout(location = 1) in vec2 vsTexCoord;

out vec2 psTexCoord;

void main() {
	gl_Position = vec4(vsPosition, 1.0);
    psTexCoord = vsTexCoord;
}
)";
const char *gDirLightPS = R"(
#version 430 core

in vec2 psTexCoord;

out vec4 psResult;

layout(std140, binding = 0) uniform Light {
    vec3 position, direction;
    vec3 ambient, diffuse, specular;
    vec3 attenuation; // not used for dir light
    vec2 spotAngles; // not used for dir light
    int type;
} gLight;

layout(binding = 0) uniform sampler2D gPositionMap;
layout(binding = 1) uniform sampler2D gNormalMap;
layout(binding = 2) uniform sampler2D gDiffuseMap;
uniform vec3 gCamPos;

void main() {
    vec3 position = texture(gPositionMap, psTexCoord).xyz;
    vec3 normal = texture(gNormalMap, psTexCoord).xyz;
    vec3 toLightDir = normalize(-gLight.direction);
    vec3 fromCamToPixel = normalize(position - gCamPos);
    vec3 ambient = gLight.ambient;
    vec3 diffuse = gLight.diffuse*max(0.0, dot(normal, -toLightDir));
    vec3 specular = gLight.specular*pow(max(0.0, dot(fromCamToPixel, reflect(-fromCamToPixel, normal))), 32);
    psResult = vec4(ambient + diffuse + specular, 1.0);
}
)";

/**** Point light program ****/

const char *gPointLightVS = R"(
#version 430 core

layout(location = 0) in vec3 vsPosition;
layout(location = 1) in vec2 vsTexCoord;

out vec2 psTexCoord;

void main() {
	gl_Position = vec4(vsPosition, 1.0);
    psTexCoord = vsTexCoord;
}
)";
const char *gPointLightPS = R"(
#version 430 core

in vec2 psTexCoord;

out vec4 psResult;

layout(std140, binding = 0) uniform Light {
    vec3 position, direction;
    vec3 ambient, diffuse, specular;
    vec3 attenuation;
    vec2 spotAngles; // not used for dir light
    int type;
} gLight;

layout(binding = 0) uniform sampler2D gPositionMap;
layout(binding = 1) uniform sampler2D gNormalMap;
layout(binding = 2) uniform sampler2D gDiffuseMap;
uniform vec3 gCamPos;

void main() {
    vec3 position = texture(gPositionMap, psTexCoord).xyz;
    vec3 normal = texture(gNormalMap, psTexCoord).xyz;
    vec3 toLightDir = normalize(gLight.position - position);
    vec3 fromCamToPixel = normalize(position - gCamPos);
    vec3 ambient = gLight.ambient;
    vec3 diffuse = gLight.diffuse*max(0.0, dot(normal, -toLightDir));
    vec3 specular = gLight.specular*pow(max(0.0, dot(fromCamToPixel, reflect(-fromCamToPixel, normal))), 32);
    float dist = distance(gLight.position, position);
    float attenuation = 1.0 / (gLight.attenuation.x + gLight.attenuation.y*dist + gLight.attenuation.z*dist*dist);
    psResult = vec4(ambient + attenuation*(diffuse + specular), 1.0);
}
)";

/**** Spot light program ****/

const char *gSpotLightVS = R"(
#version 430 core

layout(location = 0) in vec3 vsPosition;
layout(location = 1) in vec2 vsTexCoord;

out vec2 psTexCoord;

void main() {
	gl_Position = vec4(vsPosition, 1.0);
    psTexCoord = vsTexCoord;
}
)";
const char *gSpotLightPS = R"(
#version 430 core

in vec2 psTexCoord;

out vec4 psResult;

layout(std140, binding = 0) uniform Light {
    vec3 position, direction;
    vec3 ambient, diffuse, specular;
    vec3 attenuation;
    vec2 spotAngles;
    int type;
} gLight;

layout(binding = 0) uniform sampler2D gPositionMap;
layout(binding = 1) uniform sampler2D gNormalMap;
layout(binding = 2) uniform sampler2D gDiffuseMap;
uniform vec3 gCamPos;

void main() {
    vec3 position = texture(gPositionMap, psTexCoord).xyz;
    vec3 normal = texture(gNormalMap, psTexCoord).xyz;
    vec3 toLightDir = normalize(gLight.position - position);
    vec3 fromCamToPixel = normalize(position - gCamPos);
    vec3 ambient = gLight.ambient;
    vec3 diffuse = gLight.diffuse*max(0.0, dot(normal, -toLightDir));
    vec3 specular = gLight.specular*pow(max(0.0, dot(fromCamToPixel, reflect(-fromCamToPixel, normal))), 32);
    float dist = distance(gLight.position, position);
    float attenuation = 1 / (gLight.attenuation.x + gLight.attenuation.y*dist + gLight.attenuation.z*dist*dist);
    float theta = dot(-toLightDir, normalize(gLight.direction));
	//float cosCutOff = cos(gLight.spotAngles.x);
	//float cosOuterCutOff = cos(gLight.spotAngles.y);
    vec2 cosSpotAngles = cos(gLight.spotAngles);
	float epsilon = cosSpotAngles.x - cosSpotAngles.y;
	float intensity = clamp((theta - cosSpotAngles.y)/epsilon, 0.0, 1.0);    
    psResult = vec4(ambient + intensity*attenuation*(diffuse + specular), 1.0);
}
)";

DeferredRenderer::DeferredRenderer(RenderWindow *window, Graphics *graphics)
    : mWindow(window), mGraphics(graphics) {
    mGBuffer = new Framebuffer({
        FramebufferAttachment(mWindow->GetSize(), TextureFormat::RGB16),
        FramebufferAttachment(mWindow->GetSize(), TextureFormat::RGB16),
        FramebufferAttachment(mWindow->GetSize(), TextureFormat::RGB8),
        FramebufferAttachment(mWindow->GetSize(), TextureFormat::D24)
    });
    mLightMap = new Framebuffer({
        FramebufferAttachment(mWindow->GetSize(), TextureFormat::RGB8)
    });
    mSamplerState = new SamplerState(SamplerFilter::Anisotropic, 16);
    mFullscreenQuad = new FullscreenQuad(mGraphics);
    mGeometryPass = new GeometryPass(mGraphics);
    mLightPass = new LightPass(mGraphics, mFullscreenQuad);
    mOutputPass = new OutputPass(mGraphics, mFullscreenQuad);
}

DeferredRenderer::~DeferredRenderer() {
    OE_SAFE_DELETE(mOutputPass);
    OE_SAFE_DELETE(mLightPass);
    OE_SAFE_DELETE(mGeometryPass);
    OE_SAFE_DELETE(mFullscreenQuad);
    OE_SAFE_DELETE(mSamplerState);
    OE_SAFE_DELETE(mLightMap);
    OE_SAFE_DELETE(mGBuffer);
}

void DeferredRenderer::Begin(const glm::mat4 & viewProjMat, const glm::vec3 & camPos, const std::vector<Light> & lights) {
    mRenderOps.clear();
    mViewProjMat = viewProjMat;
    mCamPos = camPos;
    mLights = lights;
}

void DeferredRenderer::Draw(const StaticMesh * mesh, const glm::mat4 & worldMat) {
    RenderOp rop;
    rop.worldMat = worldMat;
    rop.staticMesh = mesh;
    mRenderOps.push_back(rop);
}

void DeferredRenderer::End() {
    mGraphics->SetSamplerState(mSamplerState, 0);
    mGraphics->SetSamplerState(mSamplerState, 1);
    mGraphics->SetSamplerState(mSamplerState, 2);

    mGeometryPass->Process(mGBuffer, mRenderOps, mViewProjMat);
    mLightPass->Process(mLightMap, mGBuffer, mLights, mCamPos);
    mOutputPass->Process(mGBuffer, mLightMap);
}

DeferredRenderer::FullscreenQuad::FullscreenQuad(Graphics * graphics) : graphics(graphics) { 
    vertexFormat = new VertexFormat({
        VertexAttrib(0, 0, 0, AttribType::Float3, false, 0),
        VertexAttrib(0, 1, 12, AttribType::Float2, false, 0)
        });
    const float quadVertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0, 0.0,
        1.0f,  1.0f, 0.0f, 1.0, 1.0,
        -1.0f,  1.0f, 0.0f, 0.0, 1.0,
        -1.0f, -1.0f, 0.0f, 0.0, 0.0,
        1.0f, -1.0f, 0.0f, 1.0, 0.0,
        1.0f,  1.0f, 0.0f, 1.0, 1.0
    };
    vertexBuffer = new VertexBuffer(quadVertices, sizeof(quadVertices), false);
}

DeferredRenderer::FullscreenQuad::~FullscreenQuad() {
    OE_SAFE_DELETE(vertexBuffer);
    OE_SAFE_DELETE(vertexFormat);
}

void DeferredRenderer::FullscreenQuad::Draw() {
    graphics->SetVertexFormat(vertexFormat);
    graphics->SetVertexBuffer(vertexBuffer, 0, 0, 20);
    graphics->Draw(PrimitiveType::Triangles, 6, 0);
}

DeferredRenderer::GeometryPass::GeometryPass(Graphics * graphics)
    : graphics(graphics), staticMeshVertexFormat(nullptr), staticMeshProgram(nullptr), staticMeshProgramViewProjMatID(-1), staticMeshProgramWorldMatID(-1) {
    staticMeshVertexFormat = new VertexFormat({
        VertexAttrib(0, 0, 0, AttribType::Float3, false, 0),
        VertexAttrib(0, 1, 12, AttribType::Float3, false, 0),
        VertexAttrib(0, 2, 24, AttribType::Float2, false, 0)
    });
    staticMeshProgram = new Program(gStaticMeshVS, gStaticMeshPS, "");
    staticMeshProgramViewProjMatID = staticMeshProgram->GetConstantID("gViewProjMat");
    staticMeshProgramWorldMatID = staticMeshProgram->GetConstantID("gWorldMat");
}

DeferredRenderer::GeometryPass::~GeometryPass() { 
    OE_SAFE_DELETE(staticMeshProgram);
    OE_SAFE_DELETE(staticMeshVertexFormat);
}

void DeferredRenderer::GeometryPass::Process(Framebuffer * gbuffer, const std::vector<RenderOp>& rops, const glm::mat4 & viewProjMat) {
    graphics->SetVertexFormat(staticMeshVertexFormat);
    graphics->SetFramebuffer(gbuffer);
    graphics->ClearColor(0, 0, 0, 1);
    graphics->ClearDepth(1.0f);

    graphics->SetDepthState(true, CompareFunc::Less, true);
    graphics->SetRasterizerState(CullFace::Back, FillMode::Solid, FrontFace::CCW, PolygonOffset());
    graphics->SetBlendState(BlendMode::Replace, ColorMask(true));

    graphics->SetProgram(staticMeshProgram);
    graphics->SetConstant(staticMeshProgramViewProjMatID, viewProjMat);
    for (auto &rop : rops) {
        graphics->SetConstant(staticMeshProgramWorldMatID, rop.worldMat);
        for (const auto &subMesh : rop.staticMesh->GetSubMeshes()) {
            graphics->SetVertexBuffer(subMesh->GetVertexBuffer(), 0, 0, sizeof(StaticVertex));
            graphics->SetIndexBuffer(subMesh->GetIndexBuffer());
            graphics->SetTexture2D(subMesh->GetDiffuseMap(), 0);
            graphics->DrawIndexed(PrimitiveType::Triangles, subMesh->GetIndices().size(), 0, IndexType::Uint);
        }
    }
}

DeferredRenderer::LightPass::LightPass(Graphics * graphics, FullscreenQuad * fullscreenQuad) : graphics(graphics), fullscreenQuad(fullscreenQuad) { 
    program[0] = new Program(gDirLightVS, gDirLightPS, "");
    programCamPosID[0] = program[0]->GetConstantID("gCamPos");
    program[1] = new Program(gPointLightVS, gPointLightPS, "");
    programCamPosID[1] = program[1]->GetConstantID("gCamPos");
    program[2] = new Program(gSpotLightVS, gSpotLightPS, "");
    programCamPosID[2] = program[2]->GetConstantID("gCamPos");
    lightConstantBuffer = new ConstantBuffer(nullptr, sizeof(Light), true);
}

DeferredRenderer::LightPass::~LightPass() {
    OE_SAFE_DELETE(lightConstantBuffer);
    OE_SAFE_DELETE(program[2]);
    OE_SAFE_DELETE(program[1]);
    OE_SAFE_DELETE(program[0]);
}

void DeferredRenderer::LightPass::Process(Framebuffer * lightMap, Framebuffer * gbuffer, const std::vector<Light>& lights, const glm::vec3 &camPos) {
    graphics->SetFramebuffer(lightMap);
    graphics->ClearColor(0, 0, 0, 1);

    graphics->SetDepthState(false, CompareFunc::Less, true);
    graphics->SetRasterizerState(CullFace::Back, FillMode::Solid, FrontFace::CCW, PolygonOffset());
    graphics->SetBlendState(BlendMode::Add, ColorMask(true));

    graphics->SetTexture2D(gbuffer->GetRenderTargets()[0], 0);
    graphics->SetTexture2D(gbuffer->GetRenderTargets()[1], 1);
    graphics->SetTexture2D(gbuffer->GetRenderTargets()[2], 2);

    graphics->SetConstantBuffer(lightConstantBuffer, 0);
    for (const auto &light : lights) {
        graphics->SetProgram(program[static_cast<uint>(light.type)]);
        graphics->SetConstant(programCamPosID[static_cast<uint>(light.type)], camPos);
        lightConstantBuffer->SetData(&light);
        fullscreenQuad->Draw();
    }
}

DeferredRenderer::OutputPass::OutputPass(Graphics * graphics, FullscreenQuad * fullscreenQuad) 
    : graphics(graphics), fullscreenQuad(fullscreenQuad), program(nullptr) {
    program = new Program(gOutputVS, gOutputPS, "");
}

DeferredRenderer::OutputPass::~OutputPass() { 
    OE_SAFE_DELETE(program);
}

void DeferredRenderer::OutputPass::Process(Framebuffer *gbuffer, Framebuffer *lightMap) {
    graphics->SetFramebuffer(nullptr);

    graphics->SetDepthState(false, CompareFunc::Less, true); 
    graphics->SetRasterizerState(CullFace::Back, FillMode::Solid, FrontFace::CCW, PolygonOffset());
    graphics->SetBlendState(BlendMode::Replace, ColorMask(true));

    graphics->SetProgram(program);
    graphics->SetTexture2D(gbuffer->GetRenderTargets()[2], 2);
    graphics->SetTexture2D(lightMap->GetRenderTargets()[0], 3);
    fullscreenQuad->Draw();
}

}