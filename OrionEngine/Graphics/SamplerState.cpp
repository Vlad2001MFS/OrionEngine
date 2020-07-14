#include "SamplerState.h"
#include "glew.h"
#include <memory.h>

namespace oe {

constexpr GLenum gSamplerMinFilter[] = {
    GL_NEAREST,
    GL_LINEAR,
    GL_LINEAR_MIPMAP_NEAREST,
    GL_LINEAR_MIPMAP_LINEAR,
    GL_LINEAR_MIPMAP_LINEAR
};

constexpr GLenum gSamplerMagFilter[] = {
    GL_NEAREST,
    GL_LINEAR,
    GL_LINEAR,
    GL_LINEAR,
    GL_LINEAR
};

constexpr GLenum gSamplerAddressModes[] = {
    GL_REPEAT,
    GL_MIRRORED_REPEAT,
    GL_CLAMP_TO_EDGE,
    GL_CLAMP_TO_BORDER,
    GL_MIRROR_CLAMP_EXT
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

SamplerState::SamplerState(SamplerFilter filter, uint maxAnisotropy) 
    : SamplerState(filter, maxAnisotropy, CompareFunc::Less, false, SamplerAddressMode::Repeat, SamplerAddressMode::Repeat, SamplerAddressMode::Repeat,
             0, nullptr, -1000, 1000) { }

SamplerState::SamplerState(SamplerFilter filter, uint maxAnisotropy, CompareFunc compareFunc, bool compareRefToTex) 
    : SamplerState(filter, maxAnisotropy, compareFunc, compareRefToTex, SamplerAddressMode::Repeat, SamplerAddressMode::Repeat, SamplerAddressMode::Repeat,
                    0, nullptr, -1000, 1000) { }

SamplerState::SamplerState(SamplerFilter filter, uint maxAnisotropy, CompareFunc compareFunc, bool compareRefToTex, SamplerAddressMode uvw) 
    : SamplerState(filter, maxAnisotropy, compareFunc, compareRefToTex, uvw, uvw, uvw, 0, nullptr, -1000, 1000) { }

SamplerState::SamplerState(SamplerFilter filter, uint maxAnisotropy, CompareFunc compareFunc, bool compareRefToTex, SamplerAddressMode uvw,
                           float lodBias, const float * borderColor, float minLod, float maxLod)
    : SamplerState(filter, maxAnisotropy, compareFunc, compareRefToTex, uvw, uvw, uvw, lodBias, borderColor, minLod, maxLod) { }

SamplerState::SamplerState(SamplerFilter filter, uint maxAnisotropy, CompareFunc compareFunc, bool compareRefToTex,
                           SamplerAddressMode u, SamplerAddressMode v, SamplerAddressMode w, float lodBias,
                           const float * borderColor, float minLod, float maxLod)
    : mSamplerState(0), mFilter(filter), mMaxAnisotropy(maxAnisotropy), mCompareFunc(compareFunc), mCompareRefToTexture(compareRefToTex),
    mU(u), mV(v), mW(w), mLodBias(lodBias), mMinLod(minLod), mMaxLod(maxLod) {
    if (borderColor) {
        memcpy(mBorderColor, borderColor, sizeof(mBorderColor));
    }
    else {
        memset(mBorderColor, 0, sizeof(mBorderColor));
    }
    glGenSamplers(1, &mSamplerState);
    glSamplerParameteri(mSamplerState, GL_TEXTURE_MIN_FILTER, gSamplerMinFilter[static_cast<uint>(mFilter)]);
    glSamplerParameteri(mSamplerState, GL_TEXTURE_MAG_FILTER, gSamplerMagFilter[static_cast<uint>(mFilter)]);
    if (mFilter == SamplerFilter::Anisotropic) {
        glSamplerParameteri(mSamplerState, GL_TEXTURE_MAX_ANISOTROPY_EXT, mMaxAnisotropy);
    }
    glSamplerParameteri(mSamplerState, GL_TEXTURE_COMPARE_FUNC, gCompareFuncs[static_cast<GLenum>(mCompareFunc)]);
    glSamplerParameteri(mSamplerState, GL_TEXTURE_COMPARE_MODE, mCompareRefToTexture ? GL_COMPARE_REF_TO_TEXTURE : GL_NONE);
    glSamplerParameteri(mSamplerState, GL_TEXTURE_WRAP_S, gSamplerAddressModes[static_cast<uint>(mU)]);
    glSamplerParameteri(mSamplerState, GL_TEXTURE_WRAP_T, gSamplerAddressModes[static_cast<uint>(mV)]);
    glSamplerParameteri(mSamplerState, GL_TEXTURE_WRAP_R, gSamplerAddressModes[static_cast<uint>(mW)]);
    glSamplerParameterf(mSamplerState, GL_TEXTURE_LOD_BIAS, mLodBias);
    glSamplerParameterfv(mSamplerState, GL_TEXTURE_BORDER_COLOR, mBorderColor);
    glSamplerParameterf(mSamplerState, GL_TEXTURE_MIN_LOD, mMinLod);
    glSamplerParameterf(mSamplerState, GL_TEXTURE_MAX_LOD, mMaxLod);
}

SamplerState::~SamplerState() {
    glDeleteSamplers(1, &mSamplerState);
}

uint SamplerState::GetHandle() const {
    return mSamplerState;
}

SamplerFilter SamplerState::GetFilter() const {
    return mFilter;
}

uint SamplerState::GetMaxAnisotropy() const {
    return mMaxAnisotropy;
}

CompareFunc SamplerState::GetCompareFunc() const {
    return mCompareFunc;
}

bool SamplerState::IsCompareRefToTexture() const {
    return mCompareRefToTexture;
}

SamplerAddressMode SamplerState::GetAddressModeU() const {
    return mU;
}

SamplerAddressMode SamplerState::GetAddressModeV() const {
    return mV;
}

SamplerAddressMode SamplerState::GetAddressModeW() const {
    return mW;
}

float SamplerState::GetLodBias() const {
    return mLodBias;
}

const float * SamplerState::GetBorderColor() const {
    return mBorderColor;
}

float SamplerState::GetMinLod() const {
    return mMinLod;
}

float SamplerState::GetMaxLod() const {
    return mMaxLod;
}

}