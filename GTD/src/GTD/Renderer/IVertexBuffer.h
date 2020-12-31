#pragma once
#include "BufferLayout.h"

namespace GTD
{
	class GTD_API IVertexBuffer
	{
	public:
		virtual ~IVertexBuffer() {}

		virtual void Bind()  const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual void SetData(const void* data, uint32_t size) = 0;

		static IVertexBuffer* Create(uint32_t size);
		static IVertexBuffer* Create(float* indices, uint32_t size); // switch to Ref too
	};
}