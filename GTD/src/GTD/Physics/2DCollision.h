#pragma once
#include "../include/Core.h"
#include "../glm/glm.hpp"
#include "../include/Rectangle.h"
#include "../Game/ECS/Movable.h"
#include "../Game/ECS/Solid.h"

namespace GTD
{
	GTD_API bool PointInRect(const glm::vec2& p, const Rect& rect)
	{
		return(p.x >= rect.Left() &&
			p.x < rect.Right() &&
			p.y >= rect.Bottom() &&
			p.y < rect.Top());
	};


	GTD_API bool RectCollideRect(const Rect& in, const Rect& other)
	{
		return
			(
				in.Left() < other.Right() && in.Right() > other.Left() &&
				in.Bottom() < other.Top() && in.Top() > other.Bottom()
				);
	};


	GTD_API bool RectCollideRay(const Rectangle& rect, const glm::vec2& rayOrigin, const glm::vec2& rayDir,
		glm::vec2& outContactPoint, glm::vec2& outContactNormal, float& t_hit_near)
	{

		glm::vec2 invRayDir = 1.0f / rayDir;

		/* Calculate top left collision */
		glm::vec2 t_near = (rect.Position() - rayOrigin) * invRayDir;

		/* Calcualte bottom right collision */
		glm::vec2 t_far = (rect.Size() + rect.Size() - rayOrigin) * invRayDir;

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

	GTD_API bool MovableSolidCollideSolid(Movable& movable, Solid& solid, glm::vec2& outContactPoint, glm::vec2& outContactNormal, float& outContactTime, float& dt)
	{
		Rectangle expanded_target = Rectangle(movable.GetPosition() - solid.GetSize() * 0.5f, movable.GetSize() + solid.GetSize());
		if (RectCollideRay(expanded_target, movable.GetPosition() + movable.GetSize() * 0.5f, movable.GetDirection() * dt, outContactPoint, outContactNormal, outContactTime))
		{
			if (outContactTime <= 1.0f) // If the collision happened sometime before the end of the timestep
			{
				LOG_FATAL("Collided!");
				return true;
			}
		}

		return false;

	}
}