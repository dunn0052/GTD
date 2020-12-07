#include <GTD.h>

class ExampleLayer : public GTD::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		//LOG_INFO("%s", m_DebugName.c_str());
	}

	void OnEvent(GTD::Event& e) override
	{
		LOG_DEBUG("%s", e.ToString().c_str());
	}
};

class Sandbox : public GTD::App
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

GTD::App* GTD::CreateApp()
{
	return new Sandbox();
}