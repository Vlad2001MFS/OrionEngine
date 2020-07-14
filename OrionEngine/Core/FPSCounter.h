#pragma once
#include "BgCommon.h"

class FPSCounter {
public:
    FPSCounter();
    ~FPSCounter();

    void BeginFrame();
    void EndFrame();

    BgUint32 GetFps() const;
    float GetFrameTime() const;

private:
    BgTimer mTimer;
    BgUint32 mFps;
    float mFrameTime;
};