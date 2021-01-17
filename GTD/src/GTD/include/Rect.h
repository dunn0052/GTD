#pragma once
#include "../glm/glm.hpp"

namespace GTD
{
	struct Rectangle
	{
		GTD_API Rectangle(const glm::vec3& position, const glm::vec2& size = { 1.0f, 1.0f }) : m_Position(position), m_Size(size) {}
		GTD_API Rectangle(const glm::vec2& position, const glm::vec2& size = { 1.0f, 1.0f }) : m_Position{ position.x, position.y, 0.0f }, m_Size(size) {}
		GTD_API Rectangle() : m_Position(glm::vec3(0.0f)), m_Size(glm::vec2(1.0f)) {}
		GTD_API const float Top() const { return m_Position.y + m_Size.y; };
		GTD_API const float Bottom() const { return m_Position.y; };
		GTD_API const float Right() const { return m_Position.x + m_Size.x; };
		GTD_API const float Left() const { return m_Position.x; };
		GTD_API const glm::vec2 Position() const { return { m_Position.x, m_Position.y }; };
		GTD_API const glm::vec2 Size() const { return m_Size; };
		glm::vec3 m_Position;
		glm::vec2 m_Size;
	};

	struct Quad
	{
		GTD_API Quad(const Rectangle& rect, const glm::vec4& color = glm::vec4(1.0f)) : m_Rect(rect), m_Color(color) {}
		GTD_API Quad() : m_Rect(), m_Color(glm::vec4(1.0f)) {}

		GTD_API const float Top() { return m_Rect.Top(); }
		GTD_API const float Bottom() { return m_Rect.Bottom(); }
		GTD_API const float Left() { return m_Rect.Left(); }
		GTD_API const float Right() { return m_Rect.Right(); }
		GTD_API const glm::vec2 Size() { return m_Rect.Size(); }
		GTD_API const glm::vec2 Position() { return m_Rect.Position(); }

		Rectangle m_Rect;
		glm::vec4 m_Color;
	};
}