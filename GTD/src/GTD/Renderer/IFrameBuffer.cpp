#include "../PCH/PCH.h"
#include "IFrameBuffer.h"
#include "Renderer.h"
#include "OpenGLFrameBuffer.h"

namespace GTD
{
    Ref<IFrameBuffer> IFrameBuffer::Create(const FrameBufferProps& props)
    {
		switch (Renderer::GetAPI())
		{
		case IRendererAPI::API::OPENGL:
		{
			return CreateRef<OpenGLFrameBuffer>(props);
		}
		case IRendererAPI::API::NONE:
		default:
		{
			LOG_WARN("Renderer not found");
			GTD_ASSERT(false, "");
		}
		}

		return nullptr;
    }
}
