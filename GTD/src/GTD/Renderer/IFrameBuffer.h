#pragma once
#include "../include/Core.h"
#include "../Util/Utils.h"
#include "../include/Logger.h"

namespace GTD
{
	struct FrameBufferProps
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	// This really should be called surface ?
	class GTD_API IFrameBuffer
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual FrameBufferProps& GetProps() = 0;
		virtual const FrameBufferProps& GetProps() const = 0;

		static Ref<IFrameBuffer> Create(const FrameBufferProps& props);
	};
}