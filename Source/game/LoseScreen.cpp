#include "game/LoseScreen.hpp"

Texture* loseScreenTexture = nullptr;
Texture* spriteBGTexture   = nullptr;

LoseScreen::LoseScreen()
{
	if (!loseScreenTexture)
		loseScreenTexture = new Texture("Resources/Textures/White.jpg");

	if (!spriteBGTexture)
		spriteBGTexture = new Texture("Resources/Textures/BGWide.png");

	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);

	this->isVisible = false;

	this->sprite = new Sprite(loseScreenTexture);
	this->sprite->position = 
	this->sprite->size = glm::vec2((float)wX / 2.0f);
	this->sprite->color = glm::vec3(0.18f);
	this->sprite->opacity = 0.8f;

	this->textBG = new Sprite(spriteBGTexture);
	this->textBG->position = this->sprite->position+glm::vec2(0, 30);
	this->textBG->size = glm::vec2((float)wX * 0.45f, (float)wX * 0.15f);
	this->textBG->color = glm::vec3(0.4f);

	this->loseText = new Text(Font::DefaultFont(), "You Lost");
	this->loseText->centered = true;
	this->loseText->position = this->sprite->position + glm::vec2(0, (float)wY * 0.065f);

	this->restartText = new Text(Font::DefaultFont(), "Press the \"New Game\" button!");
	this->restartText->centered = true;
	this->restartText->scale = 0.4f;
	this->restartText->position = this->loseText->position - glm::vec2(0, (float)wY * 0.09f);
	this->restartText->color = this->loseText->color = glm::vec3(0.2f);
}

void LoseScreen::SetVisibility(bool visibility)
{
	this->isVisible = visibility;
}

void LoseScreen::Render()
{
	if (this->isVisible)
	{
		Sprite::InitInstancing();
		this->sprite->Render();
		this->textBG->Render();

		Text::InitInstancing();
		this->loseText->Render();
		this->restartText->Render();
	}
}