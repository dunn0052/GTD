#include "../PCH/PCH.h"
#include "IIndexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "Renderer.h"
#include "../include/Logger.h"

namespace GTD
{
	
	IIndexBuffer* IIndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case IRendererAPI::API::OPENGL:
			{
				return new OpenGLIndexBuffer(indices, count);
			}
		case IRendererAPI::API::NONE:
			default:
			{
				GTD_ASSERT(false, "Renderer not found");
			}
		}

		return nullptr;
	}
}