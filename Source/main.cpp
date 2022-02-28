// TODO
// Linux support (Makefile)

#include "Game/GameLoop.hpp"
#include "Menu/Menu.hpp"

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
	Window* mainWindow = new Window(glm::uvec2(900, 1024), "2048");

	int size = 0;

// MENU

	Menu::Start(&size, mainWindow);
	
	while (Menu::IsRunning() && Menu::GetChosenSize() == 0)
	{
		Menu::Update();
		Menu::Render();
	}

	Menu::CloseMenu();

// GAME
	
	GameLoop::Start(size, mainWindow);

	while (GameLoop::IsRunning())
	{
		GameLoop::Update();
		GameLoop::Render();
	}
}