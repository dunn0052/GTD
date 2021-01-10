#pragma once
#include "Window.h"
#include "../Util/Utils.h"
#include "../Renderer/OpenGLContext.h"

#include <glfw3.h>

namespace GTD {

	class WindowsWindow : public IWindow
	{
	public:
		GTD_API WindowsWindow(const WindowProps& props);
		GTD_API virtual ~WindowsWindow();

		GTD_API void OnUpdate() override;

		GTD_API unsigned int GetWidth() const override { return m_Data.Width; }
		GTD_API unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		GTD_API void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		GTD_API void SetVSync(bool enabled) override;
		GTD_API bool IsVSync() const override;

		GTD_API virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		IContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
		int glwfInitialized;
	};

}