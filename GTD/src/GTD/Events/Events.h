#pragma once
//#include "../PCH/PCH.h"
#include "../include/Core.h"
#include "../include/Logger.h"

namespace GTD
{
	enum class EventType
	{
		NONE,
		WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LIST_FOCUS, WINDOWMOVED,
		APP_TICK, APP_UPDATE, APP_RENDER,
		KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
		MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVE, MOUSE_SCROLLED,
		JOY_CONNECTED, JOY_DISCONNECTED, JOY_BUTTON_PRESSED, JOY_STICK_MOVE
	};


	// Filter events
	enum EventCategory
	{
		None = 0,
		CAT_APP = MAKE_BIT(0), // resize, close, etc..
		CAT_INP= MAKE_BIT(1), // input from user
		CAT_KB = MAKE_BIT(2), // keyboard
		CAT_MOUSE_MOVE = MAKE_BIT(3),
		CAT_MOUSE_BUT = MAKE_BIT(4),
		CAT_JOY_STICK = MAKE_BIT(5),
		CAT_JOY_BUT = MAKE_BIT(6),
		CAT_JOY_CON = MAKE_BIT(7) // joysitck connect or disconnect
	};

	// save writing all of this for each event type
#define EVENT_CLASS_TYPE( TYPE ) static EventType GetStaticType() { return EventType::TYPE; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #TYPE; }

#define EVENT_CLASS_CATEGORY( CATEGORY ) virtual int GetCategoryFlags() const override { return CATEGORY; }

	class Event
	{
	public:
		GTD_API virtual ~Event() = default;

		bool Handled = false;

		GTD_API virtual EventType GetEventType() const = 0;
		GTD_API virtual const char* GetName() const = 0;
		GTD_API virtual int GetCategoryFlags() const = 0;
		GTD_API virtual std::string ToString() const { return GetName(); }

		GTD_API bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				event.Handled |= func(static_cast<T&>(event));
				return true;
			}
			return false;
		}
	private:
		Event& event;
	};

	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}
