#include "../PCH.h"
#include "include/Controllers.h"
#include <glfw3.h>

namespace GTD
{
	Controllers::Controllers()
	{
		Init();
	}

	Controllers::~Controllers()
	{
		m_ControllerProps.clear(); // sus on what happens if the space is reserved, but not initiated
	}

	static void debugXboxController(XboxController& controller)
	{
		bool end = false;
		std::stringstream ss;

		for (size_t i = 0; i < controller.m_numButtons; i++)
		{
			if (controller.m_buttons[i])
			{
				end = true;
				ss << XboxButtonMappings[i] << " ";
			}
		}

		for (size_t i = 0; i < controller.m_numAxis; i++)
		{
			if (controller.m_axis[i] < -controller.m_axisCenteringEpsilon[i] || controller.m_axis[i] > controller.m_axisCenteringEpsilon[i])
			{
				end = true;
				ss << controller.m_axis[i] << " ";
			}
		}

		if (end)
		{
			LOG_INFO("%s", ss.str().c_str());
		}
	}

	void Controllers::OnUpdate()
	{
		/* could unroll here if needed */
		for(XboxController& controller : m_ControllerProps)
		{
			if (controller.connected)
			{
#define IF_NULL(a,b) ((a) == NULL ? (b) : (a))
				memcpy(controller.m_buttons, IF_NULL(glfwGetJoystickButtons(controller.ID, &controller.m_numButtons), controller.m_buttons), controller.m_numButtons * sizeof(char));
				memcpy(controller.m_axis, IF_NULL(glfwGetJoystickAxes(controller.ID, &controller.m_numAxis), controller.m_axis), controller.m_numAxis * sizeof(float));
#undef IFNULL

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

				LOG_DEBUG("Controller %d connected!", cont.ID);
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
				cont.connected = false;
				LOG_DEBUG("Controller %d disconnected!", cont.ID);
			}
			else
			{
				LOG_WARN("Could not disconnect controller %d!", joypadID);
			}
		}
	}

	uint32_t Controllers::controllerIDs = 0;

	/* set controller instance to null ilnitially */
	Controllers* Controllers::GLFWCallbackWrapper::s_Controllers = nullptr;
}