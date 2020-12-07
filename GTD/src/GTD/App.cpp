#include "../PCH.h"

#include "include/App.h"
#include "include/Logger.h"

namespace GTD
{
#define BIND_EVENT_FTN( FUNCTION ) std::bind(&App::FUNCTION, this, std::placeholders::_1)

	App::App()
	{
		m_Window = WindowsWindow::Create();
		m_Window->SetEventCallback(BIND_EVENT_FTN(OnEvent));

		m_Controllers = CreateScope<Controllers>();
	}

	App::~App()
	{

	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		LOG_DEBUG("%s", e.ToString().c_str());
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FTN(OnWindowClose));

		// Go backwards to do events based on first layer shown that should access the event
		for (auto it = m_Layertack.end(); it != m_Layertack.begin(); )
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
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			/* do layer stuff here */
			for (Layer* layer : m_Layertack)
			{
				layer->OnUpdate();
			}
			/* end layer stuff */

			m_Controllers->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	void App::PushLayer(Layer* layer)
	{
		m_Layertack.PushLayer(layer);
	}

	void App::PushOverlay(Layer* overlay)
	{
		m_Layertack.PushOverlay(overlay);
	}

}