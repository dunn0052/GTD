#pragma once
#include "IComponent.h"
#include "../SpriteSheet.h"
#include "../../Renderer/Renderer2D.h"

namespace GTD
{
	class Drawable : public IComponent
	{
	public:
		GTD_API Drawable(const Ref<SubTexture>& texture, const Ref<Quad> quad);
		GTD_API Drawable();
		GTD_API virtual ~Drawable();

		GTD_API virtual void Init() override;
		GTD_API virtual void Update() override;
		GTD_API virtual void Activation(bool activate) { m_Active = activate; }
		GTD_API virtual COMPONENTS GetType() const override { return COMPONENTS::DRAWABLE; }


		GTD_API void Move(const glm::vec3& position);
		GTD_API void MoveTo(const glm::vec3& position);
		GTD_API void Tint(const glm::vec4& color);

	private:
		bool m_Active;
		Ref<SubTexture> m_SubTexture;
		Ref<Quad> m_Quad;
	};
}