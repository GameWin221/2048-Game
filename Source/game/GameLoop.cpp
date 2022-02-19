#include "game/GameLoop.hpp"

void GameLoop::Start()
{
	window = new Window(glm::uvec2(900, 1024), "2048");

	const int size = 64;

	grid = new Grid(size);

	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			grid->AddBlock(glm::ivec2(x, y), 2);

	//grid->SpawnRandomBlock();

	scoreDisplay = new ScoreDisplay;
	fpsDisplay = new FPSDisplay;

	restartButton = new RestartButton(grid, scoreDisplay);
	undoButton = new UndoButton(grid, scoreDisplay);
}
void GameLoop::Update()
{
	window->PollEvents();

	fpsDisplay->UpdateDT();

	restartButton->CheckPress();
	undoButton->CheckPress();

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

	grid->Update(fpsDisplay->deltaTime, scoreDisplay);

	// Check key states to use in the next frame
	Input::UpdateOldInputs();
}
void GameLoop::Render()
{
	window->Clear(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	Sprite::InitInstancing();

	grid->Render();

	for (auto& block : grid->blocks)
		block->Render();

	restartButton->Render();
	undoButton->Render();

	Text::InitInstancing();

	for (auto& block : grid->blocks)
		block->RenderText();

	scoreDisplay->Render();
	fpsDisplay->Render();
		
	window->Display();
}
void GameLoop::Lose()
{
}