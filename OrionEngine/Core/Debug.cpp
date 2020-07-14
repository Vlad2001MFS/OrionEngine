#include "Debug.h"
#include "BuildConfig.h"
#include <SDL2/SDL.h>
#include <cstdio>
#include <cstdarg>
#ifdef OE_PLATFORM_WINDOWS
//#   include <windows.h>
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA(_In_opt_ const char *lpOutputString);
#   define OutputDebugString OutputDebugStringA
#else
#   define OutputDebugString(str) (void*)0;
#endif

namespace oe {

struct MsgBuf {
    MsgBuf(uint count) : buf(new char[count]) { }
    ~MsgBuf() { OE_SAFE_DELETE_ARRAY(this->buf); }

    char *buf;
};

void Debug::Info(const char *fmt, ...) {
    if (fmt) {
        va_list ap;
        va_start(ap, fmt);
        MsgBuf tempStr(_vscprintf(fmt, ap) + 1);
        vsprintf(tempStr.buf, fmt, ap);
        MsgBuf buf(_scprintf("[ INFO ] %s\n", tempStr.buf) + 1);
        sprintf(buf.buf, "[ INFO ] %s\n", tempStr.buf);
        va_end(ap);
        if (mFile) {
            fprintf((FILE*)mFile, "%s", buf.buf);
            fflush((FILE*)mFile);
            mSave();
        }
        printf("%s", buf.buf);
        OutputDebugString(buf.buf);
    }
}

void Debug::Warning(const char * fmt, ...) {
    if (fmt) {
        va_list ap;
        va_start(ap, fmt);
        MsgBuf tempStr(_vscprintf(fmt, ap) + 1);
        vsprintf(tempStr.buf, fmt, ap);
        MsgBuf buf(_scprintf("[ WARNING ] %s\n", tempStr.buf) + 1);
        sprintf(buf.buf, "[ WARNING ] %s\n", tempStr.buf);
        va_end(ap);
        if (mFile) {
            fprintf((FILE*)mFile, "%s", buf.buf);
            fflush((FILE*)mFile);
            mSave();
        }
        printf("%s", buf.buf);
        OutputDebugString(buf.buf);
    }
}

void Debug::Error(const char * fmt, ...) {
    if (fmt) {
        va_list ap;
        va_start(ap, fmt);
        MsgBuf tempStr(_vscprintf(fmt, ap) + 1);
        vsprintf(tempStr.buf, fmt, ap);
        MsgBuf buf(_scprintf("[ ERROR ] %s\n", tempStr.buf) + 1);
        sprintf(buf.buf, "[ ERROR ] %s\n", tempStr.buf);
        va_end(ap);
        if (mFile) {
            fprintf((FILE*)mFile, "%s", buf.buf);
            fflush((FILE*)mFile);
            mSave();
        }
        printf("%s", buf.buf);
        OutputDebugString(buf.buf);
    }
}

void Debug::StartTimer() {
    mTimer = SDL_GetTicks();
}

unsigned int Debug::StopTimer() {
    int time = SDL_GetTicks() - mTimer;
    mTimer = 0;
    return time;
}

Debug &Debug::Get() {
    static Debug debug;
    return debug;
}

Debug::Debug() : mFile(fopen("OrionEngine.log", "w")), mForcedSave(true) { }

Debug::~Debug() {
    fclose((FILE*)mFile);
    mFile = nullptr;
}

void Debug::mSave() {
    if (mForcedSave) {
        fclose((FILE*)mFile);
        mFile = fopen("OrionEngine.log", "a");
    }
}

}