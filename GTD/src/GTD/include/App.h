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

	class App
	{
	public:
		GTD_API App();

		GTD_API virtual ~App();
		
		GTD_API void Run();

		GTD_API void OnEvent(Event& e);

		GTD_API void PushLayer(Layer* layer);
		GTD_API void PushOverlay(Layer* layer);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		/* Window */
		Scope<IWindow> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime;
		Ref<Timestep> m_DT;
	};

	// To be defined in client
	App* CreateApp();
}

