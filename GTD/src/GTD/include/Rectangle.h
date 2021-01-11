#pragma once
#include <glm.hpp> // vectors
#include <algorithm> // max and min
#include "Logger.h"

namespace GTD
{
	class Rect
	{
	public:
		GTD_API Rect() : m_Position({ 0.0f, 0.0f }), m_Size({ 0.0f, 0.0f }), m_Velocity({0.0f, 0.0f}) {};
		GTD_API Rect(const glm::vec2& pos, const glm::vec2& size) : m_Position(pos), m_Size(size), m_Velocity({0.0f}, {0.0f}) {};
		GTD_API ~Rect() {};
		GTD_API const float Top() const { return m_Position.y + m_Size.y; };
		GTD_API const float Bottom() const { return m_Position.y; };
		GTD_API const float Right() const { return m_Position.x + m_Size.x; };
		GTD_API const float Left() const { return m_Position.x; };
		GTD_API const glm::vec2 Position() const { return m_Position; };
		GTD_API const glm::vec2 Size() const { return m_Size; }
		GTD_API const glm::vec2 Velocity() const { return m_Velocity; }
		GTD_API void SetPosition(const glm::vec2& position) { 
			m_Position = position; 
			LOG_INFO("Position is (%f, %f)", position.x, position.y); 
		}

		GTD_API bool PointInRect(const glm::vec2& p)
		{
			return(p.x >= Left() &&
				p.x < Right() &&
				p.y >= Bottom() &&
				p.y < Top());
		};


		GTD_API bool RectCollideRect(const Rect& other)
		{
			return
				(
					Left() < other.Right() && Right() > other.Left() &&
					Bottom() < other.Top() && Top() > other.Bottom()
					);
		};


		GTD_API bool RectCollideRay(const glm::vec2& rayOrigin, const glm::vec2& rayDir,
			glm::vec2& outContactPoint, glm::vec2& outContactNormal, float& outContactTime)
		{
			glm::vec2 t_near = (m_Position - rayOrigin) / rayDir;
			glm::vec2 t_far = (m_Position + m_Size - rayOrigin) / rayDir;

			if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
			if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

			if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

			float t_hit_near = std::max<float>(t_near.x, t_near.y);
			float t_hit_far = std::min<float>(t_near.x, t_near.y);

			if (t_hit_far < 0) return false;

			outContactPoint = rayOrigin + t_hit_far * rayDir;

			if (t_near.x > t_near.y)
				if (rayDir.x < 0)
					outContactNormal = { 1.0f, 0.0f };
				else
					outContactNormal = { -1.0f, 0.0f };
			if (t_near.x < t_near.y)
				if (rayDir.y < 0)
					outContactNormal = { 0.0f, 1.0f };
				else
					outContactNormal = { 0.0f, -1.0f };

			return true;
		};

		GTD_API bool DynamicRectCollideRect(const Rect& in, glm::vec2& outContactPoint, glm::vec2& outContactNormal, float& outContactTime, float& dt)
		{
			/*
			if (in.Velocity().x == 0 && in.Velocity().y == 0) // If the rect hasn't moved then it hasn't had a chance to collide with anything
			{
				return false;
			}
			*/

			Rect expanded_target;
			expanded_target.m_Position = Position() - (in.Size() * 0.5f); // Create a buffer that is half the size of the moving rect
			expanded_target.m_Size = Size() + in.Size();
			if (expanded_target.RectCollideRay(in.Position() + in.Size() * 0.5f, in.Velocity() * dt, outContactPoint, outContactNormal, outContactTime))
			{
				if (outContactTime <= 1.0f)
				{
					return true;
				}
			}

			return false;

		}

	private:
		glm::vec2 m_Position;
		glm::vec2 m_Size;
		glm::vec2 m_Velocity;
	};

}