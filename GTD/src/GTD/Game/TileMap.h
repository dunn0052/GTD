#pragma once
#include "SpriteSheet.h"
#include "../Util/CSVLoader.h"
#include "../include/Core.h"
#include "TIle.h"

namespace GTD
{
	class TileMap
	{
	public:
		GTD_API TileMap(const std::string& timeMapCSVPath, const Ref<SpriteSheet> spriteSheet, float layer = 0.0f);
		GTD_API const std::vector<Tile> GetTiles() const { return m_Tiles; }
		GTD_API const Ref<SpriteSheet> GetSpriteSheet() const { return m_SpriteSheet; }
		GTD_API void SetTint(const glm::vec4& tint) { m_Tint = tint; for (Tile& tile : m_Tiles) { tile.m_Quad.m_Color = m_Tint; } }
		GTD_API void SetRelativePosition(glm::vec3 position) { m_Position = position; for (Tile& tile : m_Tiles) { tile.m_Quad.m_Rect.m_Position += m_Position; } }
	private:
		float m_Layer;
		Ref<SpriteSheet> m_SpriteSheet;
		std::vector<Tile> m_Tiles; // Tiles are stored as objects as the TileMap (should be stored as a ref)
		glm::vec4 m_Tint;
		glm::vec3 m_Position;
	};
}


