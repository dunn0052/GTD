#include "../PCH/PCH.h"
#include "SpriteSheet.h"
#include "../include/Logger.h"

namespace GTD
{
	SpriteSheet::SpriteSheet(const Ref<ITexture2D>& spriteSheet, const glm::vec2& tileSize) :
		m_SpriteSheet(spriteSheet), m_tileSize(tileSize), m_SheetSize({spriteSheet->GetWidth(), spriteSheet->GetHeight()}), m_numTiles(m_SheetSize.x/ m_tileSize.x, m_SheetSize.y / m_tileSize.y)
	{
	}

	SpriteSheet::SpriteSheet(const std::string& spriteSheetPath, const glm::vec2& tileSize)
		: m_SpriteSheet(ITexture2D::Create(spriteSheetPath)), m_tileSize(tileSize), m_SheetSize({ m_SpriteSheet->GetWidth(), m_SpriteSheet->GetHeight() }), m_numTiles(m_SheetSize.x / m_tileSize.x, m_SheetSize.y / m_tileSize.y)
	{
	}

	Ref<SubTexture> SpriteSheet::GetTile(const glm::vec2& coord, const glm::vec2& size)
	{
		GTD_ASSERT(coord.x <= m_numTiles.x && coord.y <= m_numTiles.y, "Coordinates are out of bounds");

		glm::vec2 textureCoords[] =
		{
			{(coord.x * m_tileSize.x) / m_SheetSize.x, (coord.y * m_tileSize.y) / m_SheetSize.y}, // top left
			{((coord.x + size.x) * m_tileSize.x) / m_SheetSize.x, (coord.y * m_tileSize.y) / m_SheetSize.y}, // top right
			{((coord.x + size.x) * m_tileSize.x) / m_SheetSize.x, ((coord.y + size.y) * m_tileSize.y) / m_SheetSize.y }, // bottom left
			{(coord.x * m_tileSize.x) / m_SheetSize.x, ((coord.y + size.y) * m_tileSize.y) / m_SheetSize.y}, // bottom right
		};

		return CreateRef<SubTexture>(m_SpriteSheet, textureCoords);
	}

	Ref<SubTexture> SpriteSheet::GetTile(const int32_t index, const glm::vec2& size)
	{
		glm::vec2 coord(1.0f);
		coord.x = (float)( index % (int32_t)m_numTiles.x);
		coord.y = (float)((int32_t)m_numTiles.y - index / (int32_t)m_numTiles.x) - 1;
		return GetTile(coord, size);
	}
}