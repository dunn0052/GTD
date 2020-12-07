#pragma once

namespace GTD
{
	template<int A, int B>
	struct ControllerProps
	{
		ControllerProps() 
			: ID(0), connected(false), 
			m_numAxis(A), m_numButtons(B),
			m_axis{0}, m_buttons{0}
		{
		}

		uint32_t ID;
		bool connected;

		/* info */
		int m_numAxis;
		float m_axis[A];
		float m_axisCenteringEpsilon[A];

		int m_numButtons;
		unsigned char m_buttons[B];

		/*
		* Could use hats eventually
		* int m_numHats;
		* unsigned char m_hats[H];
		*/
	};

	/* deadzone for controller centering 
	*              C
	*  |---------|E|E|---------|
	*/
	const static float axisOffsetEpsilon = 5 * pow(10, -5);

	/* controller implementation */
	const static char* XboxButtonMappings[16] =
	{
		"X", "B", "A", "Y",
		"LB", "RB",
		"LT", "RT", 
		"BACK", "START", 
		"LSB", "RSB", 
		"UP", "RIGHT", "DOWN", "LEFT"
	};

	using XboxController = ControllerProps <6, 14>;
}
