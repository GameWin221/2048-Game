#pragma once

#ifndef SCOREDISPLAY_HPP
#define SCOREDISPLAY_HPP

#include "Text.hpp"

class ScoreDisplay
{
private:
	Text* scoreText;

	int score;

public:
	void AddScore(int deltaScore);
	void SetScore(int targetScore);
	int GetScore();

	void Render();

	ScoreDisplay();
	~ScoreDisplay();
};

#endif