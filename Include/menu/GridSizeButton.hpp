#pragma once

#ifndef GRIDSIZEBUTTON_HPP
#define GRIDSIZEBUTTON_HPP

#include "game/Button/Button.hpp"
#include "gfx/Text/Text.hpp"
#include "menu/Menu.hpp"

#include <glm.hpp>

class GridSizeButton : public Button
{
private:
	int gridSize;

public:
	GridSizeButton(glm::vec2 buttonPosition, const int gSize);

	Text* gridSizeText;

	void RenderText();

	virtual void OnPress();
};

#endif