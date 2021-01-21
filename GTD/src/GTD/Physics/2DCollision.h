#pragma once
#include "../include/Core.h"
#include "../glm/glm.hpp"
#include "../include/Rectangle.h"
#include "../Game/ECS/Movable.h"
#include "../Game/ECS/Solid.h"

namespace GTD
{
	GTD_API bool PointInRect(const glm::vec2& p, const Rect& rect);

	GTD_API bool RectCollideRect(const Rect& in, const Rect& other);

	GTD_API bool RectCollideRay(const Rectangle& rect, const glm::vec2& rayOrigin, const glm::vec2& rayDir,
		glm::vec2& outContactPoint, glm::vec2& outContactNormal, float& t_hit_near);

	GTD_API bool MovableSolidCollideSolid(Movable& movable, Solid& solid, glm::vec2& outContactPoint, glm::vec2& outContactNormal, float& outContactTime, float& dt);
}