#include "../PCH/PCH.h"
#include "IRendererAPI.h"

namespace GTD
{
	IRendererAPI::API IRendererAPI::s_API = IRendererAPI::API::OPENGL; // use ifdef on renderer api eventually
}