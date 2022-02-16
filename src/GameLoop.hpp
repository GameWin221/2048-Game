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

class GameLoop
{
private:
	Window* window;
	Grid* grid;

	Text* scoreDisplay;

	Font* horror;

	FPSDisplay* fpsDisplay;

public:
	bool IsRunning() { return window->IsOpen(); };

	void Init();
	void Update();
	void Render();
	void Exit();
};