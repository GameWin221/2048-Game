//TODO
// Postprocessing (Bloom, Motion blur)
// Chosing the grid size (Kinda done)
// Linux support
// Smooth block movement (some function for interpolation)
// (Glitch) blocks look like they wouldn't stop immidiately but they bounce

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