#include "Game/RestartButton.hpp"

Texture* restartTexture = nullptr;
Texture* buttonBlurTexture = nullptr;

RestartButton::RestartButton(Grid* mainGrid, ScoreDisplay* mainScoreDisplay)
{
	this->defaultColor = glm::vec3(0.5f, 0.45f, 0.45f);
	this->highlightedColor = this->defaultColor * 0.8f;
	this->glowColor = glm::vec3(247, 154, 32)/255.0f;
	this->glowHighlightedColor = this->glowColor * 0.8f;

	this->grid = mainGrid;
	this->score = mainScoreDisplay;

	if(!restartTexture)
		restartTexture = new Texture("Resources/Textures/BGWide.png");

	if (!buttonBlurTexture)
		buttonBlurTexture = new Texture("Resources/Textures/BGWideBlur.png");

	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);

	this->sprite		= new Sprite(restartTexture);
	this->sprite->size  = glm::vec2((float)wX/6.0f, 60.0f);
	this->sprite->color = defaultColor;

	this->sprite->position    = glm::vec2(wX, wY);
	this->sprite->position.x *= 0.83f;
	this->sprite->position.y *= 0.938f;

	this->text			 = new Text(Font::DefaultFont(), "New Game");
	this->text->position = this->sprite->position;
	this->text->color	 = glm::vec3(0.2f);
	this->text->scale	 = 0.4f;
	this->text->centered = true;

	this->blur			 = new Sprite(buttonBlurTexture);
	this->blur->position = this->sprite->position;
	this->blur->size	 = this->sprite->size * 1.06f;
	this->blur->color	 = this->glowColor;
}

RestartButton::~RestartButton(){}

void RestartButton::SetGlow(bool glow)
{
	if (glow)
		this->sprite->color = this->glowColor;
	else
		this->sprite->color = this->defaultColor;
}


void RestartButton::OnHover()
{
	if (this->sprite->color != this->glowColor && this->sprite->color != this->glowHighlightedColor)
		this->sprite->color = this->highlightedColor;
	else
		this->sprite->color = this->glowHighlightedColor;
}
void RestartButton::OnIdle()
{
	if (this->sprite->color != this->glowColor && this->sprite->color != this->glowHighlightedColor)
		this->sprite->color = this->defaultColor;
	else
		this->sprite->color = this->glowColor;
}
void RestartButton::OnPress()
{
	this->grid->Reset();
	this->score->SetScore(0);
	this->SetGlow(false);
}

void RestartButton::Render()
{
	if (this->sprite->color == this->glowColor || this->sprite->color == this->glowHighlightedColor)
		this->blur->Render();

	this->sprite->Render();
}

void RestartButton::RenderText()
{
	this->text->Render();
}