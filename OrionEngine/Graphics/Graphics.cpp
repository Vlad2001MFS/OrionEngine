#include "Graphics.h"
#include "../Core/BuildConfig.h"
#include "../Core/Common.h"
#include "../Core/Debug.h"
#include "SDL2/SDL_image.h"
#include "glew.h"

namespace oe {

constexpr GLenum gPrimitiveTypes[] = {
    GL_POINTS,
    GL_LINE_STRIP,
    GL_LINES,
    GL_TRIANGLE_STRIP,
    GL_TRIANGLES,
};

constexpr GLenum gCompareFuncs[] = {
    GL_NEVER,
    GL_LESS,
    GL_EQUAL,
    GL_LEQUAL,
    GL_GREATER,
    GL_NOTEQUAL,
    GL_GEQUAL,
    GL_ALWAYS
};

constexpr GLenum gStencilOps[] =
{
    GL_KEEP,
    GL_ZERO,
    GL_REPLACE,
    GL_INCR,
    GL_DECR,
    GL_INVERT,
    GL_INCR_WRAP,
    GL_DECR_WRAP,
};

constexpr GLenum gCullFaces[] = {
    0,
    GL_FRONT,
    GL_BACK,
    GL_FRONT_AND_BACK
};

constexpr GLenum gFillModes[] = {
    GL_FILL,
    GL_LINE
};

constexpr GLenum gFrontFaces[] = {
    GL_CCW,
    GL_CW
};

constexpr int gBlendFactors[] = {
    GL_ZERO,
    GL_ONE,
    GL_SRC_COLOR,
    GL_ONE_MINUS_SRC_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_ONE_MINUS_DST_ALPHA,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_SRC_ALPHA_SATURATE,
};

constexpr int gBlendOps[] = {
    GL_FUNC_ADD,
    GL_FUNC_SUBTRACT,
    GL_FUNC_REVERSE_SUBTRACT,
    GL_MIN,
    GL_MAX,
};

const BlendModeDesc gBlendModeDescs[] = {
    BlendModeDesc(false, BlendFactor::One         , BlendFactor::Zero       , BlendOp::Add        , BlendFactor::One         , BlendFactor::Zero       , BlendOp::Add),
    BlendModeDesc(true,  BlendFactor::One         , BlendFactor::One        , BlendOp::Add        , BlendFactor::One         , BlendFactor::One        , BlendOp::Add),
    BlendModeDesc(true,  BlendFactor::DestColor   , BlendFactor::Zero       , BlendOp::Add        , BlendFactor::One         , BlendFactor::Zero       , BlendOp::Add),
    BlendModeDesc(true,  BlendFactor::SrcAlpha    , BlendFactor::InvSrcAlpha, BlendOp::Add        , BlendFactor::SrcAlpha    , BlendFactor::InvSrcAlpha, BlendOp::Add),
    BlendModeDesc(true,  BlendFactor::SrcAlpha    , BlendFactor::One        , BlendOp::Add        , BlendFactor::SrcAlpha    , BlendFactor::One        , BlendOp::Add),
    BlendModeDesc(true,  BlendFactor::One         , BlendFactor::InvSrcAlpha, BlendOp::Add        , BlendFactor::One         , BlendFactor::InvSrcAlpha, BlendOp::Add),
    BlendModeDesc(true,  BlendFactor::InvDestAlpha, BlendFactor::DestAlpha  , BlendOp::Add        , BlendFactor::InvDestAlpha, BlendFactor::DestAlpha  , BlendOp::Add),
    BlendModeDesc(true,  BlendFactor::One         , BlendFactor::One        , BlendOp::RevSubtract, BlendFactor::One         , BlendFactor::One        , BlendOp::RevSubtract),
    BlendModeDesc(true,  BlendFactor::SrcAlpha    , BlendFactor::One        , BlendOp::RevSubtract, BlendFactor::SrcAlpha    , BlendFactor::One        , BlendOp::RevSubtract)
};

void __stdcall DebugCallback(uint source, uint type, uint id, uint severity, int length, const char * message, const void * userParam) {
    const char *sourceStr = nullptr, *typeStr = nullptr, *severityStr = nullptr;
    switch (source) {
        case GL_DEBUG_SOURCE_API_ARB:
            sourceStr = "API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
            sourceStr = "Window system";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
            sourceStr = "Shader compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
            sourceStr = "Third party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION_ARB:
            sourceStr = "Application";
            break;
        case GL_DEBUG_SOURCE_OTHER_ARB:
            sourceStr = "Other";
            break;
        default:
            sourceStr = "Unknown";
            break;
    }

    switch (type) {
        case GL_DEBUG_TYPE_ERROR_ARB:
            typeStr = "Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
            typeStr = "Deprecated behaviour";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
            typeStr = "Undefined behaviour";
            break;
        case GL_DEBUG_TYPE_PORTABILITY_ARB:
            typeStr = "Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE_ARB:
            typeStr = "Performance";
            break;
        case GL_DEBUG_TYPE_OTHER_ARB:
            typeStr = "Other";
            break;
        default:
            typeStr = "Unknown";
            break;
    }

    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH_ARB:
            severityStr = "High";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM_ARB:
            severityStr = "Medium";
            break;
        case GL_DEBUG_SEVERITY_LOW_ARB:
            severityStr = "Low";
            break;
        default:
            severityStr = "Unknown";
            break;
    }

    if (type == GL_DEBUG_TYPE_ERROR_ARB)
        OE_LOG_ERROR("OpenGL Debug:\n\tSource: %s\n\tType: %s\n\tId: %d\n\tSeverity: %s\n\tMessage: %s", sourceStr, typeStr, id, severityStr, message);
    else if (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB || type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB || type == GL_DEBUG_TYPE_PORTABILITY_ARB || type == GL_DEBUG_TYPE_PERFORMANCE_ARB)
        OE_LOG_WARNING("OpenGL Debug:\n\tSource: %s\n\tType: %s\n\tId: %d\n\tSeverity: %s\n\tMessage: %s", sourceStr, typeStr, id, severityStr, message);
    else
        OE_LOG_INFO("OpenGL Debug:\n\tSource: %s\n\tType: %s\n\tId: %d\n\tSeverity: %s\n\tMessage: %s", sourceStr, typeStr, id, severityStr, message);
}

Graphics::Graphics() : mCurrentDepthMask(true) {
    OE_LOG_INFO("Initializing Graphics...");
    glewExperimental = true;
    GLenum result = glewInit();
    if (result != GLEW_OK) {
        OE_LOG_ERROR("Failed to initialize glew. Error: %s", glewGetErrorString(result));
        OE_LOG_INFO("Initializing Graphics... FAILED");
    }
#ifdef OE_DEBUG
    if (GLEW_ARB_debug_output) {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(DebugCallback, nullptr);
    }
    else {
        OE_LOG_WARNING("OpenGL Debug output not supported");
    }
#endif
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        OE_LOG_ERROR("Failed to initialize SDL_image. Error: %s", SDL_GetError());
        OE_LOG_INFO("Initializing Graphics... FAILED");
    }
    OE_LOG_INFO("Initializing Graphics... OK");
}

Graphics::~Graphics() {
    OE_LOG_INFO("Shutdown Graphics...");
    OE_LOG_INFO("Shutdown Graphics... OK");
}

void Graphics::ClearColor(float r, float g, float b, float a) { 
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::ClearColor(const float * color) { 
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Graphics::ClearDepth(float depth) { 
    if (!mCurrentDepthMask) {
        glDepthMask(true);
    }
    glClearDepth(depth);
    glClear(GL_DEPTH_BUFFER_BIT);
    if (!mCurrentDepthMask) {
        glDepthMask(false);
    }
}

void Graphics::Draw(PrimitiveType primType, uint vertexCount, uint firstVertex) { 
    glDrawArrays(gPrimitiveTypes[static_cast<uint>(primType)], firstVertex, vertexCount);
}

void Graphics::DrawInstanced(PrimitiveType primType, uint vertexCountPerInstance, uint firstVertex, uint instanceCount) {
    glDrawArraysInstanced(gPrimitiveTypes[static_cast<uint>(primType)], firstVertex, vertexCountPerInstance, instanceCount);
}

void Graphics::DrawIndexed(PrimitiveType primType, uint indexCount, uint firstIndex, IndexType indexType) {
    if (indexType == IndexType::Uint) {
        glDrawElements(gPrimitiveTypes[static_cast<uint>(primType)], indexCount, GL_UNSIGNED_INT, static_cast<char*>(nullptr) + firstIndex*sizeof(uint));
    }
    else if (indexType == IndexType::Ushort) {
        glDrawElements(gPrimitiveTypes[static_cast<uint>(primType)], indexCount, GL_UNSIGNED_SHORT, static_cast<char*>(nullptr) + firstIndex*sizeof(ushort));
    }
    else {
        glDrawElements(gPrimitiveTypes[static_cast<uint>(primType)], indexCount, GL_UNSIGNED_BYTE, static_cast<char*>(nullptr) + firstIndex*sizeof(uchar));
    }
}

void Graphics::DrawIndexedInstanced(PrimitiveType primType, uint indexCountPerInstance, uint firstIndex, IndexType indexType, uint instanceCount) {

    if (indexType == IndexType::Uint) {
        glDrawElementsInstanced(gPrimitiveTypes[static_cast<uint>(primType)], indexCountPerInstance, GL_UNSIGNED_INT,
                                static_cast<char*>(nullptr) + firstIndex*sizeof(uint), instanceCount);
    }
    else if (indexType == IndexType::Ushort) {
        glDrawElementsInstanced(gPrimitiveTypes[static_cast<uint>(primType)], indexCountPerInstance, GL_UNSIGNED_SHORT,
                                static_cast<char*>(nullptr) + firstIndex*sizeof(ushort), instanceCount);
    }
    else {
        glDrawElementsInstanced(gPrimitiveTypes[static_cast<uint>(primType)], indexCountPerInstance, GL_UNSIGNED_BYTE,
                                static_cast<char*>(nullptr) + firstIndex*sizeof(uchar), instanceCount);
    }
}

void Graphics::SetVertexFormat(const VertexFormat * vertexFormat) {
    if (vertexFormat) {
        glBindVertexArray(vertexFormat->GetHandle());
    }
    else {
        glBindVertexArray(0);
    }
}

void Graphics::SetVertexBuffer(const VertexBuffer * vertexBuffer, uint slot, uint offset, uint stride) {
    if (vertexBuffer) {
        glBindVertexBuffer(slot, vertexBuffer->GetHandle(), offset, stride);
    }
    else {
        glBindVertexBuffer(slot, 0, offset, stride);
    }
}

void Graphics::SetIndexBuffer(const IndexBuffer * indexBuffer) {
    if (indexBuffer) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->GetHandle());
    }
    else {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void Graphics::SetConstantBuffer(const ConstantBuffer * constantBuffer, uint slot) {
    if (constantBuffer) {
        glBindBufferBase(GL_UNIFORM_BUFFER, slot, constantBuffer->GetHandle());
    }
    else {
        glBindBufferBase(GL_UNIFORM_BUFFER, slot, 0);
    }
}

void Graphics::SetProgram(const Program * program) {
    if (program) {
        glUseProgram(program->GetHandle());
    }
    else {
        glUseProgram(0);
    }
}

void Graphics::SetConstant(ConstantID id, int value) { 
    glUniform1i(id.value, value);
}

void Graphics::SetConstant(ConstantID id, float value) {
    glUniform1f(id.value, value);
}

void Graphics::SetConstant(ConstantID id, const glm::vec2 & value) {
    glUniform2f(id.value, value.x, value.y);
}

void Graphics::SetConstant(ConstantID id, const glm::vec3 & value) {
    glUniform3f(id.value, value.x, value.y, value.z);
}

void Graphics::SetConstant(ConstantID id, const glm::vec4 & value) {
    glUniform4f(id.value, value.x, value.y, value.z, value.w);
}

void Graphics::SetConstant(ConstantID id, const glm::mat4 & value) {
    glUniformMatrix4fv(id.value, 1, false, glm::value_ptr(value));
}

void Graphics::SetConstant(ConstantID id, const int * value, uint count) {
    glUniform1iv(id.value, count, value);
}

void Graphics::SetConstant(ConstantID id, const float * value, uint count) {
    glUniform1fv(id.value, count, value);
}

void Graphics::SetConstant(ConstantID id, const glm::vec2 * value, uint count) {
    glUniform2fv(id.value, count, reinterpret_cast<const float*>(value));
}

void Graphics::SetConstant(ConstantID id, const glm::vec3 * value, uint count) {
    glUniform3fv(id.value, count, reinterpret_cast<const float*>(value));
}

void Graphics::SetConstant(ConstantID id, const glm::vec4 * value, uint count) {
    glUniform4fv(id.value, count, reinterpret_cast<const float*>(value));
}

void Graphics::SetConstant(ConstantID id, const glm::mat4 * value, uint count) {
    glUniformMatrix4fv(id.value, count, false, reinterpret_cast<const float*>(value));
}

void Graphics::SetTexture2D(const Texture2D * texture, uint slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    if (texture) {
        glBindTexture(GL_TEXTURE_2D, texture->GetHandle());
    }
    else         {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void Graphics::SetSamplerState(const SamplerState * samplerState, uint slot) {
    if (samplerState) {
        glBindSampler(slot, samplerState->GetHandle());
    }
    else {
        glBindSampler(slot, 0);
    }
}

void Graphics::SetFramebuffer(const Framebuffer * framebuffer) {
    static const GLenum drawBuffersUser[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3,
        GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };
    static const GLenum drawBuffersSys[] = { GL_BACK };
    
    if (framebuffer) {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->GetHandle());
        glDrawBuffers(framebuffer->GetRenderTargets().size(), drawBuffersUser);
        //SetViewport(IntRect(glm::ivec2(0, 0), framebuffer->GetSize()));
    }
    else {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glDrawBuffers(1, drawBuffersSys);
        //SetViewport(IntRect(glm::ivec2(0, 0), mDevice->GetWindowSize()));
    }
}

void Graphics::SetDepthState(bool depthTestEnabled, CompareFunc compareFunc, bool depthMask) {
    if (depthTestEnabled) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }
    glDepthFunc(gCompareFuncs[static_cast<GLenum>(compareFunc)]);
    glDepthMask(depthMask);
}

void Graphics::SetStencilState(bool enabled, const StencilTestDesc & desc, uchar ref) {
    if (enabled) {
        glEnable(GL_STENCIL_TEST);
        glStencilFuncSeparate(gCompareFuncs[static_cast<uint>(desc.frontFunc)], gCompareFuncs[static_cast<uint>(desc.backFunc)],
                              ref, desc.readMask);
        glStencilOpSeparate(GL_FRONT, gStencilOps[static_cast<uint>(desc.frontFail)], gStencilOps[static_cast<uint>(desc.frontDepthFail)],
                            gStencilOps[static_cast<uint>(desc.frontPass)]);
        glStencilOpSeparate(GL_BACK, gStencilOps[static_cast<uint>(desc.backFail)], gStencilOps[static_cast<uint>(desc.backDepthFail)],
                            gStencilOps[static_cast<uint>(desc.backPass)]);
        glStencilMask(desc.writeMask);
    }
    else {
        glDisable(GL_STENCIL_TEST);
    }
}

void Graphics::SetBlendState(const BlendModeDesc & blendModeDesc, const ColorMask & colorMask) {
    if (blendModeDesc.blendEnable) {
        glEnable(GL_BLEND);
        glBlendFuncSeparate(gBlendFactors[static_cast<uint>(blendModeDesc.srcBlend)], gBlendFactors[static_cast<uint>(blendModeDesc.dstBlend)],
                            gBlendFactors[static_cast<uint>(blendModeDesc.srcBlendAlpha)], gBlendFactors[static_cast<uint>(blendModeDesc.dstBlendAlpha)]);
        glBlendEquationSeparate(gBlendOps[static_cast<uint>(blendModeDesc.blendOp)], gBlendOps[static_cast<uint>(blendModeDesc.blendOpAlpha)]);
    }
    else {
        glDisable(GL_BLEND);
    }
    glColorMask(colorMask.r, colorMask.g, colorMask.b, colorMask.a);
}

void Graphics::SetBlendState(BlendMode blendMode, const ColorMask & colorMask) {
    SetBlendState(gBlendModeDescs[static_cast<uint>(blendMode)], colorMask);
}

void Graphics::SetRasterizerState(CullFace cullFace, FillMode fillMode, FrontFace frontFace, const PolygonOffset & polygonOffset) {
    if (cullFace == CullFace::None) {
        glDisable(GL_CULL_FACE);
    }
    else {
        glEnable(GL_CULL_FACE);
        glCullFace(gCullFaces[static_cast<uint>(cullFace)]);
    }
    glPolygonMode(GL_FRONT_AND_BACK, gFillModes[static_cast<uint>(fillMode)]);
    glFrontFace(gFrontFaces[static_cast<uint>(frontFace)]);
    if (polygonOffset.enabled) {
        glEnable(GL_POLYGON_OFFSET_FILL);
        glPolygonOffset(polygonOffset.factor, polygonOffset.units);
    }
    else {
        glDisable(GL_POLYGON_OFFSET_FILL);
    }
}

void Graphics::SetViewport(const IntRect & vp) { 
    glViewport(vp.pos.x, vp.pos.y, vp.size.x, vp.size.y);
}

}