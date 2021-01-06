#pragma once
#include <GTD.h>

class Layer2D : public GTD::Layer
{
public:
	Layer2D();
	virtual ~Layer2D() = default;

	virtual void OnUpdate(const GTD::Ref<GTD::Timestep>& dt) override;
	virtual void OnEvent(GTD::Event& e) override;

	virtual void OnAttach() override; // similar to a constructor, but layer stack can do it
	virtual void OnDetach() override;

private:
	GTD::OrthographicCameraController m_CameraController;
	GTD::Controllers m_Controllers;

	// temp
	GTD::Ref<GTD::SpriteSheet> m_SpriteSheet;
	GTD::Ref<GTD::SpriteSheet> m_SpriteEntitySheet;
	std::vector<GTD::Ref<GTD::TileMapE>> m_EMaps;
	GTD::Ref<GTD::TileLayer> m_TileLayer;
	GTD::Ref<GTD::Sprite> m_Sprite;
	GTD::Ref<GTD::EntityDirector> m_Director;
	GTD::Ref<GTD::SpriteE> m_EntitySprite;
	GTD::Ref<GTD::PC> m_PC;

	glm::vec4 m_Color;
	const std::string u_Color;
	GTD::Ref<GTD::Quad> m_Quad;
};