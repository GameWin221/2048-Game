#include "game/Button/RestartButton.hpp"

Texture* restartTexture = nullptr;

RestartButton::RestartButton() {} // For inheritance
RestartButton::RestartButton(Grid* mainGrid, ScoreDisplay* mainScoreDisplay)
{
	this->grid = mainGrid;
	this->score = mainScoreDisplay;

	if(!restartTexture)
		restartTexture = new Texture("Resources/Textures/RestartButton.png");

	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);

	this->sprite = new Sprite(restartTexture);
	this->sprite->size = glm::vec2((float)wX/16.0f);
	this->sprite->color = glm::vec3(1.0f, 1.0f, 0.0f);

	this->sprite->position = glm::vec2(wX, wY);
	this->sprite->position.x *= 0.86f;
	this->sprite->position.y *= 0.945f;
}

RestartButton::~RestartButton(){}

void RestartButton::OnPress()
{
	this->grid->Reset();
	this->score->SetScore(0);
}