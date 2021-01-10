# GTD
Generic Top Down Game Engine

This engine is a dynamically linked library (DLL) that can be used to create your own Generic Top Down applications.

To create your own application using GTD create a new C++ file that will be the main entry point for your game.
To create your GTD App, simply create your App class that inherits from the GTD::App class. After this class definition,
you must create a GTD::CreateApp() function that returns an instance of your App class. An example:

class Sandbox : public GTD::App
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

GTD::App* GTD::CreateApp()
{
	return new Sandbox();
}
