#pragma once
#include "RenderCommands.h"
#include "OrthographicCamera.h"
#include "IShader.h"

namespace GTD
{
	class Renderer
	{
	public:
		GTD_API static void Init();
		GTD_API static void OnWindowResize(uint32_t width, uint32_t height);

		GTD_API static void BeginScene(OrthographicCamera& camera); // kind of want to call this begin frame instead
		GTD_API static void EndScene(); // end frame here as well
		GTD_API static void Submit(const Ref<IShader>& shader, const Ref<IVertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f)); // will take in a ref to a mesh
		GTD_API static void Flush();

		GTD_API static inline IRendererAPI::API GetAPI() { return IRendererAPI::GetAPI(); }

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


