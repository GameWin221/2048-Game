#include "game/Button/RestartButton.hpp"

Texture* restartTexture = nullptr;

RestartButton::RestartButton(Grid* mainGrid, ScoreDisplay* mainScoreDisplay)
{
	this->defaultColor = glm::vec3(0.4f);
	this->glowColor = glm::vec3(247, 154, 32)/255.0f;

	this->grid = mainGrid;
	this->score = mainScoreDisplay;

	if(!restartTexture)
		restartTexture = new Texture("Resources/Textures/BGWide.png");

	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);

	this->sprite = new Sprite(restartTexture);
	this->sprite->size = glm::vec2((float)wX/6.0f, 60.0f);
	this->sprite->color = defaultColor;

	this->sprite->position = glm::vec2(wX, wY);
	this->sprite->position.x *= 0.83f;
	this->sprite->position.y *= 0.938f;

	this->text = new Text(Font::DefaultFont(), "New Game");
	this->text->position = this->sprite->position;
	this->text->color = glm::vec3(0.2f);
	this->text->scale = 0.4f;
	this->text->centered = true;
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

void RestartButton::RenderText()
{
	this->text->Render();
}