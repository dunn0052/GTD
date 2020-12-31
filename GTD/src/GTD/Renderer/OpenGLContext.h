#pragma once

#include "IContext.h"

struct GLFWwindow;

namespace GTD
{
	class GTD_API OpenGLContext : public IContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}