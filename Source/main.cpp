//TODO
// (Glitch) theres a "flash" when the LoseSceen shows up
// Chosing the grid size (Kinda done, but I'd like a menu)
// Linux support

#include "game/GameLoop.hpp"
#include "menu/MenuLoop.hpp"

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
int main()
#endif
{
	int size;
	MenuLoop::Start(&size);
	
	while (MenuLoop::IsRunning())
	{
		MenuLoop::Update();
		MenuLoop::Render();
	}

//####################################

	GameLoop::Start(size);
	
	while (GameLoop::IsRunning())
	{
		GameLoop::Update();
		GameLoop::Render();
	}
}