#include "GraphicsDefs.h"

namespace oe {

BlendModeDesc::BlendModeDesc() 
    : blendEnable(false), srcBlend(BlendFactor::One), dstBlend(BlendFactor::One), blendOp(BlendOp::Add),
    srcBlendAlpha(BlendFactor::One), dstBlendAlpha(BlendFactor::One), blendOpAlpha(BlendOp::Add) { }

BlendModeDesc::BlendModeDesc(bool blendEnable, BlendFactor srcBlend, BlendFactor destBlend, BlendOp blendOp,
                             BlendFactor srcBlendAlpha, BlendFactor destBlendAlpha, BlendOp blendOpAlpha)
    : blendEnable(blendEnable), srcBlend(srcBlend), dstBlend(destBlend), blendOp(blendOp),
    srcBlendAlpha(srcBlendAlpha), dstBlendAlpha(destBlendAlpha), blendOpAlpha(blendOpAlpha) { }

StencilTestDesc::StencilTestDesc() 
    : frontFunc(CompareFunc::Always), frontFail(StencilOp::Keep), frontDepthFail(StencilOp::Keep), frontPass(StencilOp::Keep),
    backFunc(CompareFunc::Always), backFail(StencilOp::Keep), backDepthFail(StencilOp::Keep), backPass(StencilOp::Keep), readMask(0xff), writeMask(0xff) { }

StencilTestDesc::StencilTestDesc(CompareFunc frontFunc, StencilOp frontFail, StencilOp frontDepthFail, StencilOp frontPass,
                                 CompareFunc backFunc, StencilOp backFail, StencilOp backDepthFail, StencilOp backPass,
                                 uchar stencilReadMask, uchar stencilWriteMask)
    : frontFunc(frontFunc), frontFail(frontFail), frontDepthFail(frontDepthFail), frontPass(frontPass),
    backFunc(backFunc), backFail(backFail), backDepthFail(backDepthFail), backPass(backPass), readMask(stencilReadMask), writeMask(stencilWriteMask) { }

ColorMask::ColorMask() 
    : r(true), g(true), b(true), a(true) { }

ColorMask::ColorMask(bool rgba) 
    : r(rgba), g(rgba), b(rgba), a(rgba) { }

ColorMask::ColorMask(bool r, bool g, bool b, bool a) 
    : r(r), g(g), b(b), a(a) { }

PolygonOffset::PolygonOffset() 
    : enabled(false), factor(0), units(0) { }

PolygonOffset::PolygonOffset(bool enabled, float factor, float units) 
    : enabled(enabled), factor(factor), units(units) { }

}