#pragma once
#include "IVertexBuffer.h"

namespace GTD
{
	class GTD_API OpenGLVertexBuffer : public IVertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual inline const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		virtual void SetData(const void* data, uint32_t size) override;

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
	};
}

