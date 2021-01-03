#pragma once
#include "IFrameBuffer.h"

namespace GTD
{
	class OpenGLFrameBuffer : public IFrameBuffer
	{
	public:
		OpenGLFrameBuffer(const FrameBufferProps& props);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }

		virtual const FrameBufferProps& GetProps() const override { return m_Props; }
		virtual FrameBufferProps& GetProps() { return m_Props; }

	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FrameBufferProps m_Props;
	};
}