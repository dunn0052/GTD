#include "../PCH/PCH.h"
#include "RenderCommands.h"
#include "OpenGLRendererAPI.h"

namespace GTD
{
	// single pointer 1 byte "memory leak"
	IRendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}