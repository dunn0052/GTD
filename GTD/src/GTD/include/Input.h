#pragma once

#include "../glm/glm.hpp"

#include "../Util/KeyCodes.h"
#include "../Util/MouseCodes.h"

namespace GTD
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
