#pragma once
#include "../glm/glm.hpp"

namespace GTD
{
	struct Rectangle
	{
		GTD_API Rectangle(const glm::vec3& position, const glm::vec2& size = { 1.0f, 1.0f }) : m_Position(position), m_Size(size) {}
		GTD_API Rectangle() : m_Position(glm::vec3(0.0f)), m_Size(glm::vec2(1.0f)) {}
		glm::vec3 m_Position;
		glm::vec2 m_Size;
	};

	struct Quad
	{
		GTD_API Quad(const Rectangle& rect, const glm::vec4& color = glm::vec4(1.0f)) : m_Rect(rect), m_Color(color) {}
		GTD_API Quad() : m_Rect(), m_Color(glm::vec4(1.0f)) {}

		GTD_API float Top() { return m_Rect.m_Position.y + m_Rect.m_Size.y; }
		GTD_API float Bottom() { return m_Rect.m_Position.y; }
		GTD_API float Left() { return m_Rect.m_Position.x; }
		GTD_API float Right() { return m_Rect.m_Position.x + m_Rect.m_Size.x; }

		Rectangle m_Rect;
		glm::vec4 m_Color;
	};
}