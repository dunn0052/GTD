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
		GTD_API const glm::vec2 Size() const { return m_Size; };
		GTD_API const glm::vec2 Velocity() const { return m_Velocity; };
		GTD_API void SetVelocity(const glm::vec2& velocity) { m_Velocity = velocity; };

		GTD_API void AddX(const float& xVel) { m_Velocity.x += xVel; };
		GTD_API void AddY(const float& yVel) { m_Velocity.y += yVel; };

		GTD_API void SetPosition(const glm::vec2& position) {
			m_Position = position;
		};

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
			glm::vec2& outContactPoint, glm::vec2& outContactNormal, float& t_hit_near)
		{

			glm::vec2 invRayDir = 1.0f / rayDir;

			/* Calculate top left collision */
			glm::vec2 t_near = (m_Position - rayOrigin) * invRayDir;

			/* Calcualte bottom right collision */
			glm::vec2 t_far = (m_Position + m_Size - rayOrigin) * invRayDir;

			if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
			if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

			/* Swap if ray is going right to left */
			if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
			if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

			/* Didn't hit */
			if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

			/* Reorder to correct for left vs right collisions */
			t_hit_near = std::max<float>(t_near.x, t_near.y);
			float t_hit_far = std::min<float>(t_far.x, t_far.y);

			/* Don't care if ray began after quad and goes in away direction ( t_hit_far is negative )*/
			if (t_hit_far < 0) return false;

			/* Standard linear interpolation */
			outContactPoint = rayOrigin + t_hit_near * rayDir;

			/* Calculate normal (must be on of 4 directions when colliding with quad */
			if (t_near.x > t_near.y)
				if (invRayDir.x < 0)
					outContactNormal = { 1.0f, 0.0f }; // right
				else
					outContactNormal = { -1.0f, 0.0f }; // left
			if (t_near.x < t_near.y)
				if (invRayDir.y < 0)
					outContactNormal = { 0.0f, 1.0f }; // up
				else
					outContactNormal = { 0.0f, -1.0f }; // down

			return true;
		};

		GTD_API bool DynamicRectCollideRect(const Rect& in, glm::vec2& outContactPoint, glm::vec2& outContactNormal, float& outContactTime, float& dt)
		{
			
			if (in.Velocity().x == 0.0f && in.Velocity().y == 0.0f) // If the rect hasn't moved then it hasn't had a chance to collide with anything
			{
				return false;
			}
			
			LOG_DEBUG("Moving");

			Rect expanded_target;
			expanded_target.m_Position = Position() - (in.Size() * 0.5f); // move original half size of colliding rect left
			expanded_target.m_Size = Size() + in.Size(); // Then add a half size of colliding rect buffer aound this
			if (expanded_target.RectCollideRay(in.Position() + in.Size() * 0.5f, in.Velocity() * dt, outContactPoint, outContactNormal, outContactTime))
			{
				if (outContactTime <= 1.0f) // If the collision happened sometime before the end of the timestep
				{
					LOG_FATAL("Collided!");
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