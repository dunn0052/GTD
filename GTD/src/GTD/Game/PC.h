#pragma once
#include "ECS/Entity.h"
#include "ECS/IComponent.h"
#include "ECS/Animated.h"
#include "ECS/Controllable.h"
#include "ECS/Solid.h"
#include "ECS/Movable.h"
#include "../include/Timestep.h"

namespace GTD

{
	struct PCProps
	{
		Ref<SpriteSheet> SpriteSheet;
		Ref<Quad> Quad;
		bool IsSolid;
		Ref<Timestep> DT;
		int32_t StartingFrame;
		const XboxController* Controller;
		float Speed;
		glm::vec3 StartingDirection;
	};

	class PC : public Entity
	{
	public:
		GTD_API PC(const PCProps& props);
		GTD_API virtual ~PC() override;

		GTD_API virtual void AddComponent(const GetComponentCallback& ret, const GetComponentCallbackParams& params, COMPONENTS type) override;

		GTD_API virtual bool const IsActive() override { return m_Active; };
		GTD_API virtual void Kill() override { Activated(false); }
		GTD_API virtual void Activated(bool activated) override 
		{
			m_Active = activated;
			for (GetComponent componentCallback : m_ComponentCallbacks)
			{
				IComponent* component = componentCallback();
				if (nullptr != component)
				{
					component->Activation(m_Active);
				}
			}
		}

		// Movable
		GTD_API void Move(const glm::vec2& position);
		GTD_API void MoveTo(const glm::vec2& position);
		GTD_API void ChangeDirection(const glm::vec2& direction);
		GTD_API void ChangeSpeed(float speed);
		GTD_API void Stop();
		GTD_API void ChangXDirection(float value);
		GTD_API void ChangYDirection(float value);
		GTD_API void ChangZDirection(float value);


		// Animated
		GTD_API void Tint(const glm::vec4& color);
		GTD_API void SetFrame(const uint32_t frameNum);
		GTD_API void NextFrame();
		GTD_API void PreviousFrame();
		GTD_API void AddAction(const ContextAxis& axis, const AxisActionCallback& action);
		GTD_API void SetAction(const ContextCode& button, const ButtonActionCallback& action);

		GTD_API Ref<Quad> GetQuad() const;

	private:
		void Init();

	private:
		bool m_Active;
		Ref<Quad> m_Quad;
		bool m_Solid;
		Ref<Timestep> m_DT;
		std::array<Ref<IComponent>, COMPONENTS::MAX_COMPONENTS> m_Components;
		std::array<GetComponent, COMPONENTS::MAX_COMPONENTS> m_ComponentCallbacks;
		ControlCallbackParams m_ControlParams;
	};
}
