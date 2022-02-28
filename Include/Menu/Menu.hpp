#pragma once

#ifndef MENU_HPP
#define MENU_HPP

#include "Core/Gfx/Window.hpp"
#include "Core/Gfx/Shader.hpp"
#include "Core/Gfx/Texture.hpp"
#include "Core/Gfx/Sprite.hpp"

#include "Core/Text/Text.hpp"
#include "Core/Text/Font.hpp"

#include "Core/Button.hpp"
#include "Menu/GridSizeButton.hpp"

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