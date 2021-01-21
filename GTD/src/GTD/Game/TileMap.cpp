#include "../PCH/PCH.h"
#include "TileMap.h"

namespace GTD
{
	TileMap::TileMap(const std::string& tileMapCSVPath, const Ref<SpriteSheet> spriteSheet, float layer) :
		m_Layer(layer), m_SpriteSheet(spriteSheet), m_Tint(glm::vec4(1.0f)), m_Position(glm::vec3(0.0f))
	{
		std::vector<std::vector<int32_t>> table = CSVLoader::GetInstance()->LoadIntegerCSV(tileMapCSVPath);
		glm::vec2 tileSize = spriteSheet->GetTileSize();

		int32_t numTiles = 0;
		for (auto& row : table)
		{
			numTiles += row.size();
		}

		m_Tiles.reserve(numTiles); // maybe should be resize?

		for (int row = 0; row < table.size(); row++)
		{
			for (int column = 0; column < table[row].size(); column++)
			{
				int32_t tileIndex = table[row][column];
				if (tileIndex > -1 && tileIndex <= m_SpriteSheet->GetNumTiles())
				{
					m_Tiles.push_back({{column, table.size() - row, m_Layer}, tileIndex });
				}
			}
		}
	}
}