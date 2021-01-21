#pragma once
#include "../include/Core.h"
#include "../include/Rect.h"
#include "SpriteSheet.h"

namespace GTD
{
	struct SpriteParams
	{
		Ref<SubTexture> SubTexture;
		Ref<Quad> Quad;
	};

	class Sprite
	{
	public:
		GTD_API Sprite(const Ref<SubTexture>& subTexture, const Ref<Quad>& quad);
		GTD_API Sprite(const Ref<SubTexture>& subTexture);
		GTD_API Sprite(const SpriteParams& params);

		GTD_API Ref<SubTexture> GetImage() const { return m_SubTexture; }
		GTD_API Ref<Quad> GetQuad() const { return m_Quad; }

	private:
		Ref<Quad> m_Quad;
		Ref<SubTexture> m_SubTexture;
	};
}


