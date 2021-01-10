#include "..\inlucde\Layer2D.h"
#include "../../Vendor/glm/gtc/matrix_transform.hpp"


Layer2D::Layer2D()
	: Layer("2D"), m_Controllers(), m_Color({1.0f, 1.0f, 1.0f, 1.0f}), u_Color("u_Color")
{
}

void Layer2D::OnAttach()
{
	m_CameraController = GTD::OrthographicCameraController(1280.f / 720.0f, m_DT, true);
	m_Director = GTD::CreateRef<GTD::EntityDirector>();
	m_SpriteSheet = GTD::CreateRef<GTD::SpriteSheet>("../Game/spritesheets/autumn.png", glm::vec2{ 32.0f, 32.0f });
	m_SpriteEntitySheet = GTD::CreateRef<GTD::SpriteSheet>("../Game/spritesheets/csBig.png", glm::vec2{ 60.0f, 80.0f });

	GTD::TileMapProps tileMapProps = {};
	tileMapProps.Position = { -6.0f, 0.0f, 0.001f };
	tileMapProps.SpriteSheet = m_SpriteSheet;
	tileMapProps.Tint = glm::vec4(1.0f);
	tileMapProps.TileMapCSVPath = "../Game/levelData/TEST_AUTUMN_Tile Layer 1.csv";
	tileMapProps.DT = m_DT;


	m_EMaps.push_back(m_Director->Create(tileMapProps));

	GTD::PCProps pcParms =
	{
		m_SpriteEntitySheet,
		GTD::CreateRef<GTD::Quad>(GTD::Rectangle({0.0f, 0.0f, 0.002f})),
		true,
		nullptr,
		m_DT,
		0,
		m_Controllers.GetXboxControllerP(0),
		5.0f,
		glm::vec3{0.0f, 0.0f, 0.0f}
	};

	m_PC = m_Director->Create(pcParms);

	GTD::TileLayerProps tileLayerProps = {};
	tileLayerProps.DT = m_DT;
	tileLayerProps.Quad = GTD::CreateRef<GTD::Quad>(GTD::Rectangle({ -6.0f, 0.0f, 0.003f }), m_Color);
	tileLayerProps.Solid = true;
	tileLayerProps.SpriteSheet = m_SpriteSheet;
	tileLayerProps.TileMapCSVPath = "../Game/levelData/TEST_AUTUMN_Tile Layer 2.csv";

	
	tileMapProps.Position = { -6.0f, 0.0f, 0.1f };
	tileMapProps.TileMapCSVPath = "../Game/levelData/TEST_AUTUMN_Tile Layer 2.csv";
	tileMapProps.Tint = m_Color;

	//m_EMaps.push_back(m_Director->Create(tileMapProps));


	m_TileLayer = m_Director->Create(tileLayerProps);
	 
	m_PC->SetAction
	(
		GTD::ContextCode::UP,

		[](const GTD::ControlCallbackParams& params, unsigned char buttonStatus)
		{
			GTD::PC* ent = (GTD::PC*)params.object;
			switch (buttonStatus)
			{
			case GTD::BUTTON_HELD:
			{
				std::cout << "BUTTON STATUS HELD: " << buttonStatus << std::endl;
				return;
			}
			case GTD::BUTTON_PRESSED:
			{
				std::cout << "BUTTON STATUS PRESSED: " << buttonStatus << std::endl;
				ent->ChangYDirection(1.0f);
				return;
			}
			case GTD::BUTTON_RELEASED:
			{
				std::cout << "BUTTON STATUS RELEASED: " << buttonStatus << std::endl;
				ent->ChangYDirection(0.0f);
				return;
			}
			}
			// use params and buttonStatus to your heart's content here
		}
	);

	m_PC->SetAction
	(
		GTD::ContextCode::DOWN,

		[](const GTD::ControlCallbackParams& params, unsigned char buttonStatus)
		{
			GTD::PC* ent = (GTD::PC*)params.object;
			switch (buttonStatus)
			{
			case GTD::BUTTON_HELD:
			{
				std::cout << "BUTTON STATUS HELD: " << buttonStatus << std::endl;
				return;
			}
			case GTD::BUTTON_PRESSED:
			{
				std::cout << "BUTTON STATUS PRESSED: " << buttonStatus << std::endl;
				ent->ChangYDirection(-1.0f);
				return;
			}
			case GTD::BUTTON_RELEASED:
			{
				std::cout << "BUTTON STATUS RELEASED: " << buttonStatus << std::endl;
				ent->ChangYDirection(0.0f);
				return;
			}
			}
			// use params and buttonStatus to your heart's content here
		}
	);

	m_PC->SetAction
	(
		GTD::ContextCode::LEFT,

		[](const GTD::ControlCallbackParams& params, unsigned char buttonStatus)
		{
			GTD::PC* ent = (GTD::PC*)params.object;
			switch (buttonStatus)
			{
			case GTD::BUTTON_HELD:
			{
				std::cout << "BUTTON STATUS HELD: " << buttonStatus << std::endl;
				return;
			}
			case GTD::BUTTON_PRESSED:
			{
				std::cout << "BUTTON STATUS PRESSED: " << buttonStatus << std::endl;
				ent->ChangXDirection(-1.0f);
				return;
			}
			case GTD::BUTTON_RELEASED:
			{
				std::cout << "BUTTON STATUS RELEASED: " << buttonStatus << std::endl;
				ent->ChangXDirection(0.0f);
				return;
			}
			}
			// use params and buttonStatus to your heart's content here
		}
	);

	m_PC->SetAction
	(
		GTD::ContextCode::RIGHT,

		[](const GTD::ControlCallbackParams& params, unsigned char buttonStatus)
		{
			GTD::PC* ent = (GTD::PC*)params.object;
			switch (buttonStatus)
			{
			case GTD::BUTTON_HELD:
			{
				std::cout << "BUTTON STATUS HELD: " << buttonStatus << std::endl;
				return;
			}
			case GTD::BUTTON_PRESSED:
			{
				std::cout << "BUTTON STATUS PRESSED: " << buttonStatus << std::endl;
				ent->ChangXDirection(1.0f);
				return;
			}
			case GTD::BUTTON_RELEASED:
			{
				std::cout << "BUTTON STATUS RELEASED: " << buttonStatus << std::endl;
				ent->ChangXDirection(0.0f);
				return;
			}
			}
			// use params and buttonStatus to your heart's content here
		}
	);
	
	m_CameraController.SetCameraPosition({ 0.0f, 5.0f, 0.0f });
}

void Layer2D::OnUpdate(const GTD::Ref<GTD::Timestep>& dt)
{

	m_Controllers.OnUpdate();
	m_CameraController.OnUpdate(m_Controllers);

	GTD::XboxController controller = m_Controllers.GetXboxController(0);

	GTD::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 0.5f });
	GTD::RenderCommand::Clear();

	GTD::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	if (controller.m_CurrentButtons[GTD::ContextCode::A])
	{
		m_Color = m_Color - glm::vec4{0.0f, -0.01f, 0.001f, -0.1f};
		m_TileLayer->SetTint(m_Color);
	}
	else if (controller.m_CurrentButtons[GTD::ContextCode::B])
	{
		m_Color = m_Color - glm::vec4{ 0.0f, 0.01f, -0.001f, 0.1f };
		m_TileLayer->SetTint(m_Color);
	}
	m_Director->Update();

	GTD::Renderer2D::EndScene();
}

void Layer2D::OnDetach()
{
}


void Layer2D::OnEvent(GTD::Event& e)
{
	m_CameraController.OnEvent(e);
}


