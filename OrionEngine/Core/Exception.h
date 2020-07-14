#pragma once

namespace oe {

class Exception {
public:
    Exception(const char *fmt, ...);
    ~Exception();

    const char *GetMessage() const;

private:
    char *mMessage;
};

}