#include "PCH/PCH.h"


#include "include/Window.h"
#include "include/Core.h"
#include "include/Logger.h"
#include "Util/Utils.h"

#ifdef GTD_PLATFORM_WINDOWS
#include "include/WindowsWindow.h"
#endif

namespace GTD
{
	Scope<IWindow> IWindow::Create(const WindowProps& props)
	{
#ifdef GTD_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		LOG_FATAL("Unknow platform!");
		return nullptr;
#endif
	}

}