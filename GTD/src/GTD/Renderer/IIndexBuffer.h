#pragma once
#include "../include/Core.h"

namespace GTD
{
	class GTD_API IIndexBuffer
	{
	public:
		virtual ~IIndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IIndexBuffer* Create(uint32_t* indices, uint32_t size);
	};
}