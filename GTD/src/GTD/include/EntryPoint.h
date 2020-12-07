#pragma once

#include "Logger.h"

#ifdef GTD_PLATFORM_WINDOWS

extern GTD::App* GTD::CreateApp();

int main(int argc, char** argv)
{
	LOG_INFO("~-** Starting GTD Engine **-~");
	auto app = GTD::CreateApp();
	app->Run();
	delete app;
}
#else
	#error Implement other OS please
#endif