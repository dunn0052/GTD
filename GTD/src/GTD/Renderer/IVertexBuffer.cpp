#include "../PCH/PCH.h"
#include "IVertexBuffer.h"
#include "OpenGLVertexBuffer.h"
#include "Renderer.h"
#include "../include/Logger.h"

namespace GTD
{
	IVertexBuffer* IVertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case IRendererAPI::API::OPENGL:
		{
			return new OpenGLVertexBuffer(size);
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


	IVertexBuffer* IVertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case IRendererAPI::API::OPENGL:
			{
				return new OpenGLVertexBuffer(vertices, size);
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