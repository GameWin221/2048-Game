#pragma once

#include "Window.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Block.hpp"
#include "Grid.hpp"
#include "Input.hpp"
#include "Text.hpp"
#include "FPSDisplay.hpp"
#include "Font.hpp"
#include "ScoreDisplay.hpp"

class GameLoop
{
private:
	Window* window;
	Grid* grid;

	Font* horror;

	ScoreDisplay* scoreDisplay;
	FPSDisplay* fpsDisplay;

public:
	bool IsRunning() { return window->IsOpen(); };

	void Start();
	void Update();
	void Render();
	void Lose();
};