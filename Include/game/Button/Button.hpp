#pragma once

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "gfx/Sprite.hpp"

class Button
{
protected:
	Button(); // For inheritance

	Sprite* sprite;

	bool wasPressed = false;

public:
	Button(Sprite* buttonSprite);
	~Button();

	virtual void OnPress();

	void CheckPress();
	void Render();
};

#endif