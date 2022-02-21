#pragma once

#ifndef RESTARTBUTTON_HPP
#define RESTARTBUTTON_HPP

#include "game/Button/Button.hpp"

#include "game/Grid.hpp"
#include "game/ScoreDisplay.hpp"

class RestartButton : public Button
{
private:
	glm::vec3 defaultColor;
	glm::vec3 glowColor;

protected:
	Grid* grid;
	ScoreDisplay* score;

public:
	RestartButton(Grid* mainGrid, ScoreDisplay* mainScoreDisplay);
	~RestartButton();

	void SetGlow(bool glow);

	virtual void OnPress();
};

#endif