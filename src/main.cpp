#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

#include "GameLoop.hpp"

int main()
{
	GameLoop game;

	game.Init();

	while (game.IsRunning())
	{
		game.Update();
		game.Render();
	}

	game.Exit();

	return 0;
}