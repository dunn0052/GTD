#pragma once
#include <GTD.h>

class Layer2D : public GTD::Layer
{
public:
	Layer2D();
	virtual ~Layer2D() = default;

	virtual void OnUpdate(GTD::Timestep dt) override;
	virtual void OnEvent(GTD::Event& e) override;

	virtual void OnAttach() override; // similar to a constructor, but layer stack can do it
	virtual void OnDetach() override;
private:
	GTD::OrthographicCameraController m_CameraController;
	GTD::Controllers m_Controllers;

	// temp
	GTD::Ref<GTD::ITexture2D> m_Texture;
	GTD::Ref<GTD::SpriteSheet> m_SpriteSheet;
	std::vector<GTD::Ref<GTD::TileMap>> m_Maps;
	GTD::Tile m_Tile;
	GTD::Ref<GTD::Sprite> m_Sprite;
	GTD::Ref<GTD::IShader> m_FlatColorShader;
	GTD::Ref<GTD::IVertexArray> m_VertexArray;
	glm::vec4 m_Color;
	const std::string u_Color;
	GTD::Ref<GTD::Quad> m_Quad;
};