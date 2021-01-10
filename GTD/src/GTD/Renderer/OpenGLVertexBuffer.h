#pragma once
#include "IVertexBuffer.h"

namespace GTD
{
	class OpenGLVertexBuffer : public IVertexBuffer
	{
	public:
		GTD_API OpenGLVertexBuffer(uint32_t size);
		GTD_API OpenGLVertexBuffer(float* vertices, uint32_t size);
		GTD_API virtual ~OpenGLVertexBuffer();

		GTD_API virtual void Bind() const override;
		GTD_API virtual void Unbind() const override;

		GTD_API virtual inline const BufferLayout& GetLayout() const override { return m_Layout; }
		GTD_API virtual inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		GTD_API virtual void SetData(const void* data, uint32_t size) override;

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
}

