#include "..\inlucde\Layer2D.h"
#include "../../Vendor/glm/gtc/matrix_transform.hpp"


Layer2D::Layer2D()
	: Layer("2D"), m_CameraController(1280.f / 720.0f, true), m_Controllers(), m_Color({0.8f, 0.2f, 0.5f, 1.0f}), u_Color("u_Color")
{
	
}

void Layer2D::OnAttach()
{
	m_Director = GTD::CreateRef<GTD::EntityDirector>();
	m_SpriteSheet = GTD::CreateRef<GTD::SpriteSheet>("../Game/spritesheets/autumn.png", glm::vec2{ 32.0f, 32.0f });
	m_SpriteEntitySheet = GTD::CreateRef<GTD::SpriteSheet>("../Game/spritesheets/csBig.png", glm::vec2{ 60.0f, 80.0f });
	m_Quad = GTD::CreateRef<GTD::Quad>( GTD::Rect({0.5f, -0.5f, 0.0f}, {1.0f, 1.0f}) );

	/*
	m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/ICE_TOWN_Tile Layer 1.csv", m_SpriteSheet, -0.02f));
	m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/ICE_TOWN_Tile Layer 2.csv", m_SpriteSheet, -0.01f));
	m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/ICE_TOWN_Tile Layer 3.csv", m_SpriteSheet, 0.00f));
	//m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/ICE_TOWN_Tile Layer 4.csv", m_SpriteSheet, 0.01f));
	m_Maps.push_back(GTD::CreateRef<GTD::TileMap>("../Game/levelData/ICE_TOWN_Tile Layer 5.csv", m_SpriteSheet, 0.02f));
	*/

	GTD::TileMapProps tileMapProps = {};
	tileMapProps.Position = { -6.0f, 0.0f, -0.02f };
	tileMapProps.SpriteSheet = m_SpriteSheet;
	tileMapProps.Tint = glm::vec4(1.0f);
	tileMapProps.TileMapCSVPath = "../Game/levelData/TEST_AUTUMN_Tile Layer 1.csv";


	m_EMaps.push_back(m_Director->Create(tileMapProps));

	GTD::PCProps pcParms = 
	{
		m_SpriteEntitySheet,
		0,
		GTD::Quad(),
		m_Controllers.GetXboxControllerP(0)
	};

	m_PC = m_Director->Create(pcParms);

	tileMapProps.Position = { -6.0f, 0.0f, 0.1f };
	tileMapProps.TileMapCSVPath = "../Game/levelData/TEST_AUTUMN_Tile Layer 2.csv";
	tileMapProps.Tint = {0.5f, 0.0f, 0.8f, 0.8f};

	m_EMaps.push_back(m_Director->Create(tileMapProps));

	m_Sprite = GTD::CreateRef<GTD::Sprite>(m_SpriteSheet->GetTile(141), m_Quad);

	m_PC->AddAction(GTD::ContextCode::UP, [](const GTD::ControlCallbackParams& param) { GTD::PC* pc = (GTD::PC*)param.object; pc->Move({ 0.0f, 0.1f, 0.0f }); });
	m_PC->AddAction(GTD::ContextCode::DOWN, [](const GTD::ControlCallbackParams& param) { GTD::PC* pc = (GTD::PC*)param.object; pc->Move({ 0.0f, -0.1f, 0.0f }); });
	m_PC->AddAction(GTD::ContextCode::LEFT, [](const GTD::ControlCallbackParams& param) { GTD::PC* pc = (GTD::PC*)param.object; pc->Move({ -0.1f, 0.0f, 0.0f }); });
	m_PC->AddAction(GTD::ContextCode::RIGHT, [](const GTD::ControlCallbackParams& param) { GTD::PC* pc = (GTD::PC*)param.object; pc->Move({ 0.1f, 0.0f, 0.0f }); });
	m_PC->AddAction(GTD::ContextCode::LT, [](const GTD::ControlCallbackParams& param) { GTD::PC* pc = (GTD::PC*)param.object; pc->NextFrame(); });
	m_PC->AddAction(GTD::ContextCode::RT, [](const GTD::ControlCallbackParams& param) { GTD::PC* pc = (GTD::PC*)param.object; pc->Kill(); });
}

void Layer2D::OnUpdate(GTD::Timestep dt)
{

	m_Controllers.OnUpdate();
	m_CameraController.OnUpdate(dt, m_Controllers);

	GTD::XboxController controller = m_Controllers.GetXboxController(0);

	GTD::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.5f });
	GTD::RenderCommand::Clear();

	GTD::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	m_Director->Update();

	GTD::Renderer2D::DrawQuad(m_Sprite);

	GTD::Renderer2D::EndScene();
}

void Layer2D::OnDetach()
{
}


void Layer2D::OnEvent(GTD::Event& e)
{
	m_CameraController.OnEvent(e);
}


