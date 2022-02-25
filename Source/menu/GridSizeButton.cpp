#include "menu/GridSizeButton.hpp"

Texture* gridButtonTexture;

GridSizeButton::GridSizeButton(glm::vec2 buttonPosition, const int gSize)
{
	if (!gridButtonTexture)
		gridButtonTexture = new Texture("Resources/Textures/TileRound.png");

	this->sprite = new Sprite(gridButtonTexture);
	this->sprite->position = buttonPosition;
	this->sprite->color = glm::vec3(0.4);
	this->sprite->size = glm::vec2(110);

	this->gridSize = gSize;

	this->gridSizeText = new Text(Font::DefaultFont(),
		std::to_string(this->gridSize) + "x" + std::to_string(this->gridSize)
	);

	this->gridSizeText->position = this->sprite->position;
	this->gridSizeText->scale = 0.5f;
	this->gridSizeText->color = glm::vec3(0.2);
	this->gridSizeText->centered = true;
}

void GridSizeButton::RenderText()
{
	this->gridSizeText->Render();
}

void GridSizeButton::OnPress()
{
	
}