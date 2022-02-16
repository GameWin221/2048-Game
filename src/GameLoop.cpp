#include "GameLoop.hpp"

void GameLoop::Init()
{
	window = new Window(glm::uvec2(1024, 1224), "2048");

	int size = 4;

	grid = new Grid(size);

	horror = new Font("Fonts/horror.ttf", 128);

	scoreDisplay = new ScoreDisplay();
	fpsDisplay = new FPSDisplay();
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
		block.Render();

	Text::InitInstancing();

	for (auto& block : grid->blocks)
		block.RenderText();

	scoreDisplay->Render();
	fpsDisplay->Render();

	window->Display();
}
void GameLoop::Exit()
{
}