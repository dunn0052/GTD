#include "../PCH/PCH.h"
#include "OpenGLContext.h"
#include "../include/Logger.h"

#include <glfw3.h>

namespace GTD
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		GTD_ASSERT(nullptr != m_WindowHandle, "Window handle is NULL!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GTD_ASSERT(status, "Failed to initialize GLAD!");

		LOG_INFO("OpenGL Version %s", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}