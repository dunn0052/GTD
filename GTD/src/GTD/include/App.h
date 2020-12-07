#pragma once

#include "Core.h"
#include "../Util/Utils.h"
#include "Window.h"
#include "WindowsWindow.h"
#include "../Events/AppEvent.h"
#include "LayerStack.h"
#include "../include/Controllers.h"

namespace GTD
{
	class GTD_API App
	{
	public:
		App();

		virtual ~App();
		
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		Scope<Window> m_Window;
		bool m_Running = true;
		LayerStack m_Layertack;
		Scope<Controllers> m_Controllers;
	};

	// to be defined in client
	App* CreateApp();


}

