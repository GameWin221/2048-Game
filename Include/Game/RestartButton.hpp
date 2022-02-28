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
	glm::vec3 glowHighlightedColor;

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

	virtual void OnHover();
	virtual void OnIdle();
	virtual void OnPress();
};

#endif