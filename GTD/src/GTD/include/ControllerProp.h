#pragma once
#include "ControllerCodes.h"

namespace GTD
{
	template<int A, int B>
	struct GTD_API ControllerProps
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
		/* distance from axis center to consider not moved */
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
	const static float axisOffsetEpsilon = static_cast<float>(5 * pow(10, -5));

	/* controller implementations */
	using XboxController = ControllerProps<4, 16>;

	using SNESController = ControllerProps<2, 10>;
}
