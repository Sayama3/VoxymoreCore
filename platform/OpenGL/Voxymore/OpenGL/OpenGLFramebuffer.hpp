//
// Created by ianpo on 21/08/2023.
//

#pragma once

#include "Voxymore/Renderer/Framebuffer.hpp"

namespace Voxymore::Core {

    class OpenGLFramebuffer : public Framebuffer {
    private:
        FramebufferSpecification m_Specification;
        uint32_t m_RendererID = 0;
		std::vector<uint32_t> m_ColorAttachments;
		uint32_t m_DepthAttachment = 0;
		std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;
    private:
        void Invalidate();
    public:
        OpenGLFramebuffer(const FramebufferSpecification& specification);
        virtual ~OpenGLFramebuffer() override;
        virtual const FramebufferSpecification& GetSpecification() const override;

        virtual void Bind() override;
        virtual void Unbind() override;
        virtual void Resize(uint32_t width, uint32_t height) override;
        virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override;
        virtual uint32_t GetDepthAttachmentRendererID() const override;
    };

} // Voxymore
// Core
