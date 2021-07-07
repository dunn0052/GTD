#include "../../PCH/PCH.h"
#include "EntityDirector.h"

namespace GTD
{
	EntityDirector::EntityDirector(const Ref<Timestep>& dt) :
		m_DT(dt), m_Drawables(), m_Animated(), m_Controllables(), m_Solid()
	{
		m_Components.resize(COMPONENTS::MAX_COMPONENTS);
	}

	EntityDirector::~EntityDirector()
	{
	}

	void EntityDirector::Update()
	{

		/*
		* Get Controls
		* Move Entities
		* Check for collisions and adjust
		* Draw images in their final locations
		*/

		for (auto& componentType : m_Components)
		{
			for (auto& component : componentType)
			{
				component->Update();
			}
		}

		for (Controllable& component : m_Controllables)
		{
			component.Update();
		}

		for (Movable& component : m_Movables)
		{
			component.Update();
		}

		for (Solid& component : m_Solid)
		{
			component.Update();
		}

		CalculateCollisions();

		for (Drawable& component : m_Drawables)
		{
			component.Update();
		}

		for (Animated& component : m_Animated)
		{
			component.Update();
		}
	}

	// Adds a callback to the last 
	void EntityDirector::SetComponentCallBack(const Ref<Entity>& entity, COMPONENTS type)
	{

		GetComponentCallbackParams params = {};
		GetComponentCallback callback;

		switch (type)
		{
			case COMPONENTS::ANIMATED:
			{
				params.Animated = &m_Animated;
				params.index = m_Animated.size() - 1;

				callback = [](const GetComponentCallbackParams& props)
				{
					return (IComponent*)&(props.Animated->data()[props.index]);
				};

				break;
			}
			case COMPONENTS::CONTROLLABLE:
			{
				params.Controllable = &m_Controllables;
				params.index = m_Controllables.size() - 1;

				callback = [](const GetComponentCallbackParams& props)
				{
					return (IComponent*)&(props.Controllable->data()[props.index]);
				};
				break;
			}
			case COMPONENTS::DRAWABLE:
			{
				params.Drawable = &m_Drawables;
				params.index = m_Drawables.size() - 1;

				callback = [](const GetComponentCallbackParams& props)
				{
					return (IComponent*)&(props.Drawable->data()[props.index]);
				};
				break;
			}
			case COMPONENTS::SOLID:
			{
				params.Solid = &m_Solid;
				params.index = 0;

				callback = [](const GetComponentCallbackParams& props)
				{
					return (IComponent*)&(props.Solid->data()[props.index]);
				};
				break;
			}
			case COMPONENTS::MOVABLE:
			{
				params.Movable = &m_Movables;
				params.index = 0;

				callback = [](const GetComponentCallbackParams& props)
				{
					return (IComponent*)&(props.Movable->data()[props.index]);
				};
				break;
			}
			case COMPONENTS::MAX_COMPONENTS:
			default:
			{
				GTD_ASSERT(false, "Illegal component type");
			}
		}

		entity->AddComponent(callback, params, type);
	}

	void EntityDirector::SetTileCallback(const Ref<TileMapE> tileMap)
	{
		GetComponentCallbackParams params = {};
		GetComponentCallback callback;

		params.Animated = &m_Animated;
		params.index = m_Animated.size() - 1;

		callback = [](const GetComponentCallbackParams& props)
		{
			return (IComponent*)&(props.Animated->data()[props.index]);
		};

		tileMap->AddTile(callback, params);
	}

	void EntityDirector::SetSolidsStartCallback(const Ref<Entity> entity)
	{
		GetComponentCallbackParams params = {};
		GetComponentCallback callback;

		params.Solid = &m_Solid;
		params.index = 0; // Beginning of the solids

		callback = [](const GetComponentCallbackParams& props)
		{
			return (IComponent*)&(props.Solid->data()[props.index]);
		};

		entity->AddComponent(callback, params, COMPONENTS::SOLID);
	}

	void EntityDirector::CalculateCollisions()
	{
		glm::vec2 contactPoint = glm::vec2(0.0f);
		glm::vec2 contactNormal = glm::vec2(0.0f);
		float time = 0.0f;
		float timestep = m_DT->GetSecond();

		for (auto& movable : m_Movables)
		{
			if (!movable.IsCollidable() || movable.IsStopped())
			{
				continue;
			}

			glm::vec2 reverse = glm::vec2(0.0f);
			bool collided = false;

			for (auto& solid : m_Solid)
			{
				if (MovableSolidCollideSolid(movable, solid, contactPoint, contactNormal, time, timestep))
				{
					// Get the line segment between the initial starting point and the collision point
					reverse += glm::vec2{ contactNormal * glm::vec2{std::abs(movable.GetDirection().x) , std::abs(movable.GetDirection().y)} * (1 - time) };
					collided = true;
				}
			}
			if (collided)
			{
				movable.SetPosition(movable.GetPosition() + ( movable.Get2DDirection() + reverse )* m_DT->GetSecond()); // reverse the original movement
			}
		}
	}

	Ref<SpriteE> EntityDirector::Create(const SpriteParamsE& spriteProps)
	{
		Ref<SpriteE> sprite = CreateRef<SpriteE>();

		m_Animated.push_back(Animated(spriteProps.SpriteSheet, spriteProps.Quad, spriteProps.StartingFrame, spriteProps.DT, 0.1f));
		SetComponentCallBack(sprite, COMPONENTS::ANIMATED);
		
		if (spriteProps.IsSolid)
		{
			m_Solid.push_back(Solid(spriteProps.Quad, spriteProps.DT, m_Solid.size()));
			SetComponentCallBack(sprite, COMPONENTS::SOLID);
		}

		return sprite;
	}

	Ref<PC> EntityDirector::Create(PCProps& pcProps)
	{
		Ref<PC> pc = CreateRef<PC>(pcProps);

		m_Animated.push_back(Animated(pcProps.SpriteSheet, pcProps.Quad, pcProps.StartingFrame, pcProps.DT, 0.1f));
		SetComponentCallBack(pc, COMPONENTS::ANIMATED);

		m_Controllables.push_back(Controllable(pcProps.Controller));
		SetComponentCallBack(pc, COMPONENTS::CONTROLLABLE);

		m_Movables.push_back(Movable(pcProps.Quad, pcProps.DT, m_Movables.size(), pcProps.Speed, pcProps.StartingDirection, pcProps.IsSolid));
		SetComponentCallBack(pc, COMPONENTS::MOVABLE);

		return pc;
	}

	Ref<TileMapE> EntityDirector::Create(const TileMapProps& spriteSheetProps)
	{
		Ref<TileMapE> tileMap = CreateRef<TileMapE>();

		std::vector<std::vector<int32_t>> table = CSVLoader::GetInstance()->LoadIntegerCSV(spriteSheetProps.TileMapCSVPath);

		for (int row = 0; row < table.size(); row++)
		{
			for (int column = 0; column < table[row].size(); column++)
			{
				int32_t tileIndex = table[row][column];
				if (tileIndex > -1 && tileIndex <= spriteSheetProps.SpriteSheet->GetNumTiles())
				{
					m_Animated.push_back
					(
						Animated
						(
							spriteSheetProps.SpriteSheet,

							CreateRef<Quad>(
								Rectangle({ spriteSheetProps.Position.x + column, spriteSheetProps.Position.y + table.size() - row, spriteSheetProps.Position.z }, { 1.0f, 1.0 }),
								spriteSheetProps.Tint
								),

							tileIndex,
							spriteSheetProps.DT,
							0.01f
						)
					);

					SetTileCallback(tileMap);
				}
			}
		}

		return tileMap;
	}

	
	Ref<TileLayer> EntityDirector::Create(const TileLayerProps& tileLayerProps)
	{
		Ref<TileLayer> tileLayer = CreateRef<TileLayer>(tileLayerProps);

		std::vector<std::vector<int32_t>> table = CSVLoader::GetInstance()->LoadIntegerCSV(tileLayerProps.TileMapCSVPath);

		for (int row = 0; row < table.size(); row++)
		{
			for (int column = 0; column < table[row].size(); column++)
			{
				int32_t tileIndex = table[row][column];
				if (tileIndex > -1 && tileIndex <= tileLayerProps.SpriteSheet->GetNumTiles())
				{
					TileParamsE params;
					params.Quad = CreateRef<Quad>(
						Rectangle({ tileLayerProps.Quad->Left() + column, tileLayerProps.Quad->Bottom() + table.size() - row, tileLayerProps.Quad->m_Rect.m_Position.z }, { 1.0f, 1.0 }),
						tileLayerProps.Quad->m_Color
						),

					m_Animated.push_back
					(
						Animated
						(
							tileLayerProps.SpriteSheet,
							params.Quad,
							tileIndex,
							tileLayerProps.DT,
							0.1f
						)
					);

					Ref<TileE> tile = CreateRef<TileE>(params);
					SetComponentCallBack(tile, COMPONENTS::ANIMATED);

					// Make walls
					if (tileLayerProps.Solid)
					{
						m_Solid.push_back(Solid(params.Quad, tileLayerProps.DT, m_Solid.size()));
						SetComponentCallBack(tile, COMPONENTS::SOLID);
					}

					tileLayer->AddTile(tile);
				}
			}
		}

		return tileLayer;
	}
	
}