#include "../PCH/PCH.h"
#include "../include/Logger.h"
#include "IShader.h"
#include "Renderer.h"
#include "OpenGLShader.h"

namespace GTD
{
	Ref<IShader> IShader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case IRendererAPI::API::OPENGL:
		{
			return CreateRef<OpenGLShader>(filePath);
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
	Ref<IShader> IShader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case IRendererAPI::API::OPENGL:
		{
			return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
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