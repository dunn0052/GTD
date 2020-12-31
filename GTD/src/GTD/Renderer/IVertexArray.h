#pragma once
#include "IVertexBuffer.h"
#include "IIndexBuffer.h"
#include "../Util/Utils.h"

namespace GTD
{
	class GTD_API IVertexArray
	{
	public:
		virtual ~IVertexArray() {}

		virtual void Bind()  const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Ref<IVertexBuffer>& vertexBuffer) = 0;
		virtual void AddIndexBuffer(const Ref<IIndexBuffer>& indexBuffer) = 0;
		virtual std::vector<Ref<IVertexBuffer>> GetVertexBuffer() const = 0;
		virtual Ref<IIndexBuffer> GetIndexBuffer() const = 0;

		static Ref<IVertexArray> Create();
	};
}

