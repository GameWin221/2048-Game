#pragma once

#ifndef MENU_HPP
#define MENU_HPP

#include "gfx/Window.hpp"
#include "gfx/Shader.hpp"
#include "gfx/Texture.hpp"
#include "gfx/Sprite.hpp"

#include "gfx/Text/Text.hpp"
#include "gfx/Text/Font.hpp"

#include "game/Button/Button.hpp"
#include "menu/GridSizeButton.hpp"

namespace Menu
{
	bool IsRunning();

	void Start(int* sizeInt, Window* window);
	void Update();
	void Render();

	void CloseMenu();

	const int& GetChosenSize();
	void SetChosenSize(const int size);

	void Exit(GLFWwindow* window);
};
#endif