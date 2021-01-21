#include "../PCH/PCH.h"
#include "TIleE.h"

namespace GTD
{
	TileE::TileE(const TileParamsE& params) :
		m_Active(true), m_Quad(params.Quad), m_ComponentCallbacks()
	{
		Init();
	}

	TileE::~TileE()
	{
	}

	void TileE::Init()
	{
		for (auto& callback : m_ComponentCallbacks)
		{
			callback = []() {return nullptr; };
		}
	}

	void TileE::AddComponent(const GetComponentCallback& ret, const GetComponentCallbackParams& params, COMPONENTS type)
	{
		m_ComponentCallbacks[type] = std::bind(ret, params);
	}

	void TileE::Tint(const glm::vec4& color)
	{
		m_Quad->m_Color = color;
	}

	void TileE::Move(const glm::vec3& position)
	{
		m_Quad->m_Rect.m_Position += position; // hoping that this will also change the position of alls
	}
}