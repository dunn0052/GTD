#include "../PCH/PCH.h"
#include "TileMapE.h"

namespace GTD
{
	TileMapE::TileMapE() :
		m_Layer(0.0f), m_SpriteSheet(), m_Tiles(), m_Tint(glm::vec4(1.0f)), m_Position(glm::vec3(0.0f)), m_Activated(true)
	{
	}

	TileMapE::~TileMapE()
	{
	}

	void TileMapE::AddComponent(const GetComponentCallback& ret, const GetComponentCallbackParams& params, COMPONENTS type)
	{
		
	}

	void TileMapE::Init()
	{
	}

	bool const TileMapE::IsActive()
	{
		return m_Activated;
	}

	void TileMapE::Activated(bool activated)
	{
		m_Activated = activated;
	}

	void TileMapE::Kill()
	{
		Activated(false);
	}
}