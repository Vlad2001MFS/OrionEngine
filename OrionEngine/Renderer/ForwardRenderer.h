#pragma once
#include "../Window/RenderWindow.h"
#include "../Graphics/Graphics.h"
#include "Light.h"
#include "StaticMesh.h"

namespace oe {

class ForwardRenderer {
public:
    ForwardRenderer(RenderWindow *window, Graphics *graphics);
    ~ForwardRenderer();

    void Begin(const glm::mat4 &viewProjMat, const glm::vec3 &camPos, const Light *lights, uint lightsCount);
    void Draw(const StaticMesh *mesh, const glm::mat4 &worldMat);
    void End();

private:
    struct RenderOp {
        glm::mat4 worldMat;
        const StaticMesh *staticMesh;
    };

    RenderWindow *mWindow;
    Graphics *mGraphics;
    SamplerState *mSamplerState;
    ConstantBuffer *mLightConstantBuffer, *mMaterialConstantBuffer;
    Program *mStaticMeshProgram;
    VertexFormat *mStaticMeshVertexFormat;
    ConstantID mStaticMeshProgramViewProjMatID, mStaticMeshProgramCamPosID, mStaticMeshProgramWorldMatID, mStaticMeshProgramLightsCountID;

    static const uint mMaxLights = 32;
    std::vector<RenderOp> mRenderOps;
    glm::mat4 mViewProjMat;
    glm::vec3 mCamPos;
    Light mLights[mMaxLights];
    int mLightsCount;
};

}