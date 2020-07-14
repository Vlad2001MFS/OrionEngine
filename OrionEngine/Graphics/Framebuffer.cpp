#include "Framebuffer.h"
#include "../Core/Debug.h"
#include "glew.h"

namespace oe {

FramebufferAttachment::FramebufferAttachment(const glm::ivec2 & size, const TextureFormat format)
    : size(size), format(format){ }

Framebuffer::Framebuffer(const std::vector<FramebufferAttachment>& attachments) : mFramebuffer(0), mAttachments(attachments), mDepthStencil(nullptr) {
    if (!attachments.empty() && attachments.size() <= 8) {
        glGenFramebuffers(1, &mFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
        uint i = 0;
        for (const auto &attachment : attachments) {
            if (attachment.format == TextureFormat::D16 || attachment.format == TextureFormat::D24 || 
                attachment.format == TextureFormat::D24S8 || attachment.format == TextureFormat::D32) {
                if (mDepthStencil) {
                    OE_LOG_ERROR("More than 1 depth stencil in framebuffer");
                }
                else {
                    mDepthStencil = new Texture2D(nullptr, attachment.size, attachment.format);
                    if (attachment.format == TextureFormat::D24S8) {
                        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mDepthStencil->GetHandle(), 0);
                    }
                    else {
                        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthStencil->GetHandle(), 0);
                    }
                }
            }
            else {
                mRenderTargets.push_back(new Texture2D(nullptr, attachment.size, attachment.format));
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mRenderTargets.back()->GetHandle(), 0);
                i++;
            }
        }
        switch (glCheckFramebufferStatus(GL_FRAMEBUFFER)) {
            case GL_FRAMEBUFFER_COMPLETE_EXT:
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
                OE_LOG_ERROR("Framebuffer incomplete attachment");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
                OE_LOG_ERROR("Framebuffer incomplete missing attachment");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
                OE_LOG_ERROR("Framebuffer incomplete dimensions");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
                OE_LOG_ERROR("Framebuffer incomplete formats");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
                OE_LOG_ERROR("Framebuffer incomplete draw buffer");
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
                OE_LOG_ERROR("Framebuffer incomplete read buffer");
                break;
            case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
                OE_LOG_ERROR("Framebuffer unsuported");
                break;
        }
    }
    else {
        OE_LOG_ERROR("Framebuffer empty or have more than 8 attachments");
    }
}

Framebuffer::~Framebuffer() {
    glDeleteFramebuffers(1, &mFramebuffer);
    OE_SAFE_DELETE(mDepthStencil);
    for (auto &renderTarget : mRenderTargets) {
        OE_SAFE_DELETE(renderTarget);
    }
}

uint Framebuffer::GetHandle() const {
    return mFramebuffer;
}

const std::vector<FramebufferAttachment>& Framebuffer::GetAttachments() const {
    return mAttachments;
}

const std::vector<Texture2D*>& Framebuffer::GetRenderTargets() const {
    return mRenderTargets;
}

const Texture2D * Framebuffer::GetDepthStencil() const {
    return mDepthStencil;
}

}