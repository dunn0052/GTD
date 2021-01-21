#include "../../PCH/PCH.h"
#include "Drawable.h"

namespace GTD
{
	Drawable::Drawable(const Ref<SubTexture>& texture, const Ref<Quad> quad) :
		m_Active(true), m_SubTexture(texture), m_Quad(quad)
	{
		Init();
	}

	Drawable::Drawable() :
		m_Active(false), m_SubTexture(), m_Quad()
	{
	}

	Drawable::~Drawable()
	{
	}

	void GTD::Drawable::Init()
	{
		m_Active = true;
	}

	void GTD::Drawable::Update()
	{
		if (m_Active)
		{
			Renderer2D::DrawQuad(m_Quad->m_Rect.m_Position, m_Quad->m_Rect.m_Size, m_SubTexture->GetSpriteSheet(), m_Quad->m_Color, m_SubTexture->GetTextureCoordinates());
		}
	}
	void Drawable::Move(const glm::vec3& position)
	{
		m_Quad->m_Rect.m_Position += position;
	}
	void Drawable::MoveTo(const glm::vec3& position)
	{
		m_Quad->m_Rect.m_Position = position;
	}
	void Drawable::Tint(const glm::vec4& color)
	{
		m_Quad->m_Color = color;
	}
}
