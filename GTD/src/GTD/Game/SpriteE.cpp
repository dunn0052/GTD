#include "../PCH/PCH.h"
#include "SpriteE.h"

namespace GTD
{
	SpriteE::SpriteE() : 
		Entity(), m_Active(true), m_ComponentCallbacks()
	{
	}

	SpriteE::~SpriteE()
	{
	}

	void SpriteE::AddComponent(const GetComponentCallback& ret, const GetComponentCallbackParams& params, COMPONENTS type)
	{
		m_ComponentCallbacks[type] = std::bind(ret, params);
	}

	void SpriteE::Init()
	{
	}

	void SpriteE::Move(const glm::vec3& position)
	{
		std::static_pointer_cast<Animated>(m_Components[COMPONENTS::ANIMATED])->Move(position);
	}

	void SpriteE::MoveTo(const glm::vec3& position)
	{
		std::static_pointer_cast<Animated>(m_Components[COMPONENTS::ANIMATED])->MoveTo(position);
	}

	void SpriteE::Tint(const glm::vec4& color)
	{
		std::static_pointer_cast<Animated>(m_Components[COMPONENTS::ANIMATED])->Tint(color);
	}

	void SpriteE::SetFrame(const uint32_t frameNum)
	{
		std::static_pointer_cast<Animated>(m_Components[COMPONENTS::ANIMATED])->SetFrame(frameNum);
	}

	void SpriteE::NextFrame()
	{
		std::static_pointer_cast<Animated>(m_Components[COMPONENTS::ANIMATED])->NextFrame();
	}

	void SpriteE::PreviousFrame()
	{
		std::static_pointer_cast<Animated>(m_Components[COMPONENTS::ANIMATED])->PreviousFrame();
	}
}

