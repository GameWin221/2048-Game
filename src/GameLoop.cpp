#include "GameLoop.hpp"

void GameLoop::Init()
{
	deltaTime = 0.0f;

	window = new Window(glm::uvec2(1024, 1024), "Window");

	int size = 8;

	grid = new Grid(size);

	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			grid->AddBlock(glm::vec2(x, y), 2);
		}
	}

	scoreDisplay = new Text("Score: ");
	scoreDisplay->position = glm::vec2(300, 950);

	fpsDisplay = new FPSDisplay(glm::vec2(800, 950), 1.0f);
}
void GameLoop::Update()
{
	window->PollEvents();

	fpsDisplay->UpdateDT();

	// If pressed W/Up Arrow
	if (Input::Clicked(Up))	
		grid->MoveBlocks(Up);

	// If pressed S/Down Arrow
	else if (Input::Clicked(Down)) 
		grid->MoveBlocks(Down);

	// If pressed A/Left Arrow
	if (Input::Clicked(Left))
		grid->MoveBlocks(Left);

	// If pressed D/Right Arrow
	else if (Input::Clicked(Right))
		grid->MoveBlocks(Right);

	// Check key states to use in the next frame
	Input::UpdateOldInputs();
}
void GameLoop::Render()
{
	window->Clear(glm::vec4(0.3f, 0.3f, 0.4f, 1.0f));

	grid->Render();

	for (auto& block : grid->blocks)
		block.Render();

	scoreDisplay->Render();

	fpsDisplay->RenderFPS();

	window->Display();
}
void GameLoop::Exit()
{
}