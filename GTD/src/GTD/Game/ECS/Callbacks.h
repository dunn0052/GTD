#pragma once
#include "Animated.h"
#include "Controllable.h"
#include "Drawable.h"
#include "Solid.h"
#include "Movable.h"
#include "IComponent.h"

namespace GTD
{
	// Communicates between EntityDirector vectors and entities wishing to get an assigned element
	struct GetComponentCallbackParams
	{
		union
		{
			std::vector<Animated>* Animated;
			std::vector<Controllable>* Controllable;
			std::vector<Drawable>* Drawable;
			std::vector<Solid>* Solid;
			std::vector<Movable>* Movable;
		};
		size_t index;
	};

	typedef IComponent* (*GetComponentCallback)(const GetComponentCallbackParams&);
	using GetComponent = std::function<IComponent* ()>;
}
