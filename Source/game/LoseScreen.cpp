#include "game/LoseScreen.hpp"

Texture* loseScreenTexture;

LoseScreen::LoseScreen()
{
	if (!loseScreenTexture)
		loseScreenTexture = new Texture("Resources/Textures/LoseScreenBG.png");

	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);

	this->isVisible = false;

	this->sprite = new Sprite(loseScreenTexture, glm::vec2((float)wX / 2.0f), glm::vec2((float)wX/2.0f));

	this->loseText = new Text(Font::DefaultFont(), "You Lost");
	this->loseText->centered = true;
	this->loseText->position = this->sprite->position + glm::vec2(0, (float)wY * 0.065f);

	this->restartText = new Text(Font::DefaultFont(), "Press the restart button!");
	this->restartText->centered = true;
	this->restartText->scale = 0.4f;
	this->restartText->position = this->loseText->position - glm::vec2(0, (float)wY * 0.08f);
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

		Text::InitInstancing();
		this->loseText->Render();
		this->restartText->Render();
	}
}