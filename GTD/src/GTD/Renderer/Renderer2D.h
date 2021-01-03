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
	class GTD_API Renderer2D
	{
	public:
		static void Init();
		static void Shudtown();

		static void BeginScene(const OrthographicCamera camera);
		static void EndScene();
		static void Flush();

		static void ResetBatch();

		static float SubmitTexture(const Ref<ITexture2D>& texture);

		// Primatives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const Ref<Quad>& quad);
		static void DrawQuad(const Ref<Sprite>& sprite);
		static void DrawQuad(const Tile& tile, const Ref<SpriteSheet> spriteSheet);
		static void DrawQuad(const Ref<TileMap>& tileMap);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<ITexture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<ITexture2D>& texture);
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<ITexture2D>& texture, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size,const Ref<ITexture2D>& texture, const glm::vec4& color, const glm::vec2 textureCoords[4]);

		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const Ref<ITexture2D>& texture, const glm::vec4& color, const float rotation = 0.0f);

		static void Draw(const Animated& animated, float textureIndex);

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