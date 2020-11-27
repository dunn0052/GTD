#pragma once

#include <functional>

#include "../include/Core.h"

enum class EventType
{
	NONE,
	WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LIST_FOCUS, WINDOWMOVED,
	APP_TICK, APP_UPDATE, APP_RENDER,
	KEY_PRESSED, KEY_RELEASED, KEY_TYPED,
	MOUSE_BUTTON_PRESSED, MOUSE_BUTTON_RELEASED, MOUSE_MOVED, MOUSE_SCROLLED
	// implement controller events too
};


// Filter events
enum EventCategory
{
	None = 0,
	CATEGORY_APP = MAKE_BIT(0),
	CATEGORY_INP = MAKE_BIT(1),
	CAT_KB = MAKE_BIT(2),
	CAT_MOUSE_MOVE = MAKE_BIT(3),
	CAT_MOUSE_BUT = MAKE_BIT(4)
};