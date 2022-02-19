#include "game/GameLoop.hpp"

//TODO
// Naprawic Undo
// Naprawic Lose (przegrywanie)

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