#pragma once
#include "../../include/Core.h"
#include "IComponent.h"
#include "../SpriteSheet.h"
#include "../../include/Rect.h"
#include "../../include/Timestep.h"

namespace GTD
{
	class Solid : public IComponent
	{
	public:

		GTD_API Solid(const Ref<Quad>& quad, const Ref<Timestep>& dt, size_t index);
		GTD_API virtual ~Solid();
		GTD_API virtual void Init() override;
		GTD_API virtual void Update() override;
		GTD_API virtual void Activation(bool activate) override;
		GTD_API virtual COMPONENTS GetType() const override { return COMPONENTS::SOLID; };


		GTD_API bool IsColliding(const Solid& other);
		GTD_API bool IsColliding(const Ref<Quad>& other);
		GTD_API const Ref<Quad> CollideRect(const Ref<Quad>& other);
		GTD_API bool CollideRect(const Ref<Quad>& other, Ref<Quad>& out);
		GTD_API const Ref<Quad> CollideRect(const Solid& other);
		GTD_API const glm::vec2 GetSize();
		GTD_API const glm::vec2 GetPosition();

	private:
		Ref<Quad> m_Quad;
		bool m_Activated;
		bool m_Colliding;
		size_t m_Index;
		Ref<Timestep> m_DT;
	};
}