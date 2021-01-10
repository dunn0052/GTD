#pragma once

//#include "../../PCH.h"

#include "Core.h"
#include "../Util/Utils.h"
#include "../Events/Events.h"
#include "../include/Timestep.h"


namespace GTD
{
	class Layer
	{
	public:
		GTD_API Layer(const std::string& name = "Layer");
		GTD_API virtual ~Layer();

		GTD_API virtual void OnAttach() {}
		GTD_API virtual void OnDetach() {}
		GTD_API virtual void OnUpdate(const Ref<Timestep>& dt) {}
		GTD_API virtual void OnEvent(Event& e) {}

		GTD_API inline const std::string& GetName() { return m_DebugName; }
		GTD_API inline const uint16_t GetID() { return m_ID;  }
		GTD_API inline void SetTimestep(const Ref<Timestep>& dt) { m_DT = dt; }

	protected:
		uint16_t m_ID;
		std::string m_DebugName;
		Ref<Timestep> m_DT;
	};
}