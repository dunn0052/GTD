#pragma once
#include "../../include/Core.h"
#include "IComponent.h"
#include "../SpriteSheet.h"
#include "../../include/Rect.h"
#include "../../include/Timestep.h"

namespace GTD
{
	class Animated : public IComponent
	{
	public:

		GTD_API Animated(const Ref<SpriteSheet>& spriteSheet, const Ref<Quad>& quad, const int32_t& startingFrame, const Ref<Timestep>& dt);
		GTD_API Animated(const Ref<Quad>& quad, const int32_t& startingFrame, float spriteSheetIndex);
		GTD_API virtual ~Animated();
		GTD_API virtual void Init() override;
		GTD_API virtual void Update() override;
		GTD_API virtual void Activation(bool activate) override;
		GTD_API virtual COMPONENTS GetType() const override { return COMPONENTS::ANIMATED; };

		GTD_API void SetFrame(const int32_t& frameNum);
		GTD_API void NextFrame();
		GTD_API void PreviousFrame();

		GTD_API void Move(const glm::vec2& position);
		GTD_API void MoveTo(const glm::vec2& position);
		GTD_API void Tint(const glm::vec4& color);

		GTD_API const Ref<Quad> GetQuad() const { return m_Quad; }
		GTD_API const float GetSpriteSheetTextureIndex() const { return m_SpriteSheetTextureIndex; }

	private:
		void Frame();

	private:
		Ref<SpriteSheet> m_SpriteSheet;
		float m_SpriteSheetTextureIndex;
		Ref<Quad> m_Quad;
		int32_t m_CurrentFrame;
		Ref<SubTexture> m_CurrentImage;
		bool m_Activated;
		Ref<Timestep> m_DT;
	};
}