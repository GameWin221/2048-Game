#include "game/Button/RestartButton.hpp"

Texture* restartTexture = nullptr;

RestartButton::RestartButton(Grid* mainGrid, ScoreDisplay* mainScoreDisplay)
{
	this->defaultColor = glm::vec3(1.0f);
	this->glowColor = glm::vec3(1.0f, 1.0f, 0.1f);

	this->grid = mainGrid;
	this->score = mainScoreDisplay;

	if(!restartTexture)
		restartTexture = new Texture("Resources/Textures/RestartButton.png");

	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);

	this->sprite = new Sprite(restartTexture);
	this->sprite->size = glm::vec2((float)wX/16.0f);
	this->sprite->color = defaultColor;

	this->sprite->position = glm::vec2(wX, wY);
	this->sprite->position.x *= 0.86f;
	this->sprite->position.y *= 0.945f;
}

RestartButton::~RestartButton(){}

void RestartButton::SetGlow(bool glow)
{
	if (glow)
		this->sprite->color = this->glowColor;
	else
		this->sprite->color = this->defaultColor;
}

void RestartButton::OnPress()
{
	this->grid->Reset();
	this->score->SetScore(0);
	this->SetGlow(false);
}