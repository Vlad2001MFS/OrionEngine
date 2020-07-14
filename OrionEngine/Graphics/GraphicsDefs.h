#pragma once
#include "../Core/Common.h"

namespace oe {

enum class PrimitiveType {
    Points,
    LineStrip,
    Lines,
    TriangleStrip,
    Triangles,
};

enum class CompareFunc {
    Never,
    Less,
    Equal,
    LessEqual,
    Greater,
    NotEqual,
    GreatEqual,
    Always
};

enum class StencilOp {
    Keep,
    Zero,
    Replace,
    IncrSat,
    DecrSat,
    Invert,
    Incr,
    Decr,
};

enum class CullMode {
    None,
    Front,
    Back,
};

enum class BlendFactor {
    Zero,
    One,
    SrcColor,
    InvSrcColor,
    SrcAlpha,
    InvSrcAlpha,
    DestAlpha,
    InvDestAlpha,
    DestColor,
    InvDestColor,
    SrcAlphaSat,
};

enum class BlendOp {
    Add,
    Subtract,
    RevSubtract,
    Min,
    Max,
};

enum class BlendMode {
    Replace,
    Add,
    Multiply,
    Alpha,
    AddAlpha,
    PreMulAlpha,
    InvDestAlpha,
    Subtract,
    SubtractAlpha,
};

enum class CullFace {
    None,
    Front,
    Back,
    FrontBack
};

enum class FillMode {
    Solid,
    Wireframe
};

enum class FrontFace {
    CCW,
    CW
};

struct BlendModeDesc {
    BlendModeDesc();
    BlendModeDesc(bool blendEnable, BlendFactor srcBlend, BlendFactor dstBlend, BlendOp blendOp,
                  BlendFactor srcBlendAlpha, BlendFactor dstBlendAlpha, BlendOp blendOpAlpha);

    bool blendEnable;
    BlendFactor srcBlend;
    BlendFactor dstBlend;
    BlendOp blendOp;
    BlendFactor srcBlendAlpha;
    BlendFactor dstBlendAlpha;
    BlendOp blendOpAlpha;
};

struct StencilTestDesc {
    StencilTestDesc();
    StencilTestDesc(CompareFunc frontFunc, StencilOp frontFail, StencilOp frontDepthFail, StencilOp frontPass,
                    CompareFunc backFunc, StencilOp backFail, StencilOp backDepthFail, StencilOp backPass,
                    uchar readMask = 0xff, uchar writeMask = 0xff);

    CompareFunc frontFunc;
    StencilOp frontFail;
    StencilOp frontDepthFail;
    StencilOp frontPass;
    CompareFunc backFunc;
    StencilOp backFail;
    StencilOp backDepthFail;
    StencilOp backPass;
    uchar readMask;
    uchar writeMask;
};

struct ColorMask {
    ColorMask();
    ColorMask(bool rgba);
    ColorMask(bool r, bool g, bool b, bool a);

    bool r, g, b, a;
};

struct PolygonOffset {
    PolygonOffset();
    PolygonOffset(bool enabled, float factor, float units);

    bool enabled;
    float factor, units;
};

}