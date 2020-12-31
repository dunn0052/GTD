#include "PCH/PCH.h"
#include "include/Controllers.h"

namespace GTD
{
	Controllers::Controllers()
	{
		Init();
	}

	Controllers::~Controllers()
	{
		m_ControllerProps.clear();
	}

	static void debugXboxController(XboxController& controller)
	{
		std::stringstream ss;

		// one of the few times I want to use non class enums
		for(ContextCode button : XboxCode)
		{
			if (controller.m_buttons[button])
			{
				ss << XboxButtonMappings[button] << " ";
			}
		}

		for(ContextAxis axis : XboxAxis)
		{
			if (controller.m_axis[axis] < -controller.m_axisCenteringEpsilon[axis] || controller.m_axis[axis] > controller.m_axisCenteringEpsilon[axis])
			{
				ss << XboxAxisMappings[axis] << ": ";
				ss << controller.m_axis[axis] << " ";
			}
		}

		if (ss.rdbuf()->in_avail())
		{
			LOG_INFO("%s", ss.str().c_str());
		}
	}

	static const unsigned char* nullCheckglfwGetJoystickButtons(XboxController& controller)
	{
		const unsigned char* ret = glfwGetJoystickButtons(controller.ID, &controller.m_numButtons);
		return ret != NULL ? ret : controller.m_buttons;
	}

	void Controllers::OnUpdate()
	{
		/* could unroll here if needed */
		for(XboxController& controller : m_ControllerProps)
		{
			if (controller.connected)
			{
				/* NULL checks here to prevent crash on controller disconnect */
				const unsigned char* buttons = glfwGetJoystickButtons(controller.ID, &controller.m_numButtons);
				if (NULL != buttons)
				{
				memcpy(controller.m_buttons, 
					buttons, 
					controller.m_numButtons * sizeof(char));
				}
				else
				{
					controller.connected = false;
					continue;
				}

				const float* axis = glfwGetJoystickAxes(controller.ID, &controller.m_numAxis);
				if (NULL != axis)
				{
				memcpy(controller.m_axis, 
					axis, 
					controller.m_numAxis * sizeof(float));
				}
				else
				{
					controller.connected = false;
					continue;
				}

#if GTD_DEBUG_MODE
			debugXboxController(controller);
#endif
			}
		}
	}

	void Controllers::SetCallBacks()
	{
		// initialize the singleton instance of this to use con
		GLFWCallbackWrapper::SetInstance(this);

		// set callbacks up with glfw
		glfwSetJoystickCallback(GLFWCallbackWrapper::ControllerConnectionEvent);
	}

	void Controllers::Init()
	{
		m_ControllerProps.resize(MAX_NUM_CONTROLLERS);

		// add currently connected controllers
		for (int i = 0; i < MAX_NUM_CONTROLLERS; i++)
		{
			if(GLFW_TRUE == glfwJoystickPresent(i))
			{
				ControllerConnectionEvent(i, GLFW_CONNECTED);
			}
		}

		SetCallBacks();
	}

	void Controllers::ControllerConnectionEvent(int joypadID, int joypadCon)
	{
		XboxController& cont = m_ControllerProps[joypadID];

		if (GLFW_CONNECTED == joypadCon)
		{
			if (&cont != nullptr)
			{
				// configure mappings?
				cont.connected = true;
				cont.ID = joypadID;

				// get centering of axis -- gonna get that sweet doom speedrun bug
				memcpy(cont.m_axisCenteringEpsilon, glfwGetJoystickAxes(cont.ID, &cont.m_numAxis), cont.m_numAxis * sizeof(float));
				for (float& axisCenter : cont.m_axisCenteringEpsilon)
				{
					axisCenter += axisOffsetEpsilon;
				}

				// can add user pointer for this if other callback stuff is done
				//glfwSetJoystickUserPointer(cont.ID, &cont);

				LOG_INFO("Controller %d connected!", cont.ID);
			}
			else
			{
				LOG_WARN("Could not connect controller %d!", joypadID);
			}

		}
		else if (GLFW_DISCONNECTED == joypadCon)
		{
			if (&cont != nullptr)
			{
				LOG_INFO("Controller %d disconnected!", cont.ID);
				//glfwSetJoystickUserPointer(cont.ID, nullptr);
				memset(&cont, 0, sizeof(cont));
			}
			else
			{
				LOG_WARN("Could not disconnect controller %d!", joypadID);
			}
		}
	}

	/* set controller instance to null ilnitially */
	Controllers* Controllers::GLFWCallbackWrapper::s_Controllers = nullptr;
}