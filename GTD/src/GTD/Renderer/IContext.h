#pragma once
#include "../include/Core.h"


namespace GTD
{
	class GTD_API IContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}