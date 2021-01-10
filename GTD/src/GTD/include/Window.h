#pragma once

#include "../Events/Events.h"
#include "Core.h"

namespace GTD {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;

		WindowProps(const std::string& title = "GTD Engine",
			uint32_t width = 1280,
			uint32_t height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class IWindow
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		GTD_API virtual ~IWindow() = default;

		GTD_API virtual void OnUpdate() = 0;

		GTD_API virtual uint32_t GetWidth() const = 0;
		GTD_API virtual uint32_t GetHeight() const = 0;

		// Window attributes
		GTD_API virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		GTD_API virtual void SetVSync(bool enabled) = 0;
		GTD_API virtual bool IsVSync() const = 0;

		GTD_API virtual void* GetNativeWindow() const = 0;

		GTD_API static std::unique_ptr<IWindow> Create(const WindowProps& props = WindowProps());
		//GTD_API static Scope<Window> Create(const WindowProps& props = WindowProps());
	};

}