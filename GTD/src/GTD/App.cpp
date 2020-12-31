#include "PCH/PCH.h"

#include "include/App.h"
#include "include/Logger.h"

namespace GTD
{
	App::App()
	{

		m_Window = WindowsWindow::Create();
		m_Window->SetEventCallback(BIND_EVENT_FTN(App::OnEvent));

		Renderer::Init();
	}

	App::~App()
	{

	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//LOG_DEBUG("%s", e.ToString().c_str());
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FTN(App::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FTN(App::OnWindowResize));

		// Go backwards to do events based on first layer shown that should access the event
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void App::Run()
	{
		while (m_Running)
		{
			float time = (float)glfwGetTime(); // should be platform independent
			Timestep dt = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				/* do layer stuff here */
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(dt);
				}
				/* end layer stuff */
			}

			m_Window->OnUpdate();
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool App::OnWindowResize(WindowResizeEvent& e)
	{
		uint32_t width = e.GetWidth();
		uint32_t height = e.GetHeight();
		if (0 == e.GetWidth() || 0 == e.GetHeight())
		{
			m_Minimized = true;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(width, height);

		LOG_INFO("RESIZED: WIDTH %u | HEIGHT %u", width, height);
		return false;
	}

	void App::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void App::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

}