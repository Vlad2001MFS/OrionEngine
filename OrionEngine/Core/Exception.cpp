#include "Exception.h"
#include "Common.h"
#include <cstdio>
#include <cstdarg>
#include <memory>

namespace oe {

Exception::Exception(const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    unsigned int size = _vscprintf(fmt, ap) + 1;
    mMessage = new char[size];
    vsprintf_s(mMessage, size, fmt, ap);
    va_end(ap);
}

Exception::~Exception() {
    OE_SAFE_DELETE_ARRAY(mMessage);
}

const char *Exception::GetMessage() const {
    return mMessage;
}

}