#pragma once

#ifndef RESTARTBUTTON_HPP
#define RESTARTBUTTON_HPP

#include "Core/Button.hpp"

#include "Game/Grid.hpp"
#include "Game/ScoreDisplay.hpp"

class RestartButton : public Button
{
private:
	glm::vec3 glowColor;

	Sprite* blur;

protected:
	Grid* grid;
	ScoreDisplay* score;

	Text* text;

public:
	RestartButton(Grid* mainGrid, ScoreDisplay* mainScoreDisplay);
	~RestartButton();

	void Render();
	void RenderText();

	void SetGlow(bool glow);

	virtual void OnPress();
};

#endif