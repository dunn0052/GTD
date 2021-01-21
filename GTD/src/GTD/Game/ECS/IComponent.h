#pragma once
#include "../../include/Core.h"

/* How to add a new component:
* Add to COMPOONENTS enum
* Create the derived IComponent class
* Add component to GetComponentCallbackParams in Callbacks.h
* Add a component vector to EntityDirector.h
* Add to EntityDirector::SetComponentCallBack()
* 
* Attach to an entity:
* EntityDirector::Create() can use SetComponentCallback() to set a component retrieval callback
* Then functions from the component can be used from the entity
*/


namespace GTD
{
	enum COMPONENTS
	{
		DRAWABLE = 0,
		CONTROLLABLE = 1,
		ANIMATED = 2,
		SOLID = 3,
		MOVABLE = 4,
		MAX_COMPONENTS = 6
	};

	class GTD_API IComponent
	{
	public:
		virtual ~IComponent() {};
		virtual void Init() = 0;
		virtual void Update() = 0;
		virtual void Activation(bool activate) = 0;
		virtual COMPONENTS GetType() const = 0;
	};

}