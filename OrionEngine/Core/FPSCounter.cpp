#include "FPSCounter.h"

FPSCounter::FPSCounter() : mFps(0), mFrameTime(0) { }

FPSCounter::~FPSCounter() { }

void FPSCounter::BeginFrame() { 
    if (!mTimer.IsStarted()) {
        mTimer.Start();
    }
}

void FPSCounter::EndFrame() { 
    static BgUint32 framesCount = 0;
    if (mTimer.GetMilliseconds() >= 1000) {
        mFps = framesCount;
        mFrameTime = 1000.0f / mFps;
        mTimer.Reset();
        framesCount = 0;
    }
    else {
        framesCount++;
    }
}

BgUint32 FPSCounter::GetFps() const {
    return mFps;
}

float FPSCounter::GetFrameTime() const {
    return mFrameTime;
}