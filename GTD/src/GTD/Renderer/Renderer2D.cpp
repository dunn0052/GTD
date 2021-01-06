#include "../PCH/PCH.h"
#include "Renderer2D.h"
#include "IVertexArray.h"
#include "IShader.h"
#include "../include/Core.h"
#include "OpenGLShader.h"
#include "RenderCommands.h"
#include "../../Vendor/glm/gtc/matrix_transform.hpp"

namespace GTD
{
	constexpr uint32_t NUM_QUAD_VERTICES = 4;
	constexpr uint32_t NUM_QUAD_INDICES = 6;
	constexpr glm::vec2 WHOLE_IMAGE_TEX_COORDS[] =
	{
		{0.0f, 0.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f},
		{0.0f, 1.0f}
	};


	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000; // Max num quads per draw call
		static const uint32_t MaxVertices = MaxQuads * NUM_QUAD_VERTICES; // 4 vertices per quad
		static const uint32_t MaxIndices = MaxVertices * NUM_QUAD_INDICES; // 6 indices per quad
		static const uint32_t MaxTextureSlots = 32; // TODO: render capacity

		Ref<IVertexArray> QuadVertexArray;
		Ref<IVertexBuffer> QuadVertexBuffer;
		Ref<IShader> ComboShader;
		Ref<ITexture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<ITexture2D>, MaxTextureSlots> TextureSlots; // really could be a dictionary
		uint32_t TextureSlotIndex = 1; // slot 0 for white texture
	};

	static Renderer2DData s_Data; // could make pointer if it gets too large

	const std::string Renderer2D::u_ViewProjection = "u_ViewProjection";
	const std::string Renderer2D::u_Transform = "u_Transform";
	const std::string Renderer2D::u_Textures = "u_Textures";
	const std::string Renderer2D::u_Color = "u_Color";
	const std::string Renderer2D::a_Position = "a_Position";
	const std::string Renderer2D::a_TexCoord = "a_TexCoord";
	const std::string Renderer2D::a_Color = "a_Color";
	const std::string Renderer2D::a_TexIndex = "a_TexIndex";

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = IVertexArray::Create();

		s_Data.QuadVertexBuffer.reset(IVertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex)));

		s_Data.QuadVertexBuffer->SetLayout({

			{ GTD::ShaderDataType::FLOAT3, a_Position },
			{ GTD::ShaderDataType::FLOAT4, a_Color},
			{ GTD::ShaderDataType::FLOAT2, a_TexCoord },
			{ GTD::ShaderDataType::FLOAT, a_TexIndex }
			
		});
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

		uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += NUM_QUAD_INDICES)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += NUM_QUAD_VERTICES;
		}

		Ref<IIndexBuffer> quadIndexBuffer;
		quadIndexBuffer.reset(IIndexBuffer::Create(quadIndices, s_Data.MaxIndices));
		s_Data.QuadVertexArray->AddIndexBuffer(quadIndexBuffer);

		/* used for non-texutred quads to sample from  bound to Texture slot 0*/
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture = ITexture2D::Create(1, 1);
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

		int32_t samplers[s_Data.MaxTextureSlots];
		for (uint32_t i = 0; i < s_Data.MaxTextureSlots; i++)
		{
			samplers[i] = i;
		}

		/* Loading shader -- could it be inline instad of loading? */
		s_Data.ComboShader = IShader::Create("assets/shaders/Combo.shdr");
		s_Data.ComboShader->Bind();
		s_Data.ComboShader->Set(u_Textures, samplers, s_Data.MaxTextureSlots);

		// set white texture
		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
	}

	void Renderer2D::Shudtown()
	{
	}

	void Renderer2D::BeginScene(const OrthographicCamera camera)
	{
		s_Data.ComboShader->Bind();
		s_Data.ComboShader->Set(u_ViewProjection, camera.GetViewProjectionMatrix());

		ResetBatch();
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		// bind textures
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
		{
			s_Data.TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);
	}

	void Renderer2D::ResetBatch()
	{

		s_Data.QuadIndexCount = 0;
		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotIndex = 1;
	}

	float Renderer2D::SubmitTexture(const Ref<ITexture2D>& texture)
	{
		float textureIndex = 0.0f;

		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (0.0f == textureIndex)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		return textureIndex;
	}

	//--------------------------------------- GEOMETRY -----------------------------------------//

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(position, size, s_Data.WhiteTexture, color);
	}

	void Renderer2D::DrawQuad(const Ref<Quad>& quad)
	{
		DrawQuad(quad->m_Rect.m_Position, quad->m_Rect.m_Size, quad->m_Color);
	}

	void Renderer2D::DrawQuad(const Ref<Sprite>& sprite)
	{
		DrawQuad(sprite->GetQuad()->m_Rect.m_Position, sprite->GetQuad()->m_Rect.m_Size, sprite->GetImage()->GetSpriteSheet(), sprite->GetQuad()->m_Color, sprite->GetImage()->GetTextureCoordinates());
	}

	void Renderer2D::DrawQuad(const Tile& tile, const Ref<SpriteSheet> spriteSheet)
	{
		DrawQuad(tile.m_Quad.m_Rect.m_Position, tile.m_Quad.m_Rect.m_Size, spriteSheet->GetSpriteSheet(), tile.m_Quad.m_Color, spriteSheet->GetTile(tile.m_PositionID)->GetTextureCoordinates());
	}

	void Renderer2D::DrawQuad(const Ref<TileMap>& tileMap)
	{
		for (auto& tile : tileMap->GetTiles())
		{
			DrawQuad(tile, tileMap->GetSpriteSheet());
		}
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<ITexture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, glm::vec4(1.0f), WHOLE_IMAGE_TEX_COORDS);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<ITexture2D>& texture)
	{
		DrawQuad(position, size, texture, glm::vec4(1.0f));
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<ITexture2D>& texture, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, color, WHOLE_IMAGE_TEX_COORDS);
	}

	/* the one true quad drawer */
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<ITexture2D>& texture, const glm::vec4& color, const glm::vec2 textureCoords[4])
	{
		if (s_Data.QuadIndexCount > Renderer2DData::MaxIndices)
		{
			EndScene();
			ResetBatch();
		}

		float textureIndex = 0.0f;
	
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (0.0f == textureIndex)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
			s_Data.TextureSlotIndex++;
		}

		s_Data.QuadVertexBufferPtr->Position = position;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[0];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[1];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[2];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[3];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		++s_Data.QuadIndexCount;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data.ComboShader->Set(u_Transform, transform);
	}

	// Most of the time don't care about rotation, but is possible here
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const Ref<ITexture2D>& texture, const glm::vec4& color, const float degrees)
	{
		s_Data.ComboShader->Bind();
		s_Data.ComboShader->Set(u_Color, color);

		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(degrees), glm::vec3(0, 0, 1)) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data.ComboShader->Set(u_Transform, transform);
	}

	void Renderer2D::Draw(const Animated& animated, float textureIndex)
	{
		/*
		GTD_ASSERT(textureIndex < s_Data.TextureSlotIndex, "Texture has not been loaded!");

		s_Data.QuadVertexBufferPtr->Position = animated;
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[0];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[1];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[2];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color = color;
		s_Data.QuadVertexBufferPtr->TexCoord = textureCoords[3];
		s_Data.QuadVertexBufferPtr->TexIndex = textureIndex;
		s_Data.QuadVertexBufferPtr++;

		++s_Data.QuadIndexCount;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		s_Data.ComboShader->Set(u_Transform, transform);
		*/
	}
}