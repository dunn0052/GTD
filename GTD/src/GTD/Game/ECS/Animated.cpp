#include "../../PCH/PCH.h"
#include "Animated.h"
#include "../../Renderer/Renderer2D.h"

namespace GTD
{
	Animated::Animated(const Ref<SpriteSheet>& spriteSheet, const Ref<Quad>& quad, const int32_t& startingFrame, const Ref<Timestep>& dt) :
		m_SpriteSheet(spriteSheet), m_Quad(quad), m_CurrentFrame(startingFrame),
		m_CurrentImage(m_SpriteSheet->GetTile(startingFrame)), m_Activated(true), m_SpriteSheetTextureIndex(0.0f), m_DT(dt)
	{
		Init();
	}

	Animated::Animated(const Ref<Quad>& quad, const int32_t& startingFrame, float spriteSheetIndex) :
		m_SpriteSheet(), m_Quad(quad), m_CurrentFrame(startingFrame),
		m_CurrentImage(m_SpriteSheet->GetTile(startingFrame)), m_Activated(true), m_SpriteSheetTextureIndex(spriteSheetIndex)
	{
		Init();
	}

	Animated::~Animated()
	{

	}

	void Animated::Init()
	{
	}

	void Animated::Update()
	{
		if (m_Activated)
		{
			Renderer2D::DrawQuad(m_Quad->m_Rect.m_Position, m_Quad->m_Rect.m_Size, m_SpriteSheet->GetSpriteSheet(), m_Quad->m_Color, m_CurrentImage->GetTextureCoordinates());
		}
	}

	void Animated::Activation(bool activate)
	{
		m_Activated = activate;
	}

	void Animated::Frame()
	{
		m_CurrentImage = m_SpriteSheet->GetTile(m_CurrentFrame);
	}

	void Animated::SetFrame(const int32_t& frameNum)
	{
		m_CurrentFrame = frameNum % m_SpriteSheet->GetNumTiles();
		Frame();
	}

	void Animated::NextFrame()
	{
		m_CurrentFrame = (m_CurrentFrame + 1) % m_SpriteSheet->GetNumTiles();
		Frame();
	}

	void Animated::PreviousFrame()
	{
		m_CurrentFrame = (m_CurrentFrame - 1) % m_SpriteSheet->GetNumTiles();
		Frame();
	}

	void Animated::Move(const glm::vec2& position)
	{
		m_Quad->m_Rect.m_Position += glm::vec3{ position.x, position.y, m_Quad->m_Rect.m_Position.z};
	}

	void Animated::MoveTo(const glm::vec2& position)
	{
		m_Quad->m_Rect.m_Position = { position, m_Quad->m_Rect.m_Position.z };
	}

	void Animated::Tint(const glm::vec4& color)
	{
		m_Quad->m_Color = color;
	}
}