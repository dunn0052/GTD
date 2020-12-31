#pragma once

//#include "../../PCH.h"

#include "Core.h"
#include "../Events/Events.h"
#include "../include/Timestep.h"

namespace GTD
{
	class GTD_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep dt) {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& const GetName() { return m_DebugName; }
		inline const uint16_t const GetID() { return m_ID;  }

	protected:
		uint16_t m_ID;
		std::string m_DebugName;
	};
}