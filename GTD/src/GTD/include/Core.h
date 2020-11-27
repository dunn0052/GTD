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

// Bits
#define MAKE_BIT( BIT_NUM ) ( 1 << BIT_NUM )
#define SET_BIT( FLAGS, BIT_NUM ) ( FLAGS |= MAKE_BIT( BIT_NUM) )