#pragma once

#ifdef GTD_PLATFORM_WINDOWS

extern GTD::App* GTD::CreateApp();

int main(int argc, char** argv)
{
	printf(" <# GTD Engine #>\n");
	auto app = GTD::CreateApp();
	app->Run();
	delete app;
}
#else
	#error Implement other OS please
#endif