#pragma once
#include "../Util/Utils.h"
#include "ContextCodes.h"
#include <unordered_map>

namespace GTD
{
	enum class GTD_API PRESS_TYPE
	{
		OFF,
		PRESSED,
		HELD,
		RELEASED
	};

	constexpr unsigned char	BUTTON_OFF = 0x0; // !current & ~previous
	constexpr unsigned char	BUTTON_RELEASED = 0x1; // ~current & previous
	constexpr unsigned char	BUTTON_PRESSED = 0x2; // current & ~previous 
	constexpr unsigned char	BUTTON_HELD = 0x3; // current & previous

	struct GTD_API Button
	{
		Button(ContextCode code)
			: m_Code(code), m_Status(BUTTON_OFF)
		{
		}
	public:
		ContextCode Code() const { return m_Code; }
		unsigned char m_Status;
	private:
		ContextCode m_Code;
	};

	static std::unordered_map<ContextCode, Button> buttonMap =
	{
		{ContextCode::X, Button(ContextCode::X)},
		{ContextCode::B, Button(ContextCode::B)},
		{ContextCode::A, Button(ContextCode::A)},
		{ContextCode::Y, Button(ContextCode::Y)},
		{ContextCode::LB, Button(ContextCode::LB)},
		{ContextCode::RB, Button(ContextCode::RB)},
		{ContextCode::LT, Button(ContextCode::LT)},
		{ContextCode::RT, Button(ContextCode::RT)},
		{ContextCode::BACK, Button(ContextCode::BACK)},
		{ContextCode::START, Button(ContextCode::START)},
		{ContextCode::LSB, Button(ContextCode::LSB)},
		{ContextCode::RSB, Button(ContextCode::RSB)},
		{ContextCode::UP, Button(ContextCode::UP)},
		{ContextCode::RIGHT, Button(ContextCode::RIGHT)},
		{ContextCode::DOWN, Button(ContextCode::DOWN)},
		{ContextCode::LEFT, Button(ContextCode::LEFT)},
	};
}