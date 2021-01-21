#include "../../PCH/PCH.h"
#include "Solid.h"

namespace GTD
{
	Solid::Solid(const Ref<Quad>& quad, const Ref<Timestep>& dt, size_t index = 0) :
		m_Quad(quad), m_DT(dt), m_Index(index)
	{
		Init();
	}

	Solid::~Solid()
	{
	}

	void Solid::Init()
	{
	}

	void Solid::Update()
	{
	}

	void Solid::Activation(bool activate)
	{
		m_Activated = activate;
	}
	bool Solid::IsColliding(const Solid& other)
	{
		return  !(m_Quad->Left() >= other.m_Quad->Right() || 
				  other.m_Quad->Left() >= m_Quad->Right() || 
				  m_Quad->Top() >= other.m_Quad->Bottom() || 
			      other.m_Quad->Top() >= m_Quad->Bottom());
	}

	bool Solid::IsColliding(const Ref<Quad>& other)
	{
		return  !(m_Quad->Left() >= other->Right() ||
			other->Left() >= m_Quad->Right() ||
			m_Quad->Top() >= other->Bottom() ||
			other->Top() >= m_Quad->Bottom());
	}
	const Ref<Quad> Solid::CollideRect(const Ref<Quad>& other)
	{
		if (IsColliding(other))
		{
			return m_Quad;
		}
		else
		{
			return nullptr;
		}
	}
	bool Solid::CollideRect(const Ref<Quad>& other, Ref<Quad>& out)
	{
		if (IsColliding(other))
		{
			out = m_Quad;
			return true;
		}
		else
		{
			out = nullptr;
			return false;
		}

	}
	const Ref<Quad> Solid::CollideRect(const Solid& other)
	{
		if (IsColliding(other))
		{
			return m_Quad;
		}
		else
		{
			return nullptr;
		}
	}
	GTD_API const glm::vec2 Solid::GetSize()
	{
		return m_Quad->Size();
	}
	const glm::vec2 Solid::GetPosition()
	{
		return m_Quad->Position();
	}
}