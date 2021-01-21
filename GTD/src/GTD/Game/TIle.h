#pragma once
#include "SpriteSheet.h"
#include "../include/Rect.h"

namespace GTD
{
	struct Tile
	{
		GTD_API Tile(const glm::vec3& position, int32_t positionID):
			m_Quad(Quad(Rectangle(position))) , m_PositionID(positionID) {}

		GTD_API Tile() : m_PositionID(-1), m_Quad() {}
		int32_t m_PositionID; // which tile on the spritesheet
		Quad m_Quad; // the position and size
	};
}