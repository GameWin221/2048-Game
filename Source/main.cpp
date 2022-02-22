#include "game/GameLoop.hpp"

//TODO
// (Glitch) Blocks are slightly flickering/teleporting after moving
// Make the game look good (Change color pallette, motion blur?)
// Chosing the grid size
// Increase the best score everytime score is added (if it's greater than the previous best score of course)

using namespace GameLoop;

int main()
{
	const int size = 4;

	Start(size);
	
	while (IsRunning())
	{
		Update();
		Render();
	}
}