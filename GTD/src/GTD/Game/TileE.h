#pragma once
#include "ECS/Animated.h"
#include "ECS/Entity.h"
#include "../Util/Utils.h"
#include "../include/Core.h"

namespace GTD
{
	struct TileParamsE
	{
		Ref<Quad> Quad;
	};

	class TileE : public Entity
	{
	public:
		GTD_API TileE(const TileParamsE& params);
		GTD_API virtual ~TileE() override;

		GTD_API virtual void AddComponent(const GetComponentCallback& ret, const GetComponentCallbackParams& params, COMPONENTS type) override;
		GTD_API virtual void Init() override;
		GTD_API virtual bool const IsActive() override { return m_Active; };
		GTD_API virtual void Kill() override { Activated(false); }
		GTD_API virtual void Activated(bool activated) override 
		{
			m_Active = activated;
			for (GetComponent& callback : m_ComponentCallbacks)
			{
				IComponent* component = callback();
				if (nullptr != component)
				{
					component->Activation(m_Active);
				}
			}
		}

		GTD_API void Tint(const glm::vec4& color);
		GTD_API void Move(const glm::vec3& position);

	private:
		bool m_Active;
		Ref<Quad> m_Quad;
		std::array<GetComponent, COMPONENTS::MAX_COMPONENTS> m_ComponentCallbacks;
	};
}