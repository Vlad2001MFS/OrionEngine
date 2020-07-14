#pragma once
#include "../Core/Common.h"
#include "GraphicsDefs.h"

namespace oe {

enum class SamplerFilter {
    Point,
    Linear,
    Bilinear,
    Trilinear,
    Anisotropic,
};

enum class SamplerAddressMode {
    Repeat,
    Mirror,
    Clamp,
    Border,
    MirrorOnce
};

class SamplerState {
public:
    SamplerState(SamplerFilter filter, uint maxAnisotropy = 1);
    SamplerState(SamplerFilter filter, uint maxAnisotropy, CompareFunc compareFunc, bool compareRefToTex);
    SamplerState(SamplerFilter filter, uint maxAnisotropy, CompareFunc compareFunc, bool compareRefToTex, SamplerAddressMode uvw);
    SamplerState(SamplerFilter filter, uint maxAnisotropy, CompareFunc compareFunc, bool compareRefToTex, SamplerAddressMode uvw,
                 float lodBias, const float *borderColor, float minLod, float maxLod);
    SamplerState(SamplerFilter filter, uint maxAnisotropy, CompareFunc compareFunc, bool compareRefToTex,
                 SamplerAddressMode u, SamplerAddressMode v, SamplerAddressMode w, float lodBias, const float *borderColor, float minLod, float maxLod);
    ~SamplerState();

    uint GetHandle() const;
    SamplerFilter GetFilter() const;
    uint GetMaxAnisotropy() const;
    CompareFunc GetCompareFunc() const;
    bool IsCompareRefToTexture() const;
    SamplerAddressMode GetAddressModeU() const;
    SamplerAddressMode GetAddressModeV() const;
    SamplerAddressMode GetAddressModeW() const;
    float GetLodBias() const;
    const float *GetBorderColor() const;
    float GetMinLod() const;
    float GetMaxLod() const;

private:
    uint mSamplerState;
    SamplerFilter mFilter;
    uint mMaxAnisotropy;
    CompareFunc mCompareFunc;
    bool mCompareRefToTexture;
    SamplerAddressMode mU, mV, mW;
    float mLodBias, mBorderColor[4], mMinLod, mMaxLod;
};

}