#pragma once
#include "../include/Core.h"
#include "../Renderer/ITexture.h"

namespace GTD
{
	class SubTexture
	{
	public:
		GTD_API SubTexture(Ref<ITexture2D>& spriteSheet, glm::vec2 textureCoordinates[4]) : m_SpriteSheet(spriteSheet)
		{
			memcpy(m_TexCoords, textureCoordinates, 4 * sizeof(glm::vec2));
		}

		GTD_API const Ref<ITexture2D> GetSpriteSheet() const { return m_SpriteSheet; }
		GTD_API const glm::vec2* GetTextureCoordinates() const { return m_TexCoords; }
		GTD_API const glm::vec2 GetSize() const { return { m_TexCoords[1].x - m_TexCoords[0].x, m_TexCoords[1].y - m_TexCoords[0].y }; }

	private:
		Ref<ITexture2D> m_SpriteSheet;
		glm::vec2 m_TexCoords[4];
	};

	class SpriteSheet
	{
	public:
		GTD_API SpriteSheet(const Ref<ITexture2D>& spriteSheet, const glm::vec2& tileSize);
		GTD_API SpriteSheet(const std::string& spriteSheetPath, const glm::vec2& tileSize);
		GTD_API glm::vec2 GetTileSize() const { return m_tileSize; }
		GTD_API Ref<SubTexture> GetTile(const glm::vec2& coord, const glm::vec2& size = { 1.0f, 1.0f });
		GTD_API Ref<SubTexture> GetTile(const int32_t index, const glm::vec2& size = { 1.0f, 1.0f });
		GTD_API const Ref<ITexture2D> GetSpriteSheet() const { return m_SpriteSheet; }
		GTD_API const int32_t GetNumTiles() const { return (int32_t)(m_numTiles.x * m_numTiles.y); }
	private:
		Ref<ITexture2D> m_SpriteSheet;
		glm::vec2 m_tileSize;
		glm::vec2 m_SheetSize;
		glm::vec2 m_numTiles;
	};

}