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

// set debug: 1 on, 0 off
#define GTD_DEBUG_MODE 1
#define GTD_ENABLE_ASSERTS 1

// Bits
#define MAKE_BIT( BIT_NUM ) ( 1ull << BIT_NUM )
#define SET_BIT( FLAGS, BIT_NUM ) ( FLAGS |= MAKE_BIT( BIT_NUM) )
#define UNSET_BIT( FLAGS, BIT_NUM ) ( FLAGS &= ~MAKE_BIT( BIT_NUM ) )