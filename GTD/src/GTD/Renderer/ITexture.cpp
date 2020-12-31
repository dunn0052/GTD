#include "../PCH/PCH.h"
#include "ITexture.h"

#include "Renderer.h"
#include "OpenGLTexture.h"

namespace GTD
{
	Ref<ITexture2D> ITexture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
		case IRendererAPI::API::OPENGL:
		{
			return CreateRef<OpenGLTexture2D>(width, height);
		}
		case IRendererAPI::API::NONE:
		default:
		{
			GTD_ASSERT(false, "Renderer not found");
		}
		}

		return nullptr;
	}

	Ref<ITexture2D> GTD::ITexture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case IRendererAPI::API::OPENGL:
			{
				return CreateRef<OpenGLTexture2D>(path);
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
