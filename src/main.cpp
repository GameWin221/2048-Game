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