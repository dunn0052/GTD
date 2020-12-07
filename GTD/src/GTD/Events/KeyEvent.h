#pragma once

#include "Events.h"
#include "../Util/KeyCodes.h"

namespace GTD
{
	class KeyEvent : public Event
	{
	public:
		KeyCode GetKeyCode() const { return keycode; }

		EVENT_CLASS_CATEGORY(CAT_KB | CAT_INP)
	protected:
		KeyEvent(const KeyCode keycode)
			: keycode(keycode) {}

		KeyCode keycode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
			: KeyEvent(keycode), repeatCount(repeatCount) {}

		uint16_t GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keycode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_PRESSED)
	private:
		uint16_t repeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_RELEASED)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_TYPED)
	};
}