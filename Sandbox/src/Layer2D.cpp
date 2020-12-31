#include "..\inlucde\Layer2D.h"
#include "../../Vendor/glm/gtc/matrix_transform.hpp"


Layer2D::Layer2D()
	: Layer("2D"), m_CameraController(1280.f / 720.0f, true), m_Controllers(), m_Color({0.8f, 0.2f, 0.5f, 1.0f}), u_Color("u_Color")
{
	
}

void Layer2D::OnAttach()
{
	m_Texture = GTD::ITexture2D::Create("assets/images/mariot.png");
	m_SpriteSheet = GTD::CreateRef<GTD::SpriteSheet>("../Game/spritesheets/autumn.png", glm::vec2{ 32.0, 32.0 });
	m_Quad = GTD::CreateRef<GTD::Quad>( GTD::Rect({0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}) );

	/*
	m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/ICE_TOWN_Tile Layer 1.csv", m_SpriteSheet, -0.02f));
	m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/ICE_TOWN_Tile Layer 2.csv", m_SpriteSheet, -0.01f));
	m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/ICE_TOWN_Tile Layer 3.csv", m_SpriteSheet, 0.00f));
	//m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/ICE_TOWN_Tile Layer 4.csv", m_SpriteSheet, 0.01f));
	m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/ICE_TOWN_Tile Layer 5.csv", m_SpriteSheet, 0.02f));
	*/

	m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/TEST_AUTUMN_Tile Layer 1.csv", m_SpriteSheet, -0.02f));
	m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/TEST_AUTUMN_Tile Layer 2.csv", m_SpriteSheet, -0.01f));


	for (auto& map : m_Maps)
	{
		map->SetRelativePosition({ -6.0, -4.0f, 0.0f });
	}
	
	m_Tile = GTD::Tile({ 0.0f ,0.0f ,0.0f }, 0);

	m_Maps[1]->SetTint({ 0.5f, 0.0f, 0.8f, 0.3f });

	m_Sprite = GTD::CreateRef<GTD::Sprite>(m_SpriteSheet->GetTile(141), m_Quad);
}

void Layer2D::OnUpdate(GTD::Timestep dt)
{

	m_Controllers.OnUpdate();
	m_CameraController.OnUpdate(dt, m_Controllers);

	GTD::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.5f });
	GTD::RenderCommand::Clear();

	GTD::Renderer2D::BeginScene(m_CameraController.GetCamera());
	for (auto& map : m_Maps)
	{
		GTD::Renderer2D::DrawQuad(map);
	}
	//GTD::Renderer2D::DrawQuad(m_Tile, m_SpriteSheet);

	//GTD::Renderer2D::DrawQuad(m_Tile);

	//GTD::Renderer2D::DrawQuad(m_Sprite);

	//GTD::Renderer2D::DrawQuad({ 0.0f, 0.0f}, { 1.0f, 1.0f }, m_Texture);
	//GTD::Renderer2D::DrawQuad({ -0.5f, -0.5f, -0.01f }, { 1.0f, 1.0f }, m_Texture);
	//GTD::Renderer2D::DrawQuad(m_Quad);

	GTD::Renderer2D::EndScene();
	GTD::Renderer2D::Flush();
}

void Layer2D::OnDetach()
{
}


void Layer2D::OnEvent(GTD::Event& e)
{
	m_CameraController.OnEvent(e);
}


