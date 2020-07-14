#pragma once
#include "Common.h"
#include "Exception.h"

#define OE_LOG_INFO(fmt, ...) do { oe::Debug::Get().Info(fmt, __VA_ARGS__); } while(false)
#define OE_LOG_WARNING(fmt, ...) do { oe::Debug::Get().Warning(fmt, __VA_ARGS__); } while(false)
#define OE_LOG_ERROR(fmt, ...) \
    do { \
        oe::Debug::Get().Error("FILE: '%s'\nFUNCTION: '%s'\nLINE: %d\n" fmt, __FILE__, __FUNCSIG__, __LINE__, __VA_ARGS__); \
        throw oe::Exception("FILE: '%s'\nFUNCTION: '%s'\nLINE: %d\n" fmt, __FILE__, __FUNCSIG__, __LINE__, __VA_ARGS__); \
    } while(false)
#define OE_ASSERT(expr) \
    do { if (expr) {  } else { \
        oe::Debug::Get().Error("ASSERTION FAILED!\nFILE: '%s'\nFUNCTION: '%s'\nLINE: %d\nEXPRESSION: '%s'", __FILE__, __FUNCSIG__, __LINE__, #expr); \
        throw oe::Exception("ASSERTION FAILED!\nFILE: '%s'\nFUNCTION: '%s'\nLINE: %d\nEXPRESSION: '%s'", __FILE__, __FUNCSIG__, __LINE__, #expr); \
    } } while(false)

namespace oe {

class Debug {
public:
    void Info(const char *fmt, ...);
    void Warning(const char *fmt, ...);
    void Error(const char *fmt, ...);

    void StartTimer();
    uint StopTimer();

    static Debug &Get();

private:
    Debug();
    ~Debug();
    void mSave();

    void *mFile;
    uint mTimer;
    bool mForcedSave;
};

}