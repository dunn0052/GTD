#pragma once
#include "RenderCommands.h"
#include "OrthographicCamera.h"
#include "IShader.h"

namespace GTD
{
	class GTD_API Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera); // kind of want to call this begin frame instead
		static void EndScene(); // end frame here as well
		static void Submit(const Ref<IShader>& shader, const Ref<IVertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f)); // will take in a ref to a mesh
		static void Flush();

		static inline IRendererAPI::API GetAPI() { return IRendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
		static const std::string  u_ViewProjectionShaderName;
		static const std::string  u_TransformShaderName;

	};

}


