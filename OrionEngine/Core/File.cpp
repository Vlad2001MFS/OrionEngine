#include "File.h"
#include "Debug.h"
#include <cstdio>

namespace oe {

File::File() : mHandle(nullptr) { }

File::File(const std::string & filename, FileMode mode) : mHandle(nullptr) {
    Open(filename, mode);
}

File::~File() { 
    Close();
}

void File::Open(const std::string & filename, FileMode mode) {
    switch (mode) {
        case FileMode::Read:
            mHandle = fopen(filename.data(), "rb");
            break;
        case FileMode::Write:
            mHandle = fopen(filename.data(), "wb");
            break;
        case FileMode::ReadWrite:
            mHandle = fopen(filename.data(), "rwb");
            break;
    }
    if (!mHandle) {
        OE_LOG_ERROR("Failed to open file '%s'", filename.data());
    }
}

void File::Close() { 
    fclose(static_cast<FILE*>(mHandle));
}

uint File::Read(void * dest, uint size) const {
    return fread(dest, 1, size, static_cast<FILE*>(mHandle));
}

uint File::Write(const void * data, uint size) {
    return fwrite(data, 1, size, static_cast<FILE*>(mHandle));
}

std::string File::ReadAllText() const {
    uint size = GetSize();
    std::string buf(size, ' ');
    Read(buf.data(), size);
    return buf;
}

uint File::GetSize() const {
    FILE *f = static_cast<FILE*>(mHandle);
    uint curPos = ftell(f);
    fseek(f, 0, SEEK_END);
    uint size = ftell(f);
    fseek(f, curPos, SEEK_SET);
    if (ftell(f) != curPos) {
        OE_LOG_ERROR("Failed to get file size");
    }
    return size;
}

bool File::IsExist(const std::string & filename) {
    FILE *f = fopen(filename.data(), "r");
    bool isExist = f ? true : false;
    fclose(f);
    return isExist;
}

}