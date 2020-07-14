#pragma once
#include "../Core/Common.h"
#include "glm/glm.hpp"
#include <string>

namespace oe {

enum class TextureFormat {
    R8,
    RG8,
    RGB8,
    RGBA8,
    A8,
    R16,
    RG16,
    RGB16,
    RGBA16,
    R16F,
    RG16F,
    RGB16F,
    RGBA16F,
    R32F,
    RG32F,
    RGB32F,
    RGBA32F,
    D16,
    D24,
    D32,
    D24S8,
    //DXT1,
    //DXT3,
    //DXT5
};

class Texture2D {
public:
	Texture2D(const void * data, const glm::ivec2 &size, const TextureFormat format);
    Texture2D(const std::string &filename);
	~Texture2D();

    uint GetHandle() const;
    const glm::ivec2 &GetSize() const;
    TextureFormat GetFormat() const;

private:
    uint mTexture;
    glm::ivec2 mSize;
    TextureFormat mFormat;
};

}