#include "GameLoop.hpp"

int main()
{
	GameLoop game;
	
	game.Start();
	
	while (game.IsRunning())
	{
		game.Update();
		game.Render();
	}
	
	game.Lose();
	
	return 0;
}