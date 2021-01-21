#include "../PCH/PCH.h"
#include "Sprite.h"

namespace GTD
{
	Sprite::Sprite(const Ref<SubTexture>& subTexture, const Ref<Quad>& quad) :
		m_SubTexture(subTexture), m_Quad(quad)
	{
	}

	Sprite::Sprite(const Ref<SubTexture>& subTexture) :
		m_SubTexture(subTexture)
	{
		m_Quad = CreateRef<Quad>(Rectangle{ {0.0f, 0.0f, 0.0f}, {1.0f,  1.0f} });
	}

	Sprite::Sprite(const SpriteParams& params) :
		m_SubTexture(params.SubTexture), m_Quad(params.Quad)
	{

	}
}