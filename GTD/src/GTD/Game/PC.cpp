#include "../PCH/PCH.h"
#include "PC.h"

namespace GTD
{
	PC::PC(const PCProps& pcProps) :
		Entity(), m_Active(true), m_ComponentCallbacks(), m_ControlParams{0.0f, this}, m_Quad(pcProps.Quad), 
		m_DT(pcProps.DT), m_Solid(pcProps.IsSolid)
	{
		Init();
	}

	PC::~PC()
	{
	}

	void PC::AddComponent(const GetComponentCallback& ret, const GetComponentCallbackParams& params, COMPONENTS type)
	{
		m_ComponentCallbacks[type] = std::bind(ret, params);
	}

	void PC::Move(const glm::vec2& position)
	{
		m_Quad->m_Rect.m_Position += glm::vec3{position.x, position.y, 0.0f} *m_DT->GetSecond();
	}

	void PC::MoveTo(const glm::vec2& position)
	{
		((Animated*)m_ComponentCallbacks[COMPONENTS::ANIMATED]())->MoveTo(position);
	}

	void PC::ChangeDirection(const glm::vec2& direction)
	{
		((Movable*)m_ComponentCallbacks[COMPONENTS::MOVABLE]())->ChangeDirection(direction);
	}

	void PC::ChangeSpeed(float speed)
	{
		((Movable*)m_ComponentCallbacks[COMPONENTS::MOVABLE]())->UpdateSpeed(speed);
	}

	void PC::Stop()
	{
		((Movable*)m_ComponentCallbacks[COMPONENTS::MOVABLE]())->Stop();
	}

	void PC::ChangXDirection(float value)
	{
		((Movable*)m_ComponentCallbacks[COMPONENTS::MOVABLE]())->ChangeXDirection(value);
	}

	void PC::ChangYDirection(float value)
	{
		((Movable*)m_ComponentCallbacks[COMPONENTS::MOVABLE]())->ChangeYDirection(value);
	}

	void PC::ChangZDirection(float value)
	{
		((Movable*)m_ComponentCallbacks[COMPONENTS::MOVABLE]())->ChangeZDirection(value);
	}

	void PC::Tint(const glm::vec4& color)
	{
		((Animated*)m_ComponentCallbacks[COMPONENTS::ANIMATED]())->Tint(color);
	}

	void PC::SetFrame(const uint32_t frameNum)
	{
		((Animated*)m_ComponentCallbacks[COMPONENTS::ANIMATED]())->SetFrame(frameNum);
	}

	void PC::NextFrame()
	{
		((Animated*)m_ComponentCallbacks[COMPONENTS::ANIMATED]())->NextFrame();
	}

	void PC::PreviousFrame()
	{
		((Animated*)m_ComponentCallbacks[COMPONENTS::ANIMATED]())->PreviousFrame();
	}

	void PC::AddAction(const ContextAxis& axis, const AxisActionCallback& action)
	{
		((Controllable*)m_ComponentCallbacks[COMPONENTS::CONTROLLABLE]())->AddAction(axis, action, m_ControlParams);
	}

	void PC::SetAction(const ContextCode& button, const ButtonActionCallback& action)
	{
		((Controllable*)m_ComponentCallbacks[COMPONENTS::CONTROLLABLE]())->SetAction(button, action, m_ControlParams);
	}

	Ref<Quad> PC::GetQuad() const
	{
		return m_Quad;
	}

	void PC::Init()
	{
		for (uint32_t type = 0; type < COMPONENTS::MAX_COMPONENTS; type++)
		{
			m_ComponentCallbacks[type] = []() { return nullptr; };
		}
	}
}