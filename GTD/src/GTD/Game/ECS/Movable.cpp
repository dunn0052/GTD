#include "../../PCH/PCH.h"
#include "Movable.h"

namespace GTD
{
	Movable::Movable(const Ref<Quad>& quad, const Ref<Timestep>& dt, size_t index, float speed, const glm::vec3& direction, const bool& collidable) :
		m_Quad(quad), m_DT(dt), m_Index(index), m_Activated(true), m_Acceleration(0.0f), m_Speed(speed), m_Direction(direction), m_Collidable(collidable)
	{
	}

	Movable::~Movable()
	{
	}

	void Movable::Init()
	{
	}

	void Movable::Update()
	{
		if (m_Activated)
		{
			Move();
		}
	}

	void Movable::Activation(bool activate)
	{
		m_Activated = activate;
	}

	void Movable::Stop()
	{
		m_Direction = glm::vec3(0.0f);
	}

	void Movable::UpdateSpeed(float speed)
	{
		m_Speed = speed;
	}

	void Movable::ChangeDirection(const glm::vec2& direction)
	{
		m_Direction = { direction.x, direction.y, m_Direction.z };
	}

	void Movable::Move()
	{
		m_Quad->m_Rect.m_Position += m_Direction * m_Speed * m_DT->GetSecond();
	}

	void Movable::ChangeXDirection(float value)
	{
		m_Direction.x = value;
	}

	void Movable::ChangeYDirection(float value)
	{
		m_Direction.y = value;
	}

	void Movable::ChangeZDirection(float value)
	{
		m_Direction.z = value;
	}

	void Movable::SetPosition(const glm::vec2& position)
	{
		m_Quad->m_Rect.m_Position.x = position.x;
		m_Quad->m_Rect.m_Position.y = position.y;
	}

	const glm::vec3 Movable::GetDirection() const
	{
		return m_Direction;
	}

	const glm::vec2 Movable::Get2DDirection() const
	{
		return { m_Direction.x, m_Direction.y };
	}

	const float Movable::GetSpeed() const
	{
		return m_Speed;
	}

	const bool Movable::IsStopped() const
	{
		return m_Direction.x == 0.0f && m_Direction.y == 0.0f;
	}

	const bool Movable::IsCollidable() const
	{
		return m_Collidable;
	}

	GTD_API const glm::vec2 Movable::GetSize() const
	{
		return m_Quad->Size();
	}

	GTD_API const glm::vec2 Movable::GetPosition() const
	{
		return m_Quad->Position();
	}

}
