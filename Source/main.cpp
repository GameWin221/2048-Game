//TODO
// Make the game look good (Change color pallette, motion blur?)
// Chosing the grid size (Kinda done)
// (Glitch) Loading the game after lose causes it to freeze

#include "game/GameLoop.hpp"

#define NOMINMAX
#include <windows.h>

using namespace GameLoop;

int main()
{
	std::cout << "Type in the grid's size (min: 2, max: 32): ";
	
	int size;
	std::cin >> size;
	size = std::min(std::max(size, 2), 32);

	ShowWindow(GetConsoleWindow(), SW_HIDE);
	Start(size);
	
	while (IsRunning())
	{
		Update();
		Render();
	}
}