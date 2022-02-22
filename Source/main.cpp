#include "game/GameLoop.hpp"

//TODO
// (Glitch) Blocks are slightly flickering/teleporting after moving
// Make the game look good (Change color pallette)
// Maybe motion blur?

using namespace GameLoop;

int main()
{
	Start();
	
	while (IsRunning())
	{
		Update();
		Render();
	}
}