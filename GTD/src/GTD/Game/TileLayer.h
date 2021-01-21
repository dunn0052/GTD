#pragma once
#include "../include/Core.h"
#include "../include/Timestep.h"
#include "TileE.h"
#include "SpriteSheet.h"


namespace GTD
{
	struct TileLayerProps
	{
		std::string TileMapCSVPath;
		Ref<SpriteSheet> SpriteSheet;
		Ref<Quad> Quad;
		bool Solid;
		Ref<Timestep> DT;
	};

	class  TileLayer
	{
	public:
		GTD_API TileLayer(const TileLayerProps& props);
		GTD_API ~TileLayer();

		GTD_API void Activated(bool activated);
		GTD_API void Kill() { Activated(false); }

		GTD_API void AddTile(const Ref<TileE>& tile);
		GTD_API void SetTint(const glm::vec4& tint);

	private:
		std::vector<Ref<TileE>> m_Tiles;
		Ref<Quad> m_Quad;
		Ref<Timestep> m_DT;
		bool m_Activated;
	};
}