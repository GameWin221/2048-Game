#pragma once

#ifndef INPUT_HPP
#define INPUT_HPP

#include "Core/Direction.hpp"
#include "glfw3.h"

namespace Input
{
	extern bool Clicked(Direction directionKey);

	extern void UpdateOldInputs();
};

#endif