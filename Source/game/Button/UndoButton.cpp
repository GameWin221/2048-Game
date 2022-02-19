#include "game/Button/UndoButton.hpp"

Texture* undoTexture = nullptr;

UndoButton::UndoButton(Grid* mainGrid, ScoreDisplay* mainScoreDisplay)
{
	this->grid = mainGrid;
	this->score = mainScoreDisplay;

	if (!undoTexture)
		undoTexture = new Texture("Resources/Textures/UndoButton.png");

	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);

	this->sprite = new Sprite(undoTexture);
	this->sprite->size = glm::vec2((float)wX / 16.0f);
	this->sprite->color = glm::vec3(1.0f, 1.0f, 0.0f);

	this->sprite->position = glm::vec2(wX, wY);
	this->sprite->position.x *= 0.7f;
	this->sprite->position.y *= 0.945f;
}
UndoButton::~UndoButton(){}

void UndoButton::OnPress()
{
	this->grid->UndoBlocks();
	this->score->UndoScore();
}