#include "../../PCH/PCH.h"
#include "Animated.h"
#include "../../Renderer/Renderer2D.h"

namespace GTD
{
	Animated::Animated(const Ref<SpriteSheet>& spriteSheet, const Ref<Quad>& quad, const int32_t& startingFrame, const Ref<Timestep>& dt, const float& frameTime) :
		m_SpriteSheet(spriteSheet), m_Quad(quad), m_CurrentFrame(startingFrame),
		m_CurrentImage(m_SpriteSheet->GetTile(startingFrame)), m_Activated(true), m_SpriteSheetTextureIndex(0.0f), m_DT(dt), m_FrameUpdateTime(frameTime), m_FrameChangeTimer(0.0f)
	{
		Init();
	}

	Animated::Animated(const Ref<Quad>& quad, const int32_t& startingFrame, float spriteSheetIndex) :
		m_SpriteSheet(), m_Quad(quad), m_CurrentFrame(startingFrame),
		m_CurrentImage(m_SpriteSheet->GetTile(startingFrame)), m_Activated(true), m_SpriteSheetTextureIndex(spriteSheetIndex), m_FrameChangeTimer(0.0f), m_FrameUpdateTime(0.2f)
	{
		Init();
	}

	Animated::~Animated()
	{

	}

	void Animated::Init()
	{
		m_AnimationSequenceKey = "DEFAULT";
		AddFrameRange(m_AnimationSequenceKey, 0, 0);
		UpdateFrame = &Animated::SingleFrameUpdate;
	}

	void Animated::Update()
	{
		if (m_Activated)
		{

			(this->*UpdateFrame)(); // updates to next frame if multiple are defined otherwise do nothing because there is only a single frame

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

	void Animated::MultiFrameUpdate()
	{
		// add the time delta and check if it exceeds the max time alloted to change
		m_FrameChangeTimer += *m_DT;
		if (m_FrameChangeTimer >= m_FrameUpdateTime)
		{
			// The animation sequence key tells us which frame range to use. This cycles through that that range.
			m_CurrentFrame = (m_CurrentFrame + 1) % std::get<1>(*m_FrameRanges[m_AnimationSequenceKey]) + std::get<0>(*m_FrameRanges[m_AnimationSequenceKey]); // % div by 0 here need to fix
			m_FrameChangeTimer = 0.0f; // reset timer
			Frame();
		}
	}

	void Animated::SingleFrameUpdate()
	{
		
	}

	void Animated::SetFrame(const int32_t& frameNum)
	{
		m_CurrentFrame = frameNum % m_SpriteSheet->GetNumTiles();
		Frame();
	}

	void Animated::AddFrameRange(const std::string& key, const int32_t& beginningFrame, const int32_t& endingFrame)
	{
		GTD_ASSERT(endingFrame >= beginningFrame || endingFrame > m_SpriteSheet->GetNumTiles() || beginningFrame < 0, "Invalid frame range!");
		m_FrameRanges[key] = CreateRef<FrameRange>(beginningFrame, endingFrame - beginningFrame);
	}

	bool Animated::TryChangeFrameRange(const std::string& key)
	{
		if (m_FrameRanges.find(key) != m_FrameRanges.end())
		{
			m_AnimationSequenceKey = key;
			if (0 != std::get<1>(*m_FrameRanges[m_AnimationSequenceKey]))
			{
				UpdateFrame = &Animated::MultiFrameUpdate; // if we changed to a state that has more than 1 state then we need to calculate when to change frames
			}
			else
			{
				UpdateFrame = &Animated::SingleFrameUpdate; // does not need to figure out if a new frame is needed
			}

			return true;
		}
		return false;
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