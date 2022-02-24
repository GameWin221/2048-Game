#pragma once

#ifndef LOSESCREEN_HPP
#define LOSESCREEN_HPP

#include "gfx/Sprite.hpp"
#include "gfx/Text/Text.hpp"

class LoseScreen
{
private:
	bool isVisible;

	Text* loseText;
	Text* restartText;

	Sprite* sprite;
	Sprite* textBG;

public:
	LoseScreen();

	void SetVisibility(bool visibility);
	void Render();
};

#endif