#include "Timer.h"
#include "SDL2/SDL.h"

namespace oe {
namespace core {

Timer::Timer() {
    mIsStarted = false;
    mStartTime = 0;
}

Timer::~Timer() {
    Stop();
}

void Timer::Start() {
    if (!IsStarted()) {
        mIsStarted = true;
        mStartTime = SDL_GetTicks();
    }
}

void Timer::Stop() {
    if (IsStarted()) {
        mIsStarted = false;
    }
}

void Timer::Reset() {
    Stop();
    Start();
}

uint Timer::GetMinuts() const {
    return (SDL_GetTicks() - mStartTime) / 1000 / 60;
}

uint Timer::GetSeconds() const {
    return (SDL_GetTicks() - mStartTime) / 1000;
}

uint Timer::GetMilliseconds() const {
    return SDL_GetTicks() - mStartTime;
}

bool Timer::IsStarted() const {
    return mIsStarted;
}

}
}