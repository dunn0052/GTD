#pragma once
#include "IComponent.h"
#include "Drawable.h"
#include "Controllable.h"
#include "Solid.h"
#include "Movable.h"
#include "../../include/Core.h"
#include "../SpriteE.h"
#include "../TileMapE.h"
#include "../PC.h"
#include "Callbacks.h"
#include "../TileLayer.h"
#include "../../include/Timestep.h"
#include "../../Physics/2DCollision.h"

namespace GTD
{
	class EntityDirector
	{
	public:
		GTD_API EntityDirector(const Ref<Timestep>& dt);
		GTD_API ~EntityDirector();

		GTD_API void Update();

		GTD_API Ref<SpriteE> Create(const SpriteParamsE& spriteProps);
		GTD_API Ref<TileMapE> Create(const TileMapProps& spriteSheetProps);
		GTD_API Ref<TileLayer> Create(const TileLayerProps& tileLayerProps);
		GTD_API Ref<PC> Create(PCProps& pcProps); // non-const since we want to have the ability to add a reference to m_Solid

	private:
		void SetComponentCallBack(const Ref<Entity>& entity, COMPONENTS type);
		void SetTileCallback(const Ref<TileMapE> tileMap);
		void SetSolidsStartCallback(const Ref<Entity> ent);
		void CalculateCollisions();

	private:
		Ref<Timestep> m_DT;

		std::vector<Drawable> m_Drawables;
		std::vector<Animated> m_Animated;
		std::vector<Controllable> m_Controllables;
		std::vector<Solid> m_Solid;
		std::vector<Movable> m_Movables;
	};
}