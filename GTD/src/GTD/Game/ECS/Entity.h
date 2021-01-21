#pragma once
#include "../../include/Core.h"
#include "../../Util/Utils.h"
#include "IComponent.h"
#include "Callbacks.h"

namespace GTD
{
	class GTD_API Entity
	{
	public:
		virtual ~Entity() {};

		// Callbacks are created to get the component from a vector.
		// The pointer cannot be saved directly as vectors can resize and invalidating the pointer address
		virtual void AddComponent(const GetComponentCallback& ret, const GetComponentCallbackParams& params, COMPONENTS type) = 0;
		virtual void Init() = 0;
		virtual bool const IsActive() = 0;
		virtual void Activated(bool activated) = 0;
		virtual void Kill() = 0;
	};
}