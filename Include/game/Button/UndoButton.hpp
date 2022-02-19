#pragma once

#ifndef UNDOBUTTON_HPP
#define UNDOBUTTON_HPP

#include "game/Button/RestartButton.hpp"

class UndoButton : public RestartButton
{
public:
	UndoButton(Grid* mainGrid, ScoreDisplay* mainScoreDisplay);
	~UndoButton();

	virtual void OnPress();
};
#endif