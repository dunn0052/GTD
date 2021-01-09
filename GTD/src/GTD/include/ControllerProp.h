#pragma once
#include "ControllerCodes.h"
#include "Button.h"
#include <unordered_set>

namespace GTD
{
	template<int A, int B>
	struct ControllerProps
	{
		GTD_API ControllerProps()
			: ID(0), connected(false), 
			m_numAxis(A), m_numButtons(B),
			m_axis{0}, m_CurrentButtons{0}
		{
		}

		GTD_API bool IsButtonPressed(ContextCode button) { return m_CurrentButtons[button]; };

		GTD_API Button& GetButton(ContextCode button)
		{
			/*
			Set button status 
			OFF = 0x0, // !current & ~previous
			RELEASED = 0x1, // ~current & previous
			PRESSED = 0x2, // current & ~previous
			HELD = 0x3 // current & previous
			*/

			m_Buttons[button].m_Status |= 1 << m_CurrentButtons[button] & m_PreviousButtons[button];

			return m_Buttons[button];
		}
		
		const std::vector<Button> GetButtons() const { return m_Buttons; }

		uint32_t ID;
		bool connected;

		/* info */
		int m_numAxis;
		float m_axis[A];
		/* distance from axis center to consider not moved */
		float m_axisCenteringEpsilon[A];

		int m_numButtons;
		unsigned char m_CurrentButtons[B];
		unsigned char m_PreviousButtons[B];

		/* Probably uneccesary */
		std::vector<Button> m_Buttons =
		{
			Button(ContextCode::X),
			Button(ContextCode::B),
			Button(ContextCode::A),
			Button(ContextCode::Y),
			Button(ContextCode::LB),
			Button(ContextCode::RB),
			Button(ContextCode::LT),
			Button(ContextCode::RT),
			Button(ContextCode::BACK),
			Button(ContextCode::START),
			Button(ContextCode::LSB),
			Button(ContextCode::RSB),
			Button(ContextCode::UP),
			Button(ContextCode::RIGHT),
			Button(ContextCode::DOWN),
			Button(ContextCode::LEFT),
		};

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

	/*
	template<> class ControllerProps<4, 16>
	{
	public:
		GTD_API ControllerProps();
		GTD_API ~ControllerProps();

	private:

	};

	GTD_API ControllerProps<4, 16>::ControllerProps<4, 16>()
	{
	}

	GTD_API ControllerProps<4, 16>::~ControllerProps<4, 16>()
	{
	}
	*/
}
