#pragma once
#include "ECS/Drawable.h"
#include "ECS/Animated.h"
#include "ECS/Entity.h"
#include "../Util/Utils.h"
#include "../include/Core.h"
#include "../include/Timestep.h"

namespace GTD
{
	struct SpriteParamsE
	{
		Ref<SpriteSheet> SpriteSheet;
		Ref<Quad> Quad;
		Ref<Timestep> DT;
		int32_t StartingFrame;
		bool IsSolid;
	};

	class SpriteE : public Entity
	{
	public:
		GTD_API SpriteE();
		GTD_API	virtual ~SpriteE() override;
		GTD_API virtual void AddComponent(const GetComponentCallback& ret, const GetComponentCallbackParams& params, COMPONENTS type) override;
		GTD_API virtual void Init() override;
		GTD_API virtual bool const IsActive() override { return m_Active; };
		GTD_API virtual void Kill() override { Activated(false); }
		GTD_API virtual void Activated(bool activated) override {
			m_Active = activated; 
			for (Ref<IComponent>& component : m_Components) 
			{ 
				if (nullptr != component)
				{
					component->Activation(m_Active); 
				}
			}
		}

		GTD_API void Move(const glm::vec3& position);
		GTD_API void MoveTo(const glm::vec3& position);
		GTD_API void Tint(const glm::vec4& color);
		GTD_API void SetFrame(const uint32_t frameNum);
		GTD_API void NextFrame();
		GTD_API void PreviousFrame();

	private:
		bool m_Active;
		Ref<Timestep> m_DT;
		std::array<Ref<IComponent>, COMPONENTS::MAX_COMPONENTS> m_Components;
		std::array<GetComponent, COMPONENTS::MAX_COMPONENTS> m_ComponentCallbacks;
	};
}