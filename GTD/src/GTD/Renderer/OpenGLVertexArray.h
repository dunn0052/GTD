#pragma once
#include "IVertexArray.h"

namespace GTD
{
	class GTD_API OpenGLVertexArray : public IVertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind()  const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer) override;
		virtual void AddIndexBuffer(const Ref<IIndexBuffer>& indexBuffer) override;
		virtual std::vector<Ref<IVertexBuffer>> GetVertexBuffer() const { return m_VertexBuffers; };
		virtual Ref<IIndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; };

	private:
		std::vector<Ref<IVertexBuffer>> m_VertexBuffers;
		Ref<IIndexBuffer> m_IndexBuffer;
		unsigned int m_RendererID;
	};
}


