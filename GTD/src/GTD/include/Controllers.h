#pragma once
#include "Logger.h"
#include "Core.h"
#include "ControllerProp.h"

namespace GTD
{
	static const char MAX_NUM_CONTROLLERS = 16; //GLFW_JOYSTICK_LAST + 1;

	class GTD_API Controllers
	{
	public:
		
		Controllers();
		~Controllers();

		void OnUpdate();
		void SetCallBacks();
		const std::vector<XboxController>& GetXboxControllers() const { return m_ControllerProps; };
		const XboxController& GetXboxController(size_t ID) const { GTD_ASSERT(ID < MAX_NUM_CONTROLLERS && ID > 0, "Controller index out of range!"); return m_ControllerProps[ID]; }

		// all callbacks must be mirrored in the GLFWCallbackWrapper class
		// and then set in SetCallbacks()
		void ControllerConnectionEvent(int joypadID, int joypadCon);

	private:
		void Init();
		std::vector<XboxController> m_ControllerProps;

		/* Creates reference to Controllers class so its members can be used */
		class GLFWCallbackWrapper
		{
		public:
			GLFWCallbackWrapper() = delete;
			GLFWCallbackWrapper(const GLFWCallbackWrapper&) = delete;
			GLFWCallbackWrapper(GLFWCallbackWrapper&&) = delete;
			~GLFWCallbackWrapper() = delete;

			static void SetInstance(Controllers* controller)
			{
				s_Controllers = controller;
			}

			static void ControllerConnectionEvent(int joypadID, int joypadCon)
			{
				return s_Controllers->ControllerConnectionEvent(joypadID, joypadCon);
			}

		private:
			static Controllers* s_Controllers;
		};
	};

}

