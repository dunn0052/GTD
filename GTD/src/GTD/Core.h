#pragma once

#ifdef GTD_PLATFORM_WINDOWS
	#ifdef GTD_BUILD_DLL
		#define GTD_API __declspec(dllexport)
	#else
		#define GTD_API __declspec(dllimport)
	#endif
#else
	#error Implement other OS please
#endif