#pragma once

#include "Direction.hpp"
#include "glfw3.h"

namespace Input
{
	extern bool Clicked(Direction directionKey);

	extern void UpdateOldInputs();
};