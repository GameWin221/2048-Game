#include "game/ScoreDisplay.hpp"

ScoreDisplay::ScoreDisplay(const int& gridSize)
{
	this->score = 0;
	this->bestScore = 0;

	// Loading the best score
	std::ifstream file("Saves/best" + std::to_string(gridSize) + ".save");
	std::string bestScoreString = "";

	if (!file.is_open())
	{
		std::ofstream newFile("Saves/best" + std::to_string(gridSize) + ".save");
		newFile << "0";
		newFile.close();

		file.open("Saves/best" + std::to_string(gridSize) + ".save");
	}

	std::getline(file, bestScoreString);

	if(bestScoreString.length() > 0 && std::isdigit(bestScoreString[0]))
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

void ScoreDisplay::AddScore(int deltaScore)
{
	int newTarget = this->score + deltaScore;
	this->SetScore(newTarget);
}
void ScoreDisplay::SetScore(int targetScore)
{
	if (this->bestScore < targetScore)
		this->SetBestScore(targetScore);

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

void ScoreDisplay::SaveBestScore(const int& gridSize)
{
	// Loading the best score
	std::fstream file("Saves/best" +std::to_string(gridSize) + ".save", std::ofstream::in | std::ofstream::out);
	std::string bestScoreString = "";

	std::getline(file, bestScoreString);
	const int bestScoreInt = std::stoi(bestScoreString);

	// If the previous high score was lower then the current score
	if(bestScoreInt < this->score)
	{
		// Clearing the file
		file.close();
		file.open("Saves/best" + std::to_string(gridSize) + ".save", std::ofstream::in | std::ofstream::out);

		file << std::to_string(this->score);
		this->SetBestScore(this->score);
	}

	file.close();
}