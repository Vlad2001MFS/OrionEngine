#pragma once
#include "Common.h"
#include <string>

namespace oe {

enum class FileMode {
    Read,
    Write,
    ReadWrite
};

class File {
public:
    File();
    File(const std::string &filename, FileMode mode);
    ~File();

    void Open(const std::string &filename, FileMode mode);
    void Close();

    uint Read(void *dest, uint size) const;
    uint Write(const void *data, uint size);
    std::string ReadAllText() const;

    uint GetSize() const;

    static bool IsExist(const std::string &filename);

private:
    void *mHandle;
};

}