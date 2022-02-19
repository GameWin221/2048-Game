#include "game/ScoreDisplay.hpp"

ScoreDisplay::ScoreDisplay()
{
	this->score = 0;
	this->bestScore = 0;

	// Loading the best score
	std::ifstream file("BestScore.txt");
	std::string bestScoreString = "";

	if (file.bad())
	{
		std::cout << "Could not find BestScore.txt, creating it now...\n";

		std::ofstream newFile("BestScore.txt");
		newFile << "0";
		newFile.close();
	}

	std::getline(file, bestScoreString);
	this->bestScore = std::stoi(bestScoreString);

	file.close();

	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);

	glm::vec2 position(wX, wY);
	position.x *= 0.02f;
	position.y *= 0.9f;

	this->scoreText = new Text(Font::DefaultFont(), "Score: 0");
	this->scoreText->position = position;
	this->scoreText->color = glm::vec3(0.0f, 0.0, 0.0f);
	this->scoreText->scale = 0.4f;

	position = glm::vec2(wX, wY);
	position.x *= 0.02f;
	position.y *= 0.96f;

	this->bestScoreText = new Text(Font::DefaultFont(), "Best Score: " + std::to_string(this->bestScore));
	this->bestScoreText->position = position;
	this->bestScoreText->color = glm::vec3(0.0f, 0.0, 0.0f);
	this->bestScoreText->scale = 0.4f;
}

ScoreDisplay::~ScoreDisplay(){}

void ScoreDisplay::Render()
{
	this->scoreText->Render();
	this->bestScoreText->Render();
}

void ScoreDisplay::UndoScore()
{
	this->score = lastScore;
	this->SetScore(this->lastScore);
}

void ScoreDisplay::AddScore(int deltaScore)
{
	int newTarget = this->score + deltaScore;
	this->SetScore(newTarget);
}
void ScoreDisplay::SetScore(int targetScore)
{
	this->lastScore = this->score;

	this->score = targetScore;
	this->scoreText->SetString("Score: " + std::to_string(this->score));
}
const int& ScoreDisplay::GetScore() const
{
	return this->score;
}

void ScoreDisplay::SetBestScore(int targetBestScore)
{
	this->bestScore = targetBestScore;
	this->bestScoreText->SetString("Best Score: " + std::to_string(this->bestScore));
}

const int& ScoreDisplay::GetBestScore() const
{
	return this->bestScore;
}

void ScoreDisplay::SaveBestScore()
{
	// Loading the best score
	std::fstream file("BestScore.txt");
	std::string bestScoreString = "";

	std::getline(file, bestScoreString);
	const int bestScoreInt = std::stoi(bestScoreString);

	// If the previous high score was lower then the current score
	if(bestScoreInt < this->score)
	{
		// Clearing the file
		std::ofstream clr("test.txt", std::ofstream::out | std::ofstream::trunc);
		clr.close();

		file << std::to_string(this->score);
		this->SetBestScore(this->score);
	}

	file.close();
}
