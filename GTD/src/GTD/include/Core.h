#pragma once

#define GTD_DYNAMIC_LINK 1

#ifdef GTD_PLATFORM_WINDOWS
	#if GTD_DYNAMIC_LINK
//  need to add GTD_API to all class interfaces
		#ifdef GTD_BUILD_DLL
			#define GTD_API __declspec(dllexport)
		#else
			#define GTD_API __declspec(dllimport)
		#endif
	#else
		#define GTD_API
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

// Events
#define BIND_EVENT_FTN( FUNCTION ) std::bind(&FUNCTION, this, std::placeholders::_1)