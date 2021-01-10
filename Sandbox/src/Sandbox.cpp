#include <GTD.h>
#include "GTD/Renderer/OpenGLShader.h"
#include "../inlucde/Layer2D.h"

#include "GTD/include/EntryPoint.h"

#include "../../Vendor/glm/gtc/matrix_transform.hpp"


class Sandbox : public GTD::App
{
public:
	Sandbox()
	{
		PushLayer(new Layer2D());
	}

	~Sandbox()
	{

	}
};

GTD::App* GTD::CreateApp()
{
	return new Sandbox();
}
