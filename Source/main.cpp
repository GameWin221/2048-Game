//TODO
// Postprocessing (Bloom, Motion blur)
// Change the default color of the New Game button
// Chosing the grid size (Kinda done)
// Linux support

#include "game/GameLoop.hpp"

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

using namespace GameLoop;

int main()
{
	std::cout << "Type in the grid's size (min: 2, max: 32): ";
	
	int size;
	std::cin >> size;
	size = std::min(std::max(size, 2), 32);

#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	Start(size);
	
	while (IsRunning())
	{
		Update();
		Render();
	}

#ifdef _WIN32
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif
}