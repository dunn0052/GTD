#include <GTD.h>

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