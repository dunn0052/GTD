#include "../PCH/PCH.h"
#include "TileLayer.h"

namespace GTD
{
	TileLayer::TileLayer(const TileLayerProps& props) :
		m_Tiles(), m_Quad(props.Quad), m_DT(props.DT), m_Activated(true)
	{
	}

	TileLayer::~TileLayer()
	{
	}
	void TileLayer::Activated(bool activated)
	{
		m_Activated = activated;
		for (auto& tile : m_Tiles)
		{
			tile->Activated(m_Activated);
		}
	}
	void TileLayer::AddTile(const Ref<TileE>& tile)
	{
		m_Tiles.push_back(tile);
	}
	void TileLayer::SetTint(const glm::vec4& tint)
	{
		for (auto& tile : m_Tiles)
		{
			tile->Tint(tint);
		}
	}
}
