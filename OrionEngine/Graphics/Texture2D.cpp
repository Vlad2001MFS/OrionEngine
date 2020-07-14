#include "Texture2D.h"
#include "../Core/Debug.h"
#include "SDL2/SDL_image.h"
#include "glew.h"

namespace oe {

constexpr GLenum gTextureInternalFormats[] = {
    GL_R8,
    GL_RG8,
    GL_RGB8,
    GL_RGBA8,
    GL_ALPHA,
    GL_R16,
    GL_RG16,
    GL_RGB16,
    GL_RGBA16,
    GL_R16F,
    GL_RG16F,
    GL_RGB16F,
    GL_RGBA16F,
    GL_R32F,
    GL_RG32F,
    GL_RGB32F,
    GL_RGBA32F,
    GL_DEPTH_COMPONENT16,
    GL_DEPTH_COMPONENT24,
    GL_DEPTH_COMPONENT32,
    GL_DEPTH24_STENCIL8,
    //GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
    //GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
    //GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
};
constexpr GLenum gTextureExternalFormats[] = {
    GL_RED,
    GL_RG,
    GL_RGB,
    GL_RGBA,
    GL_ALPHA,
    GL_RED,
    GL_RG,
    GL_RGB,
    GL_RGBA,
    GL_RED,
    GL_RG,
    GL_RGB,
    GL_RGBA,
    GL_RED,
    GL_RG,
    GL_RGB,
    GL_RGBA,
    GL_DEPTH_COMPONENT,
    GL_DEPTH_COMPONENT,
    GL_DEPTH_COMPONENT,
    GL_DEPTH_STENCIL,
    //GL_COMPRESSED_RGBA_S3TC_DXT1_EXT,
    //GL_COMPRESSED_RGBA_S3TC_DXT3_EXT,
    //GL_COMPRESSED_RGBA_S3TC_DXT5_EXT,
};
constexpr GLenum gTextureDataTypes[] = {
    GL_UNSIGNED_BYTE,
    GL_UNSIGNED_BYTE,
    GL_UNSIGNED_BYTE,
    GL_UNSIGNED_BYTE,
    GL_UNSIGNED_BYTE,
    GL_UNSIGNED_SHORT,
    GL_UNSIGNED_SHORT,
    GL_UNSIGNED_SHORT,
    GL_UNSIGNED_SHORT,
    GL_FLOAT,
    GL_FLOAT,
    GL_FLOAT,
    GL_FLOAT,
    GL_FLOAT,
    GL_FLOAT,
    GL_FLOAT,
    GL_FLOAT,
    GL_UNSIGNED_SHORT,
    GL_UNSIGNED_INT,
    GL_UNSIGNED_INT,
    GL_UNSIGNED_INT_24_8,
};

Texture2D::Texture2D(const void * data, const glm::ivec2 & size, const TextureFormat format)
    : mTexture(0), mSize(size), mFormat(format) {
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, gTextureInternalFormats[static_cast<uint>(format)], size.x, size.y, 0,
                 gTextureExternalFormats[static_cast<uint>(format)], gTextureDataTypes[static_cast<uint>(format)], data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture2D::Texture2D(const std::string & filename) 
    : mTexture(0), mSize(0, 0), mFormat(TextureFormat::RGBA8) {
    SDL_Surface *img = IMG_Load(filename.data());
    if (!img) {
        OE_LOG_ERROR("Failed to load image '%s'. Error: %s", filename.data(), IMG_GetError());
    }
    TextureFormat fmt;
    if (img->format->BytesPerPixel == 3) {
        fmt = TextureFormat::RGB8;
    }
    else if (img->format->BytesPerPixel == 4) {
        fmt = TextureFormat::RGBA8;
    }
    else {
        OE_LOG_ERROR("Failed to create texture 2d from file '%s'. Supported only RGB or RGBA textures", filename.data());
    }
    uchar *tmpbuf = new uchar[img->pitch];
    uchar *rowhi = (uchar*)img->pixels;
    uchar *rowlo = rowhi + (img->h * img->pitch) - img->pitch;
    for (int i = 0; i<img->h/2; ++i) {
        for (int j = 0; j<img->w; ++j) {
            uchar tmpch = rowhi[j*img->format->BytesPerPixel];
            rowhi[j*img->format->BytesPerPixel] = rowhi[j*img->format->BytesPerPixel+2];
            rowhi[j*img->format->BytesPerPixel+2] = tmpch;
            tmpch = rowlo[j*img->format->BytesPerPixel];
            rowlo[j*img->format->BytesPerPixel] = rowlo[j*img->format->BytesPerPixel+2];
            rowlo[j*img->format->BytesPerPixel+2] = tmpch;
        }
        memcpy(tmpbuf, rowhi, img->pitch);
        memcpy(rowhi, rowlo, img->pitch);
        memcpy(rowlo, tmpbuf, img->pitch);
        rowhi += img->pitch;
        rowlo -= img->pitch;
    }
    OE_SAFE_DELETE_ARRAY(tmpbuf);

    mSize = glm::ivec2(img->w, img->h);
    mFormat = fmt;
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, gTextureInternalFormats[static_cast<uint>(fmt)], img->w, img->h, 0,
                 gTextureExternalFormats[static_cast<uint>(fmt)], gTextureDataTypes[static_cast<uint>(fmt)], img->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    SDL_FreeSurface(img);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &mTexture);
}

uint Texture2D::GetHandle() const {
    return mTexture;
}

const glm::ivec2 & Texture2D::GetSize() const {
    return mSize;
}

TextureFormat Texture2D::GetFormat() const {
    return mFormat;
}

}