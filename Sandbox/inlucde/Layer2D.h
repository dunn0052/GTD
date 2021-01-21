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

	bool OnMouseDown(GTD::MouseButtonPressedEvent& e);
	bool OnMouseMove(GTD::MouseMovedEvent& e);
	bool OnWindowResize(GTD::WindowResizeEvent& e);

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

	GTD::Ref<GTD::Solid> m_Solid;

	std::vector<GTD::Ref<GTD::Rect>> m_RectCollisions;
	GTD::Ref<GTD::Rect> m_CollisionRect;
	glm::vec2 m_WindowSize;

	glm::vec4 m_Color;
	GTD::Ref<GTD::Quad> m_Quad;
};