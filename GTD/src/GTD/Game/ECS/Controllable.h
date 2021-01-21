#pragma once
#include "IComponent.h"
#include "../../Util/JoypadCodes.h"
#include "../../Util/KeyCodes.h"
#include "../../Util/MouseCodes.h"
#include "../../Util/Utils.h"
#include "../../include/ControllerCodes.h"
#include "../../include/ContextCodes.h"
#include "../../include/Controllers.h"
#include "../../include/ControllerProp.h"
#include "../../include/Core.h"
#include "../../include/Timestep.h"

namespace GTD
{

	struct ControlCallbackParams
	{
		Timestep dt;
		void* object;
	};

	typedef void  (*ButtonActionCallback)(const ControlCallbackParams&, unsigned char status);
	typedef void  (*AxisActionCallback)(const ControlCallbackParams&, float axis);


	class Controllable : public IComponent
	{

	public:
		//Controllable(const XboxController& controller);
		GTD_API Controllable(const XboxController* controller);
		GTD_API virtual ~Controllable() {};

		GTD_API virtual void Init() override;
		GTD_API virtual void Update() override;
		GTD_API virtual void Activation(bool activate) override;
		GTD_API virtual COMPONENTS GetType() const override { return COMPONENTS::CONTROLLABLE; };

		GTD_API void Do(Button button); // could be private
		GTD_API void Do(ContextAxis axis); // could be private

		GTD_API void SetAction(const ContextCode& button, const ButtonActionCallback& action, const ControlCallbackParams& params);
		GTD_API void AddAction(const ContextAxis& button, const AxisActionCallback& action, const ControlCallbackParams& params);

	private:
		bool m_Active = false;
		std::unordered_map<ContextCode, std::function<void(unsigned char)>> m_ButtonCallbacks;
		std::unordered_map<ContextAxis, std::function<void(float)>> m_AxisActions;
		const XboxController* m_Controller;
	};
}
