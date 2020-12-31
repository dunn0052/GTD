#pragma once
#include "Core.h"

namespace GTD
{
	/* Set numbers since they will map with array indices and I want to be careful */
	enum ContextCode : size_t
	{
		NONE = -1,
		X = 0,
		B = 1,
		A = 2,
		Y = 3,
		LB = 4,
		RB = 5,
		LT = 6,
		RT = 7,
		BACK = 8,
		START = 9,
		LSB = 10,
		RSB = 11,
		UP = 12,
		RIGHT = 13,
		DOWN = 14,
		LEFT = 15
	};

	enum ContextAxis : size_t
	{
		LX = 0,
		LY = 1,
		RX = 2,
		RY = 3
	};
}
