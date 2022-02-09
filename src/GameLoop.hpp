#pragma once

#include "Window.hpp"
#include "Sprite.hpp"
#include "Texture.hpp"
#include "Block.hpp"
#include "Grid.hpp"
#include "Input.hpp"
#include "Text.hpp"
#include "FPSDisplay.hpp"

class GameLoop
{
private:
	Window* window;
	Grid* grid;

	Text* scoreDisplay;

	FPSDisplay* fpsDisplay;

public:
	bool IsRunning() { return window->IsOpen(); };

	void Init();
	void Update();
	void Render();
	void Exit();
};