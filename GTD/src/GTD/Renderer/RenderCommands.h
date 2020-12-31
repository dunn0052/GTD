#pragma once
#include "IRendererAPI.h"

namespace GTD
{
	class GTD_API RenderCommand
	{
	public:

		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void DrawIndexed(const Ref<IVertexArray>& vertexArray, uint32_t count)
		{
			s_RendererAPI->DrawIndexed(vertexArray, count);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

	private:
		static IRendererAPI* s_RendererAPI;
	};
}