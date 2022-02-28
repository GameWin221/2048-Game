#pragma once

#ifndef GRIDSIZEBUTTON_HPP
#define GRIDSIZEBUTTON_HPP

#include "Core/Button.hpp"
#include "Core/Text/Text.hpp"
#include "Menu/Menu.hpp"

#include <glm.hpp>

class GridSizeButton : public Button
{
private:
	int gridSize;

public:
	GridSizeButton(glm::vec2 buttonPosition, const int gSize);

	Text* gridSizeText;

	void RenderText();

	virtual void OnHover();
	virtual void OnIdle();
	virtual void OnPress();
};

#endif