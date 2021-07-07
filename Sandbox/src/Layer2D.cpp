#include "..\inlucde\Layer2D.h"
#include "../../Vendor/glm/gtc/matrix_transform.hpp"


Layer2D::Layer2D()
	: Layer("2D"), m_Controllers(), m_Color({ 1.0f, 1.0f, 1.0f, 1.0f }), m_WindowSize({1280.0f, 720.0f})
{
}

void Layer2D::OnAttach()
{
	m_WindowSize = { 1280.f, 720.0f };
	m_CameraController = GTD::OrthographicCameraController(m_WindowSize.x / m_WindowSize.y, m_DT, true);
	m_Director = GTD::CreateRef<GTD::EntityDirector>(m_DT);
	m_SpriteSheet = GTD::CreateRef<GTD::SpriteSheet>("../GameData/spritesheets/autumn.png", glm::vec2{ 32.0f, 32.0f });
	m_SpriteEntitySheet = GTD::CreateRef<GTD::SpriteSheet>("../GameData/spritesheets/csBig.png", glm::vec2{ 60.0f, 80.0f });

	GTD::TileMapProps tileMapProps = {};
	tileMapProps.Position = { -6.0f, 0.0f, 0.001f };
	tileMapProps.SpriteSheet = m_SpriteSheet;
	tileMapProps.Tint = glm::vec4(1.0f);
	tileMapProps.TileMapCSVPath = "../GameData/levelData/TEST_AUTUMN_Tile Layer 1.csv";
	tileMapProps.DT = m_DT;


	m_EMaps.push_back(m_Director->Create(tileMapProps));

	GTD::PCProps pcParms =
	{
		m_SpriteEntitySheet,
		GTD::CreateRef<GTD::Quad>(GTD::Rectangle({0.0f, 0.0f, 0.002f}, {0.5f, 0.5f})),
		true,
		m_DT,
		0,
		m_Controllers.GetXboxControllerP(0),
		2.0f,
		glm::vec3{0.0f, 0.0f, 0.0f}
	};

	GTD::PCProps pc;

	m_PC = m_Director->Create(pcParms);

	GTD::TileLayerProps tileLayerProps = {};
	tileLayerProps.DT = m_DT;
	tileLayerProps.Quad = GTD::CreateRef<GTD::Quad>(GTD::Rectangle({ -6.0f, 0.0f, 0.003f }), m_Color);
	tileLayerProps.Solid = true;
	tileLayerProps.SpriteSheet = m_SpriteSheet;
	tileLayerProps.TileMapCSVPath = "../GameData/levelData/TEST_AUTUMN_Tile Layer 2.csv";

	
	tileMapProps.Position = { -6.0f, 0.0f, 0.1f };
	tileMapProps.TileMapCSVPath = "../GameData/levelData/TEST_AUTUMN_Tile Layer 3.csv";
	tileMapProps.Tint = m_Color;


	tileLayerProps.TileMapCSVPath = "../GameData/levelData/TEST_AUTUMN_Tile Layer 2.csv";

	m_TileLayer = m_Director->Create(tileLayerProps);
	
	m_EMaps.push_back(m_Director->Create(tileMapProps));

	m_PC->SetFrameRange("DOWN", 0, 3);
	m_PC->SetFrameRange("LEFT", 3, 6);
	m_PC->SetFrameRange("RIGHT", 6, 9);
	m_PC->SetFrameRange("UP", 9, 12);

	m_PC->SetFrameRange("DOWN_NEUTRAL", 0, 0);
	m_PC->SetFrameRange("LEFT_NEUTRAL", 3, 3);
	m_PC->SetFrameRange("RIGHT_NEUTRAL", 6, 6);
	m_PC->SetFrameRange("UP_NEUTRAL", 9, 9);

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
				//std::cout << "BUTTON STATUS HELD: " << buttonStatus << std::endl;
				return;
			}
			case GTD::BUTTON_PRESSED:
			{
				//std::cout << "BUTTON STATUS PRESSED: " << buttonStatus << std::endl;
				ent->ChangYDirection(1.0f);
				ent->TryChangeFrameRange("UP");
				return;
			}
			case GTD::BUTTON_RELEASED:
			{
				//std::cout << "BUTTON STATUS RELEASED: " << buttonStatus << std::endl;
				ent->ChangYDirection(0.0f);
				ent->TryChangeFrameRange("UP_NEUTRAL");
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
				//std::cout << "BUTTON STATUS HELD: " << buttonStatus << std::endl;
				return;
			}
			case GTD::BUTTON_PRESSED:
			{
				//std::cout << "BUTTON STATUS PRESSED: " << buttonStatus << std::endl;
				ent->ChangYDirection(-1.0f);
				ent->TryChangeFrameRange("DOWN");
				return;
			}
			case GTD::BUTTON_RELEASED:
			{
				//std::cout << "BUTTON STATUS RELEASED: " << buttonStatus << std::endl;
				ent->ChangYDirection(0.0f);
				ent->TryChangeFrameRange("DOWN_NEUTRAL");
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
				//std::cout << "BUTTON STATUS HELD: " << buttonStatus << std::endl;
				return;
			}
			case GTD::BUTTON_PRESSED:
			{
				//std::cout << "BUTTON STATUS PRESSED: " << buttonStatus << std::endl;
				ent->ChangXDirection(-1.0f);
				ent->TryChangeFrameRange("LEFT");
				return;
			}
			case GTD::BUTTON_RELEASED:
			{
				//std::cout << "BUTTON STATUS RELEASED: " << buttonStatus << std::endl;
				ent->ChangXDirection(0.0f);
				ent->TryChangeFrameRange("LEFT_NEUTRAL");
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
				//std::cout << "BUTTON STATUS HELD: " << buttonStatus << std::endl;
				return;
			}
			case GTD::BUTTON_PRESSED:
			{
				//std::cout << "BUTTON STATUS PRESSED: " << buttonStatus << std::endl;
				ent->ChangXDirection(1.0f);
				ent->TryChangeFrameRange("RIGHT");
				return;
			}
			case GTD::BUTTON_RELEASED:
			{
				//std::cout << "BUTTON STATUS RELEASED: " << buttonStatus << std::endl;
				ent->ChangXDirection(0.0f);
				ent->TryChangeFrameRange("RIGHT_NEUTRAL");
				return;
			}
			}
			// use params and buttonStatus to your heart's content here
		}
	);
	
	m_CameraController.SetCameraPosition({ 0.0f, 5.0f, 0.0f });

	GTD::SpriteParamsE spriteParms = {};

	spriteParms.DT = m_DT;
	spriteParms.IsSolid = true;
	spriteParms.Quad = GTD::CreateRef<GTD::Quad>(GTD::Rectangle({ -10.0f, 0.0f, 0.003f }), m_Color);
	spriteParms.StartingFrame = 3;
	spriteParms.SpriteSheet = m_SpriteEntitySheet;

	m_EntitySprite = m_Director->Create(spriteParms);
	//m_RectCollisions.push_back(GTD::CreateRef<GTD::Rect>(glm::vec2({ 0.0f, 5.0f }), glm::vec2({ 1.0f, 1.0f })));
	//m_RectCollisions.push_back(GTD::CreateRef<GTD::Rect>(glm::vec2(0.0f), glm::vec2({2.0f, 5.0f})));
	//m_CollisionRect = GTD::CreateRef<GTD::Rect>(glm::vec2({ 0.0f, 0.0f}), glm::vec2({ 1.0f, 1.0f }));
	m_CameraController.Follow(m_PC);
}

void Layer2D::OnUpdate(const GTD::Ref<GTD::Timestep>& dt)
{

	m_Controllers.OnUpdate();
	//m_CameraController.OnUpdate(m_Controllers);

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
	/*
	m_CollisionRect->SetVelocity({ 0.0f, 0.0f });
	if (controller.m_CurrentButtons[GTD::ContextCode::UP])
	{
		m_CollisionRect->AddY(1.0f);
		//m_CollisionRect->SetPosition(m_CollisionRect->Position() + glm::vec2({ 0.0f, 1.0f }) *m_DT->GetSecond());
	}
	if (controller.m_CurrentButtons[GTD::ContextCode::DOWN])
	{
		m_CollisionRect->AddY(-1.0f);
		//m_CollisionRect->SetPosition(m_CollisionRect->Position() + glm::vec2({ 0.0f, -1.0f }) * m_DT->GetSecond());
	}
	if (controller.m_CurrentButtons[GTD::ContextCode::LEFT])
	{
		m_CollisionRect->AddX(-1.0f);
		//m_CollisionRect->SetPosition(m_CollisionRect->Position() + glm::vec2({ -1.0f, 0.0f }) * m_DT->GetSecond());
	}
	if (controller.m_CurrentButtons[GTD::ContextCode::RIGHT])
	{
		m_CollisionRect->AddX(1.0f);
		//m_CollisionRect->SetPosition(m_CollisionRect->Position() + glm::vec2({ 1.0f, 0.0f }) * m_DT->GetSecond());
	
	}

	m_CollisionRect->SetPosition(m_CollisionRect->Position() + m_CollisionRect->Velocity() * m_DT->GetSecond());


	glm::vec2 contactPoint = glm::vec2(0.0f);
	glm::vec2 contactNormal = glm::vec2(0.0f);
	glm::vec4 color{0.0f, 1.0f, 0.0f, 1.0f};
	float time = 0.0f;
	float timestep = m_DT->GetSecond();

	for (auto rect : m_RectCollisions)
	{
		if (rect->DynamicRectCollideRect(*m_CollisionRect, contactPoint, contactNormal, time, timestep))
		{
			m_CollisionRect->SetVelocity(m_CollisionRect->Velocity() + contactNormal *
				glm::vec2(std::abs(m_CollisionRect->Velocity().x), std::abs(m_CollisionRect->Velocity().y)) * (1 - time)); // calculate dot product instead

			m_CollisionRect->SetPosition(m_CollisionRect->Position() + m_CollisionRect->Velocity() * m_DT->GetSecond()); // reverse the original movement

			color = { 1.0f, 0.0f, 0.0f, 1.0f };
		}
		else
		{
			color = { 0.0f, 1.0f, 0.0f, 1.0f };
		}
		GTD::Renderer2D::Draw(rect, color);
	}

	GTD::Renderer2D::Draw(m_CollisionRect, m_Color);
	*/

	m_CameraController.OnUpdate();

	GTD::Renderer2D::EndScene();
}

void Layer2D::OnDetach()
{
}

bool Layer2D::OnMouseDown(GTD::MouseButtonPressedEvent& e)
{
	return false;
}

bool Layer2D::OnMouseMove(GTD::MouseMovedEvent& e)
{
	//m_CollisionRect->SetPosition({ (e.GetX() / m_WindowSize.x - 0.5f) * m_CameraController.GetZoomLevel() * m_WindowSize.x / m_WindowSize.y , (-e.GetY() / m_WindowSize.y + 5.5) * m_CameraController.GetZoomLevel() * m_WindowSize.x / m_WindowSize.y });
	//std::cout << "Mouse Screen Coords (" << (e.GetX() / m_WindowSize.x - 0.5f) * m_CameraController.GetZoomLevel() << ", " << (-e.GetY() / m_WindowSize.y + 5.5) * m_CameraController.GetZoomLevel() << ") " << std::endl;

	/*
	if (m_CollisionRect->PointInRect({ e.GetX() / m_WindowSize.x, e.GetY() / m_WindowSize.y }))
	{
		m_Color = { 1.0f, 0.0f, 0.0f, 1.0f };
	}
	else
	{
		m_Color = { 0.0f, 1.0f, 0.0f, 1.0f };
	}
	*/
	return false;
}

bool Layer2D::OnWindowResize(GTD::WindowResizeEvent& e)
{
	m_WindowSize = { e.GetWidth(), e.GetHeight() };
	return false;
}


void Layer2D::OnEvent(GTD::Event& e)
{
	GTD::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<GTD::WindowResizeEvent>(BIND_EVENT_FTN(Layer2D::OnWindowResize));
	dispatcher.Dispatch<GTD::MouseMovedEvent>(BIND_EVENT_FTN(Layer2D::OnMouseMove));
	
	m_CameraController.OnEvent(e);

}



