#include <GTD.h>
#include "GTD/Renderer/OpenGLShader.h"
#include "../inlucde/Layer2D.h"

#include "GTD/include/EntryPoint.h"

#include "../../Vendor/glm/gtc/matrix_transform.hpp"

class ExampleLayer : public GTD::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.f / 720.0f, m_DT, true), m_Controllers()
	{
		m_VertexArray = GTD::IVertexArray::Create();

		// triangle
		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f,/*color*/ 0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f,/*color*/ 0.2f, 0.3f, 0.8f, 1.0f,
			0.0f, 0.5f, 0.0f,/*color*/ 0.8f, 0.8f, 0.2f, 1.0f
		};

		// /*color*/ 1.0f, 0.0f, 1.0f, 1.0f
		GTD::Ref<GTD::IVertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(GTD::IVertexBuffer::Create(vertices, sizeof(vertices)));

		GTD::BufferLayout layout =
		{
			{ GTD::ShaderDataType::FLOAT3, "a_Position" },
			{ GTD::ShaderDataType::FLOAT4, "a_Color"}
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		m_SVertexArray = GTD::IVertexArray::Create();

		GTD::Ref<GTD::IIndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(GTD::IIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->AddIndexBuffer(m_IndexBuffer);

		float squareVertices[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // top left
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom left
			0.5f, 0.5, 0.0f, 1.0f, 1.0f, // top right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f // bottom right
		};

		GTD::Ref<GTD::IVertexBuffer> squareVBuffer;
		squareVBuffer.reset(GTD::IVertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVBuffer->SetLayout({
			{ GTD::ShaderDataType::FLOAT3, "a_Position" },
			{GTD::ShaderDataType::FLOAT2, "a_TexCoord"}
			});
		m_SVertexArray->AddVertexBuffer(squareVBuffer);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		GTD::Ref<GTD::IIndexBuffer> squareIBuffer;
		squareIBuffer.reset(GTD::IIndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SVertexArray->AddIndexBuffer(squareIBuffer);

		std::string vertexSrc =
			R"(
		#version 410 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec4 a_Color;
			
		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec3 v_Position;
		out vec4 v_Color;

		void main()
		{
			v_Position = a_Position;
			v_Color = a_Color;

			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}

	)";

		std::string fragmentSrc =

			R"(
		#version 410 core

		layout(location = 0) out vec4 o_Color;

		in vec3 v_Position;
		in vec4 v_Color;
		
		uniform vec4 u_Color;		

		void main()
		{
			o_Color = u_Color;
		}

	)";

		m_Shader = GTD::IShader::Create("triangleShader" ,vertexSrc, fragmentSrc);

		std::string texVertexSrc =
			R"(
		#version 410 core

		layout(location = 0) in vec3 a_Position;
		layout(location = 1) in vec2 a_TexCoord;
			
		uniform mat4 u_ViewProjection;
		uniform mat4 u_Transform;

		out vec2 v_TexCoord;

		void main()
		{
			v_TexCoord = a_TexCoord;

			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}

	)";

		std::string texFragmentSrc =

			R"(
		#version 410 core

		layout(location = 0) out vec4 o_Color;

		in vec2 v_TexCoord;

		uniform sampler2D u_Texture;		

		void main()
		{
			o_Color = texture(u_Texture,  v_TexCoord);
		}

	)";

		//m_TexShader = GTD::IShader::Create("assets/shaders/Texture.shdr");

		auto texShader = m_ShaderLibrary.Load("assets/shaders/Texture.shdr");

		m_Texture = (GTD::ITexture2D::Create("assets/images/mariot.png"));

		texShader->Bind();
		texShader->UploadUniform("u_Texture", 0);

	}

	void OnUpdate(const GTD::Ref<GTD::Timestep>& dt) override
	{


	}

	void OnEvent(GTD::Event& e) override
	{
		m_CameraController.OnEvent(e);
		//GTD::EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<GTD::KeyPressedEvent>(BIND_EVENT_FTN(ExampleLayer::OnKeyPressedEvent));
	}

private:
	/* Rendering */
	GTD::ShaderLibrary m_ShaderLibrary;

	GTD::Ref<GTD::IVertexArray> m_VertexArray;
	GTD::Ref<GTD::IShader> m_Shader;

	GTD::Ref<GTD::IVertexArray> m_SVertexArray;

	GTD::Ref<GTD::ITexture2D> m_Texture;

	GTD::OrthographicCameraController m_CameraController;

	glm::vec3 m_Position;
	float m_Rotate = 0.0f;
	float m_MoveSpeed = 1.0f;
	float m_RotateSpeed = 20.0f;


	/* Controllers */
	GTD::Controllers m_Controllers;
};

class Sandbox : public GTD::App
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Layer2D());
	}

	~Sandbox()
	{

	}
};

GTD::App* GTD::CreateApp()
{
	return new Sandbox();
}
