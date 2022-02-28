#pragma once

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Core/Gfx/Sprite.hpp"

class Button
{
protected:
	Button(); // For inheritance

	Sprite* sprite;

	glm::vec3 defaultColor;
	glm::vec3 highlightedColor;

	bool mouseWasPressed = false;

public:
	Button(Sprite* buttonSprite);

	virtual void OnPress();
	virtual void Render();

	void CheckPress();
};

#endif