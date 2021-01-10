#pragma once
#include "IVertexArray.h"

namespace GTD
{
	class OpenGLVertexArray : public IVertexArray
	{
	public:
		GTD_API OpenGLVertexArray();
		GTD_API ~OpenGLVertexArray();

		GTD_API virtual void Bind()  const override;
		GTD_API virtual void Unbind() const override;

		GTD_API virtual void AddVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer) override;
		GTD_API virtual void AddIndexBuffer(const Ref<IIndexBuffer>& indexBuffer) override;
		GTD_API virtual std::vector<Ref<IVertexBuffer>> GetVertexBuffer() const { return m_VertexBuffers; };
		GTD_API virtual Ref<IIndexBuffer> GetIndexBuffer() const { return m_IndexBuffer; };

	private:
		std::vector<Ref<IVertexBuffer>> m_VertexBuffers;
		Ref<IIndexBuffer> m_IndexBuffer;
		unsigned int m_RendererID;
	};
}


