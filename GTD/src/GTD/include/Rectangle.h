#pragma once
#include <glm.hpp>

namespace GTD
{
	class Rect
	{
	public:
		Rect() : m_Position({ 0.0f, 0.0f }), m_Size({ 0.0f, 0.0f }) {};
		Rect(const glm::vec2& pos, const glm::vec2& size) : m_Position(pos), m_Size(size) {};
		~Rect() {};
		const float Top() const { return m_Position.y + m_Size.y; };
		const float Bottom() const { return m_Position.y; };
		const float Right() const { return m_Position.x + m_Size.x; };
		const float Left() const { return m_Position.x; };

	private:
		glm::vec2 m_Position;
		glm::vec2 m_Size;
	};

	static bool PointInRect(const glm::vec2& p, const Rect& r)
	{
		return(p.x >= r.Left()    &&
				p.x < r.Right()   &&
				p.y >= r.Bottom() &&
				p.y < r.Top());
	};

	static bool RectCollideRect(const Rect& r1, const Rect& r2)
	{
		return  
			(
			r1.Left() < r2.Right() && r1.Right() > r2.Left() && 
			r1.Bottom() < r2.Top() && r1.Top() > r2.Bottom()
			);
	}
}