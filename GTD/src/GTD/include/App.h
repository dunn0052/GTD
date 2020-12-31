#pragma once

#include "Core.h"
#include "../Util/Utils.h"
#include "Window.h"
#include "WindowsWindow.h"
#include "../Events/AppEvent.h"
#include "LayerStack.h"
#include "../include/Controllers.h"
#include "../Renderer/IShader.h"
#include "../Renderer/IIndexBuffer.h"
#include "../Renderer/IVertexBuffer.h"
#include "../Renderer/IVertexArray.h"
#include "../Renderer/RenderCommands.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/OrthographicCamera.h"
#include "../include/Timestep.h"

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
		bool OnWindowResize(WindowResizeEvent& e);

		/* Window */
		Scope<IWindow> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime;
	};

	// To be defined in client
	App* CreateApp();


}

