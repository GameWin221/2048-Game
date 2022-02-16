#include "ScoreDisplay.hpp"

ScoreDisplay::ScoreDisplay()
{
	this->score = 0;

	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);
	glm::vec2 position(wX, wY);
	position.x *= 0.05f;
	position.y *= 0.875f;
	
	this->scoreText = new Text(Font::DefaultFont(), "Score: 0");
	this->scoreText->position = position;
	this->scoreText->color = glm::vec3(0.0f, 0.0, 0.0f);
	this->scoreText->scale = 1.2f;
}

ScoreDisplay::~ScoreDisplay(){}

void ScoreDisplay::Render()
{
	this->scoreText->Render();
}

void ScoreDisplay::AddScore(int deltaScore)
{
	int newTarget = this->score + deltaScore;
	this->SetScore(newTarget);
}
void ScoreDisplay::SetScore(int targetScore)
{
	this->score = targetScore;
	this->scoreText->SetString("Score: " + std::to_string(this->score));
}
int ScoreDisplay::GetScore()
{
	return this->score;
}