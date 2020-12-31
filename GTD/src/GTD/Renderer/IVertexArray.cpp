#include "../PCH/PCH.h"
#include "IVertexArray.h"
#include "Renderer.h"
#include "OpenGLVertexArray.h"

namespace GTD
{
	Ref<IVertexArray> IVertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case IRendererAPI::API::OPENGL:
			return CreateRef<OpenGLVertexArray>();
		case IRendererAPI::API::NONE:
			GTD_ASSERT(false, "RendererAPI::NONE is currently not supported!");
			return nullptr;
		}

		GTD_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
