#pragma once

#include "Core.h"

namespace GTD
{
	class GTD_API App
	{
	public:
		App();
		virtual ~App();
		void Run();
	};

	// to be defined in client
	App* CreateApp();
}

