#pragma once
#include "ECS/Entity.h"
#include "ECS/Animated.h"
#include "SpriteSheet.h"
#include "../Util/CSVLoader.h"
#include "../include/Core.h"
#include "TileE.h"


namespace GTD
{
	struct TileMapProps
	{
		Ref<SpriteSheet> SpriteSheet;
		Ref<Timestep> DT;
		std::string TileMapCSVPath;
		glm::vec4 Tint;
		glm::vec3 Position;
	};

	class TileMapE : public Entity
	{
	public:
		GTD_API TileMapE();
		GTD_API virtual ~TileMapE() override;

		GTD_API virtual void AddComponent(const GetComponentCallback& ret, const GetComponentCallbackParams& params, COMPONENTS type) override;
		GTD_API virtual void Init() override;

		GTD_API virtual bool const IsActive() override;
		GTD_API virtual void Activated(bool activated) override;
		GTD_API virtual void Kill() override;


		GTD_API const std::vector<Ref<Animated>> GetTiles() const { return m_Tiles; }
		GTD_API const Ref<SpriteSheet> GetSpriteSheet() const { return m_SpriteSheet; }

		GTD_API void SetTint(const glm::vec4& tint)
		{ 
			m_Tint = tint;
			for (GetComponent callback : m_TileCallbacks)
			{
				((Animated*)callback())->Tint(m_Tint);
			}
		}

		GTD_API void SetRelativePosition(const glm::vec3& position)
		{ 
			m_Position = position;
			for (GetComponent callback : m_TileCallbacks)
			{
				((Animated*)callback())->Move(m_Position);
			}
		}

		GTD_API void AddTile(const GetComponentCallback& ret, const GetComponentCallbackParams& params)
		{
			m_TileCallbacks.push_back(std::bind(ret, params));
		}

		GTD_API void AddTile(const Ref<TileE> tile)
		{
			m_TileEs.push_back(tile);
		}

	private:
		float m_Layer;
		Ref<SpriteSheet> m_SpriteSheet;
		std::vector<Ref<Animated>> m_Tiles; // Tiles are stored as objects as the TileMap (should be stored as a ref)
		std::vector<Ref<TileE>> m_TileEs; // Tiles are stored as objects as the TileMap (should be stored as a ref)
		std::vector<std::function<IComponent* ()>> m_TileCallbacks;
		glm::vec4 m_Tint;
		glm::vec3 m_Position;
		bool m_Activated;
	};
}

