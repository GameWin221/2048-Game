#include "game/GameLoop.hpp"

// Only for debugging/testing purposes
const void FillGrid(Grid* grid, const int& size)
{
	for (int x = 0; x < size; x++)
		for (int y = 0; y < size; y++)
			grid->AddBlock(glm::ivec2(x, y), 2);
}

namespace GameLoop
{
	Window* gameWindow;
	Grid* grid;

	ScoreDisplay* scoreDisplay;
	FPSDisplay* fpsDisplay;

	RestartButton* restartButton;
	LoseScreen* loseScreen;

	void Start(const unsigned int& arg)
	{
		gameWindow = new Window(glm::uvec2(900, 1024), "2048");
		glfwSetWindowCloseCallback(gameWindow->glfwWindow, Exit);

		grid = new Grid(arg);

		scoreDisplay  = new ScoreDisplay(grid->gridSize);
		fpsDisplay	  = new FPSDisplay;
		loseScreen	  = new LoseScreen;
		restartButton = new RestartButton(grid, scoreDisplay);

		//FillGrid(grid, arg);

		if (GameLoader::SaveExists(grid))
		{
			GameLoader::Load(grid, scoreDisplay);
			grid->CheckLose();
		}
		else
			grid->SpawnRandomBlock();
	}
	void Update()
	{
		fpsDisplay->UpdateDT();

		gameWindow->PollEvents();

		restartButton->CheckPress();

		// If the player didn't lose yet
		if (!grid->lost)
		{
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

			if (grid->shouldLose)
				Lose();

			grid->Update(fpsDisplay->deltaTime, scoreDisplay);

			loseScreen->SetVisibility(false);
		}
		else
			loseScreen->SetVisibility(true);

		// Check key states to use in the next frame
		Input::UpdateOldInputs();
	}
	void Render()
	{
		gameWindow->Clear(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		Sprite::InitInstancing();

		grid->Render();

		for (auto& block : grid->blocks)
			block.RenderSprite();

		restartButton->Render();

		Text::InitInstancing();

		for (auto& block : grid->blocks)
			block.RenderText();

		scoreDisplay->Render();
		fpsDisplay->Render();


		loseScreen->Render();

		gameWindow->Display();
	}
	void Exit(GLFWwindow* window)
	{
		GameLoader::Save(grid, scoreDisplay);

		scoreDisplay->SaveBestScore(grid->gridSize);
		glfwSetWindowShouldClose(window, GL_TRUE);
		gameWindow->Close();
	}
	void Lose()
	{
		restartButton->SetGlow(true);

		scoreDisplay->SaveBestScore(grid->gridSize);

		grid->shouldLose = false;
		grid->lost = true;
	}

	bool IsRunning()
	{
		return gameWindow->IsOpen();
	}
}