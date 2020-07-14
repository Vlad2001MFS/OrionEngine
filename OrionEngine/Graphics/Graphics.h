#pragma once
#include "GraphicsDefs.h"
#include "VertexFormat.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Program.h"
#include "Texture2D.h"
#include "SamplerState.h"
#include "Framebuffer.h"
#include "../Math/IntRect.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"

namespace oe {

enum class IndexType {
    Uint,
    Ushort,
    Byte
};

class Graphics {
public:
    Graphics();
    ~Graphics();

    void ClearColor(float r, float g, float b, float a);
    void ClearColor(const float *color);
    void ClearDepth(float depth);
    void Draw(PrimitiveType primType, uint vertexCount, uint firstVertex);
    void DrawInstanced(PrimitiveType primType, uint vertexCountPerInstance, uint firstVertex, uint instanceCount);
    void DrawIndexed(PrimitiveType primType, uint indexCount, uint firstIndex, IndexType indexType);
    void DrawIndexedInstanced(PrimitiveType primType, uint indexCountPerInstance, uint firstIndex, IndexType indexType, uint instanceCount);

    void SetVertexFormat(const VertexFormat *vertexFormat);
    void SetVertexBuffer(const VertexBuffer *vertexBuffer, uint slot, uint offset, uint stride);
    void SetIndexBuffer(const IndexBuffer *indexBuffer);
    void SetConstantBuffer(const ConstantBuffer *constantBuffer, uint slot);
    void SetProgram(const Program *program);
    void SetConstant(ConstantID id, int value);
    void SetConstant(ConstantID id, float value);
    void SetConstant(ConstantID id, const glm::vec2 &value);
    void SetConstant(ConstantID id, const glm::vec3 &value);
    void SetConstant(ConstantID id, const glm::vec4 &value);
    void SetConstant(ConstantID id, const glm::mat4 &value);
    void SetConstant(ConstantID id, const int *value, uint count);
    void SetConstant(ConstantID id, const float *value, uint count);
    void SetConstant(ConstantID id, const glm::vec2 *value, uint count);
    void SetConstant(ConstantID id, const glm::vec3 *value, uint count);
    void SetConstant(ConstantID id, const glm::vec4 *value, uint count);
    void SetConstant(ConstantID id, const glm::mat4 *value, uint count);
    void SetTexture2D(const Texture2D *texture, uint slot);
    void SetSamplerState(const SamplerState *samplerState, uint slot);
    void SetFramebuffer(const Framebuffer *framebuffer);
    void SetDepthState(bool depthTestEnabled, CompareFunc compareFunc, bool depthMask);
    void SetStencilState(bool enabled, const StencilTestDesc &desc, uchar ref);
    void SetBlendState(const BlendModeDesc &blendModeDesc, const ColorMask &colorMask);
    void SetBlendState(BlendMode blendMode, const ColorMask &colorMask);
    void SetRasterizerState(CullFace cullFace, FillMode fillMode, FrontFace frontFace, const PolygonOffset &polygonOffset);
    void SetViewport(const IntRect &vp);

private:
    bool mCurrentDepthMask;
};

}