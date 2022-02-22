#pragma once

#include "gfx/Window.hpp"
#include "gfx/Shader.hpp"
#include "gfx/Texture.hpp"
#include "gfx/Sprite.hpp"

#include "gfx/Text/Text.hpp"
#include "gfx/Text/Font.hpp"

#include "game/Direction.hpp"
#include "game/Input.hpp"
#include "game/Block.hpp"
#include "game/Grid.hpp"

#include "game/FPSDisplay.hpp"
#include "game/ScoreDisplay.hpp"
#include "game/LoseScreen.hpp"

#include "game/Button/Button.hpp"
#include "game/Button/RestartButton.hpp"

#include "game/GameLoader.hpp"

namespace GameLoop
{
	bool IsRunning();

	void Start();
	void Update();
	void Render();
	void Exit(GLFWwindow* window);
	void Lose();
};