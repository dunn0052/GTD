#include "../PCH/PCH.h"
#include "Renderer.h"
#include "../Util/Utils.h"
#include "OpenGLShader.h"
#include "Renderer2D.h"

namespace GTD
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const Ref<IShader>& shader, const Ref<IVertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->UploadUniform(u_ViewProjectionShaderName, m_SceneData->ViewProjectionMatrix);

		shader->UploadUniform(u_TransformShaderName, transform);
	}

	void Renderer::Flush()
	{

	}

	/* Shader Uniforms -- should be in shader class IMO */
	const std::string  Renderer::u_ViewProjectionShaderName = "u_ViewProjection";
	const std::string  Renderer::u_TransformShaderName = "u_Transform";
}