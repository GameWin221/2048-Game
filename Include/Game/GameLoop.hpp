#pragma once

#ifndef GAMELOOP_HPP
#define GAMELOOP_HPP

#include "Core/Gfx/Window.hpp"
#include "Core/Gfx/Shader.hpp"
#include "Core/Gfx/Texture.hpp"
#include "Core/Gfx/Sprite.hpp"

#include "Core/Text/Text.hpp"
#include "Core/Text/Font.hpp"

#include "Core/Direction.hpp"
#include "Core/Input.hpp"

#include "Game/Block.hpp"
#include "Game/Grid.hpp"
#include "Game/FPSDisplay.hpp"
#include "Game/ScoreDisplay.hpp"
#include "Game/LoseScreen.hpp"

#include "Core/Button.hpp"
#include "Game/RestartButton.hpp"

#include "Game/GameLoader.hpp"

namespace GameLoop
{
	bool IsRunning();

	void Start(const unsigned int& arg, Window* window);
	void Update();
	void Render();
	void Exit(GLFWwindow* window);
	void Lose();
};

#endif