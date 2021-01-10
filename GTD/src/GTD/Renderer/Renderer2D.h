#pragma once
#include "OrthographicCamera.h"
#include "ITexture.h"
#include "../include/Rect.h"
#include "../Game/Sprite.h"
#include "../Game/TIle.h"
#include "../Game/TIleMap.h"
#include "../Game/ECS/Animated.h"

namespace GTD
{
	class Renderer2D
	{
	public:
		GTD_API static void Init();
		GTD_API static void Shudtown();

		GTD_API static void BeginScene(const OrthographicCamera camera);
		GTD_API static void EndScene();
		GTD_API static void Flush();

		GTD_API static void ResetBatch();

		GTD_API static float SubmitTexture(const Ref<ITexture2D>& texture);

		// Primatives
		GTD_API static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		GTD_API static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		GTD_API static void DrawQuad(const Ref<Quad>& quad);
		GTD_API static void DrawQuad(const Ref<Sprite>& sprite);
		GTD_API static void DrawQuad(const Tile& tile, const Ref<SpriteSheet> spriteSheet);
		GTD_API static void DrawQuad(const Ref<TileMap>& tileMap);

		GTD_API static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<ITexture2D>& texture);
		GTD_API static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<ITexture2D>& texture);
		
		GTD_API static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<ITexture2D>& texture, const glm::vec4& color);
		GTD_API static void DrawQuad(const glm::vec3& position, const glm::vec2& size,const Ref<ITexture2D>& texture, const glm::vec4& color, const glm::vec2 textureCoords[4]);

		GTD_API static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const Ref<ITexture2D>& texture, const glm::vec4& color, const float rotation = 0.0f);

		GTD_API static void Draw(const Animated& animated, float textureIndex);

	private:
		static const std::string u_ViewProjection;
		static const std::string u_Transform;
		static const std::string u_Textures;
		static const std::string u_Color;
		static const std::string a_Position;
		static const std::string a_TexCoord;
		static const std::string a_Color;
		static const std::string a_TexIndex;
	};
}