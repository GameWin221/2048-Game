#pragma once

#ifndef MENULOOP_HPP
#define MENULOOP_HPP

#include "gfx/Window.hpp"
#include "gfx/Shader.hpp"
#include "gfx/Texture.hpp"
#include "gfx/Sprite.hpp"

#include "gfx/Text/Text.hpp"
#include "gfx/Text/Font.hpp"

#include "game/Button/Button.hpp"
#include "menu/GridSizeButton.hpp"

namespace MenuLoop
{
	bool IsRunning();

	void Start(int* sizeInt);
	void Update();
	void Render();

	void CloseMenu();

	void Exit(GLFWwindow* window);
};
#endif