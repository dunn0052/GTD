#pragma once
#include "../glm/glm.hpp"

namespace GTD
{
	struct GTD_API Rect
	{
		Rect(const glm::vec3& position, const glm::vec2& size = { 1.0f, 1.0f }) : m_Position(position), m_Size(size) {}
		Rect() : m_Position(glm::vec3(0.0f)), m_Size(glm::vec2(1.0f)) {}
		glm::vec3 m_Position;
		glm::vec2 m_Size;
	};

	struct GTD_API Quad
	{
		Quad(const Rect& rect, const glm::vec4& color = glm::vec4(1.0f)) : m_Rect(rect), m_Color(color) {}
		Quad() : m_Rect(), m_Color(glm::vec4(1.0f)) {}

		float Top() { return m_Rect.m_Position.y + m_Rect.m_Size.y; }
		float Bottom() { return m_Rect.m_Position.y; }
		float Left() { return m_Rect.m_Position.x; }
		float Right() { return m_Rect.m_Position.x + m_Rect.m_Size.x; }

		Rect m_Rect;
		glm::vec4 m_Color;
	};
}