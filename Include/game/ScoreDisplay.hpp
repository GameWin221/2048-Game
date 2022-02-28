#pragma once

#ifndef SCOREDISPLAY_HPP
#define SCOREDISPLAY_HPP

#include "Core/Text/Text.hpp"
#include "Core/Gfx/Sprite.hpp"
#include <fstream>

class ScoreDisplay
{
private:
	Text* scoreText;
	Text* bestScoreText;

	Text* scoreValueText;
	Text* bestScoreValueText;

	Sprite* scoreBG;
	Sprite* bestScoreBG;

	int score;
	int bestScore;

public:
	void AddScore(int deltaScore);
	void SetScore(int targetScore);
	const int& GetScore() const;

	void SetBestScore(int targetBestScore);
	const int& GetBestScore() const;

	void SaveBestScore(const int& gridSize);

	void RenderBG();
	void RenderText();

	ScoreDisplay(const int& gridSize);
	~ScoreDisplay();
};

#endif