#pragma once
#include "ContextCodes.h"

#include <unordered_map>

namespace GTD
{
	const static char* XboxButtonMappings[16] =
	{
		"X", "B", "A", "Y",
		"LB", "RB",
		"LT", "RT",
		"BACK", "START",
		"LSB", "RSB",
		"UP", "RIGHT", "DOWN", "LEFT"
	};

	const static char* XboxAxisMappings[4]
	{
		"LX", "LY",
		"RX", "RY"
	};

	const static char* SNESButtonMappings[16] =
	{
		"X", "B", "A", "Y",
		"LB", "RB",
		"L??", "R??",
		"BACK", "START"
	};

	const static char* SNESAxisMappings[4]
	{
		"DX", "DY",
	};

	/* array index matches with button index */
	const static ContextCode XboxCode[16] =
	{
		ContextCode::X,
		ContextCode::B,
		ContextCode::A,
		ContextCode::Y,
		ContextCode::LB,
		ContextCode::RB,
		ContextCode::LT,
		ContextCode::RT,
		ContextCode::BACK,
		ContextCode::START,
		ContextCode::LSB,
		ContextCode::RSB,
		ContextCode::UP,
		ContextCode::RIGHT,
		ContextCode::DOWN,
		ContextCode::LEFT,
	};

	const static ContextAxis XboxAxis[4] =
	{
		ContextAxis::LX,
		ContextAxis::LY,
		ContextAxis::RX,
		ContextAxis::RY,
	};

	const static ContextCode SNESButtons[10]
	{
		ContextCode::X,
		ContextCode::B,
		ContextCode::A,
		ContextCode::Y,
		ContextCode::LB,
		ContextCode::RB,
		ContextCode::NONE, // not sure what the nones map to..?
		ContextCode::NONE,
		ContextCode::BACK,
		ContextCode::START
	};

	const static ContextAxis SNESAxis[2] =
	{
		ContextAxis::LX,
		ContextAxis::RX
	};
}
