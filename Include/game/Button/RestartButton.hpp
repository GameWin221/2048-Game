#pragma once

#ifndef RESTARTBUTTON_HPP
#define RESTARTBUTTON_HPP

#include "game/Button/Button.hpp"

#include "game/Grid.hpp"
#include "game/ScoreDisplay.hpp"

class RestartButton : public Button
{
protected:
	RestartButton(); // For inheritance

	Grid* grid;
	ScoreDisplay* score;

public:
	RestartButton(Grid* mainGrid, ScoreDisplay* mainScoreDisplay);
	~RestartButton();

	virtual void OnPress();
};

#endif