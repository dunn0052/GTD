#include "../../PCH/PCH.h"
#include "Controllable.h"

namespace GTD
{

    Controllable::Controllable(const XboxController* controller) :
        m_Controller(controller), m_AxisActions(), m_Active(true)
    {
        Init();
    }

    void Controllable::Init()
    {

        // Ensure all buttons exist for action and default to an approprate "do nothing" lambda
        for (ContextCode button : XboxCode)
        {
            m_ButtonCallbacks[button] = [](unsigned char) {};
        }

        for (ContextAxis axis : XboxAxis)
        {
            m_AxisActions[axis] = [](float) {};
        }
    }

    void Controllable::Update()
    {
        if (m_Active && m_Controller->connected)
        {
            for (const Button& button : m_Controller->GetButtons()) // Then we don't care about mapping and can use interfaces
            {
                Do(button);
            }

            for (ContextAxis axis : XboxAxis)
            {
                Do(axis);
            }
        }
    }

    void Controllable::Activation(bool activate)
    {
        m_Active = activate;
    }

    void Controllable::Do(Button button)
    {
        if (button.m_Status) // if !OFF
        {
            m_ButtonCallbacks[button.Code()](button.m_Status); // call button callback with the status of the button
        }
    }

    void Controllable::Do(ContextAxis axis)
    {
        // If the axis tilt is outside of "centered" epsilon then call the function with the axis
        if (m_Controller->m_axis[axis] < -m_Controller->m_axisCenteringEpsilon[axis] || m_Controller->m_axis[axis] > m_Controller->m_axisCenteringEpsilon[axis])
        {
            m_AxisActions[axis](m_Controller->m_axis[axis]);
        }
    }

    void Controllable::SetAction(const ContextCode& button, const ButtonActionCallback& action, const ControlCallbackParams& params)
    {
        m_ButtonCallbacks[button] = std::bind(action, std::ref(params), std::placeholders::_1);
    }
    
    void Controllable::AddAction(const ContextAxis& axis, const AxisActionCallback& action, const ControlCallbackParams& params)
    {
        m_AxisActions[axis] = std::bind(action, std::ref(params), std::placeholders::_1);
    }
}