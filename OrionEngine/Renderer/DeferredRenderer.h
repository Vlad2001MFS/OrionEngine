#pragma once
#include "../Window/RenderWindow.h"
#include "../Graphics/Graphics.h"
#include "Light.h"
#include "StaticMesh.h"

namespace oe {

class DeferredRenderer {
public:
    DeferredRenderer(RenderWindow *window, Graphics *graphics);
    ~DeferredRenderer();

    void Begin(const glm::mat4 &viewProjMat, const glm::vec3 &camPos, const std::vector<Light> &lights);
    void Draw(const StaticMesh *mesh, const glm::mat4 &worldMat);
    void End();

private:
    struct RenderOp {
        glm::mat4 worldMat;
        const StaticMesh *staticMesh;
    };
    struct FullscreenQuad {
        FullscreenQuad(Graphics *graphics);
        ~FullscreenQuad();

        void Draw();

        Graphics *graphics;
        VertexFormat *vertexFormat;
        VertexBuffer *vertexBuffer;
    };
    struct GeometryPass {
        GeometryPass(Graphics *graphics);
        ~GeometryPass();

        void Process(Framebuffer *gbuffer, const std::vector<RenderOp> &rops, const glm::mat4 &viewProjMat);

        Graphics *graphics;
        VertexFormat *staticMeshVertexFormat;
        Program *staticMeshProgram;
        ConstantID staticMeshProgramViewProjMatID, staticMeshProgramWorldMatID;
    };
    struct LightPass {
        LightPass(Graphics *graphics, FullscreenQuad *fullscreenQuad);
        ~LightPass();

        void Process(Framebuffer *lightMap, Framebuffer *gbuffer, const std::vector<Light> &lights, const glm::vec3 &camPos);

        Graphics *graphics;
        FullscreenQuad *fullscreenQuad;
        Program *program[3];
        ConstantID programCamPosID[3];
        ConstantBuffer *lightConstantBuffer;
    };
    struct OutputPass {
        OutputPass(Graphics *graphics, FullscreenQuad *fullscreenQuad);
        ~OutputPass();

        void Process(Framebuffer *gbuffer, Framebuffer *lightMap);

        Graphics *graphics;
        FullscreenQuad *fullscreenQuad;
        Program *program;
    };

    RenderWindow *mWindow;
    Graphics *mGraphics;
    Framebuffer *mGBuffer, *mLightMap;
    SamplerState *mSamplerState;
    FullscreenQuad *mFullscreenQuad;
    GeometryPass *mGeometryPass;
    LightPass *mLightPass;
    OutputPass *mOutputPass;

    std::vector<RenderOp> mRenderOps;
    glm::mat4 mViewProjMat;
    glm::vec3 mCamPos;
    std::vector<Light> mLights;
};

}