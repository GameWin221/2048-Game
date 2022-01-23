#include "GameLoop.hpp"

void GameLoop::Init()
{
	window = new Window(glm::uvec2(1024, 1024), "Window");
	grid = new Grid(11);

	grid->AddBlock(glm::vec2(4, 4), 2);
	grid->AddBlock(glm::vec2(1, 4), 2);
	grid->AddBlock(glm::vec2(10, 5), 2);
	grid->AddBlock(glm::vec2(6, 8), 2);
	grid->AddBlock(glm::vec2(0, 9), 2);
	grid->AddBlock(glm::vec2(5, 2), 2);
	grid->AddBlock(glm::vec2(7, 7), 2);

	text = new Text("Hello World");
}
void GameLoop::Update()
{
	window->PollEvents();

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

	//grid->Render();

	//for (auto& block : grid->blocks)
		//block.Render();
  
	text->Render("Hello World!", 25.0f, 25.0f);

	window->Display();
}
void GameLoop::Exit()
{
}