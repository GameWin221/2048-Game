#include "game/ScoreDisplay.hpp"

Texture* bgTexture;

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

	if (!bgTexture)
		bgTexture = new Texture("Resources/Textures/TileRound.png");

	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);

	// ### SCORE BG ###
	glm::vec2 position(wX, wY);
	position.x *= 0.2f;
	position.y *= 0.938f;

	this->scoreBG = new Sprite(bgTexture);
	this->scoreBG->position = position;
	this->scoreBG->color = glm::vec3(0.4);

	// ### SCORE TEXT ###
	this->scoreText = new Text(Font::DefaultFont(), "Score:");
	this->scoreText->position = this->scoreBG->position + glm::vec2(0, 35);
	this->scoreText->color = glm::vec3(0.2f);
	this->scoreText->scale = 0.3f;
	this->scoreText->centered = true;

	// ### SCORE VALUE ###
	this->scoreValueText = new Text(Font::DefaultFont(), std::to_string(this->score));
	this->scoreValueText->position = this->scoreBG->position - glm::vec2(0, 20);
	this->scoreValueText->color = glm::vec3(0.2f);
	this->scoreValueText->scale = 0.5f;
	this->scoreValueText->centered = true;


	// ### BEST SCORE BG ###
	this->bestScoreBG = new Sprite(bgTexture);
	this->bestScoreBG->color = this->scoreBG->color;

	// ### BEST SCORE TEXT ###
	this->bestScoreText = new Text(Font::DefaultFont(), "Best:");
	this->bestScoreText->color = glm::vec3(0.2f);
	this->bestScoreText->scale = 0.3f;
	this->bestScoreText->centered = true;

	// ### BEST SCORE VALUE ###
	this->bestScoreValueText = new Text(Font::DefaultFont(), std::to_string(this->bestScore));
	this->bestScoreValueText->color = glm::vec3(0.2);
	this->bestScoreValueText->scale = 0.5f;
	this->bestScoreValueText->centered = true;
}
ScoreDisplay::~ScoreDisplay(){}

void ScoreDisplay::RescaleBGs()
{
	this->scoreBG->size		= glm::vec2(std::max(this->scoreValueText->GetBounds().x	 * 0.65f, this->scoreText->GetBounds().x	 * 0.65f), 60);
	this->bestScoreBG->size = glm::vec2(std::max(this->bestScoreValueText->GetBounds().x * 0.65f, this->bestScoreText->GetBounds().x * 0.65f), 60);

	this->bestScoreBG->position		   = this->scoreBG->position     + glm::vec2(this->scoreBG->size.x + this->bestScoreBG->size.x + 15, 0);
	this->bestScoreText->position	   = this->bestScoreBG->position + glm::vec2(0, 35);
	this->bestScoreValueText->position = this->bestScoreBG->position - glm::vec2(0, 20);
}
void ScoreDisplay::RenderBG()
{
	this->scoreBG->Render();
	this->bestScoreBG->Render();
}
void ScoreDisplay::RenderText()
{
	this->scoreText->Render();
	this->bestScoreText->Render();

	this->scoreValueText->Render();
	this->bestScoreValueText->Render();
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
	this->scoreValueText->SetString(std::to_string(this->score));

	this->RescaleBGs();
}
const int& ScoreDisplay::GetScore() const
{
	return this->score;
}

void ScoreDisplay::SetBestScore(int targetBestScore)
{
	this->bestScore = targetBestScore;
	this->bestScoreValueText->SetString(std::to_string(this->bestScore));

	this->RescaleBGs();
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