#pragma once

#ifndef SCOREDISPLAY_HPP
#define SCOREDISPLAY_HPP

#include "gfx/Text/Text.hpp"
#include <fstream>

class ScoreDisplay
{
private:
	Text* scoreText;
	Text* bestScoreText;

	int score;
	int bestScore;

public:
	void AddScore(int deltaScore);
	void SetScore(int targetScore);
	const int& GetScore() const;

	void SetBestScore(int targetBestScore);
	const int& GetBestScore() const;

	void SaveBestScore();

	void Render();

	ScoreDisplay();
	~ScoreDisplay();
};

#endif