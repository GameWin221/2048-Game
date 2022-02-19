#pragma once

#include "game/Block.hpp"
#include "game/Direction.hpp"
#include "game/FPSDisplay.hpp"
#include "game/Grid.hpp"
#include "game/Input.hpp"
#include "game/ScoreDisplay.hpp"

#include "game/Button/Button.hpp"
#include "game/Button/RestartButton.hpp"
#include "game/Button/UndoButton.hpp"

#include "gfx/Text/Text.hpp"
#include "gfx/Text/Font.hpp"

#include "gfx/Shader.hpp"
#include "gfx/Sprite.hpp"
#include "gfx/Texture.hpp"
#include "gfx/Window.hpp"

class GameLoop
{
private:
	Window* window;
	Grid* grid;

	ScoreDisplay* scoreDisplay;
	FPSDisplay* fpsDisplay;

	RestartButton* restartButton;
	UndoButton* undoButton;

public:
	bool IsRunning() { return window->IsOpen(); };

	void Start();
	void Update();
	void Render();
	void Lose();
};