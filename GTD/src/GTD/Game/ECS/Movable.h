#pragma once
#include "../../include/Core.h"
#include "IComponent.h"
#include "../SpriteSheet.h"
#include "../../include/Rect.h"
#include "../../include/Timestep.h"

namespace GTD
{
	class Movable : public IComponent
	{
	public:

		GTD_API Movable(const Ref<Quad>& quad, const Ref<Timestep>& dt, size_t index, float speed, const glm::vec3& direction, const bool& collidable);
		GTD_API virtual ~Movable();
		GTD_API	virtual void Init() override;
		GTD_API virtual void Update() override;
		GTD_API virtual void Activation(bool activate) override;
		GTD_API virtual COMPONENTS GetType() const override { return COMPONENTS::MOVABLE; };

		GTD_API void Stop();
		GTD_API void UpdateSpeed(float speed);
		GTD_API void ChangeDirection(const glm::vec2& direction);
		GTD_API void Move(); // move in current direction
		GTD_API void ChangeXDirection(float value);
		GTD_API void ChangeYDirection(float value);
		GTD_API void ChangeZDirection(float value);
		GTD_API void SetPosition(const glm::vec2& position);
		
		GTD_API const glm::vec3  GetDirection() const;
		GTD_API const glm::vec2 Get2DDirection() const;
		GTD_API const float GetSpeed() const;
		GTD_API const bool IsStopped() const;
		GTD_API const bool IsCollidable() const;
		GTD_API const glm::vec2 GetSize() const;
		GTD_API const glm::vec2 GetPosition() const;

	private:
		Ref<Quad> m_Quad;
		bool m_Activated;
		glm::vec3 m_Direction;
		float m_Speed;
		float m_Acceleration;
		size_t m_Index;
		Ref<Timestep> m_DT;
		bool m_Collidable;
	};
}