#pragma once
#include "PCH/PCH.h"

#include "include/WindowsWindow.h"

#include "include/Logger.h"
#include "Events/AppEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

namespace GTD {

	
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		LOG_WARN("GLFW Error(%d) : %s", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;


		LOG_INFO("Creating window | TITLE: %s | WIDTH:  %d | HEIGHT: %d" , props.Title.c_str(), props.Width, props.Height);
		
		if (s_GLFWWindowCount == 0)
		{
			glwfInitialized = glfwInit();
			GTD_ASSERT(glwfInitialized, "Could not init GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}


		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		// set where to render
		++s_GLFWWindowCount;

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		
		// Set GLFW callbacks

		// when the window is reisized
		glfwSetWindowSizeCallback(m_Window, 
			[](GLFWwindow* window, int width, int height)
			{
				// get pointer to window struct
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				//set that data
				data.Width = width;
				data.Height = height;

				// create event callback
				WindowResizeEvent resize_event(width, height);
				
				// do callback that we just created
				data.EventCallback(resize_event);
			}
		);

		glfwSetWindowCloseCallback(m_Window, 
			[](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent close_event;
				data.EventCallback(close_event);
			}
		);
		
		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent key_event(key, 0);
					data.EventCallback(key_event);
					break;
				}
				case GLFW_RELEASE:
				{					
					KeyReleasedEvent key_event(key);
					data.EventCallback(key_event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent key_event(key, 1);
					data.EventCallback(key_event);
					break;
				}
				}
			}
			);

		glfwSetMouseButtonCallback(m_Window,
			[](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent mouse_event(button);
					data.EventCallback(mouse_event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent mouse_event(button);
					data.EventCallback(mouse_event);
					break;
				}
				}
			}
		);

		glfwSetScrollCallback(m_Window,
			[](GLFWwindow* window, double x_offset, double y_offset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent mouse_event((float)x_offset, (float)y_offset);
				data.EventCallback(mouse_event);
			}
		);

		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double x_position, double y_position)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent mouse_event((float)x_position, (float)y_position);
			data.EventCallback(mouse_event);
		}
		);
	}

	void WindowsWindow::Shutdown()
	{

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
