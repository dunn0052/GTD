#pragma once

#include "Events.h"
#include "../Util/JoypadCodes.h"

namespace GTD
{
	class JoypadConnectedEvent : public Event
	{
	public:
		JoypadConnectedEvent(int id) : joypad_id(id)
		{

		}

		int GetID() const { return joypad_id; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "JoypadConnectedEvent: " << joypad_id;
			return ss.str();
		}

		EVENT_CLASS_TYPE(JOY_CONNECTED);

		EVENT_CLASS_CATEGORY(CAT_JOY_CON | CAT_INP)

	private:
		// Can by char since its only 16 total. Only need half char
		int joypad_id;
	};
	class JoypadJoystickEvent : public Event
	{
	public:
		JoypadJoystickEvent(const float x, const float y)
			: stickX(x), stickY(y) {}
		float GetX() const { return stickX; }
		float GetY() const { return stickY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "JoypadJoysticEvent: " << stickX << ", " << stickY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(JOY_STICK_MOVE)

		EVENT_CLASS_CATEGORY(CAT_JOY_STICK | CAT_INP)

	private:
		float stickX, stickY;
	};

}