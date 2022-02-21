#include "game/GameLoop.hpp"

//TODO
// (Glitch) Blocks are slightly flickering/teleporting after moving
// Make Lose() better
// Save the game after closing the window

int main()
{
	GameLoop game;
	
	game.Start();
	
	while (game.IsRunning())
	{
		game.Update();
		game.Render();
	}
}