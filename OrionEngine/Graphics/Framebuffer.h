#pragma once
#include "../Core/Common.h"
#include "../Graphics/Texture2D.h"
#include <vector>

namespace oe {

struct FramebufferAttachment {
    FramebufferAttachment(const glm::ivec2 &size, const TextureFormat format);

    glm::ivec2 size;
    TextureFormat format;
};

class Framebuffer {
public:
    Framebuffer(const std::vector<FramebufferAttachment> &attachments);
    ~Framebuffer();

    uint GetHandle() const;
    const std::vector<FramebufferAttachment> &GetAttachments() const;
    const std::vector<Texture2D*> &GetRenderTargets() const;
    const Texture2D *GetDepthStencil() const;

private:
    uint mFramebuffer;
    std::vector<FramebufferAttachment> mAttachments;
    std::vector<Texture2D*> mRenderTargets;
    Texture2D *mDepthStencil;
};

}