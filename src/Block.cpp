#include "Block.hpp"

Texture* blockTexture = nullptr;

Block::Block(glm::ivec2 pos, const float& gridOffset, unsigned int val)
{
	// Load the 'blockTexture' texture
	if (!blockTexture)
		blockTexture = new Texture("Textures/Tile.jpg");

	this->gridPos = pos;
	this->gridBlockOffset = gridOffset;
	this->value = value;


	// Create the block's sprite
	this->sprite = new Sprite(blockTexture, glm::vec2(0), 0.95f * glm::vec2(gridOffset/2.0));
}
Block::~Block()
{
}

void Block::Render()
{
	// Set the block's position to fit the grid
	this->sprite->position = glm::vec2(gridBlockOffset * this->gridPos.x, gridBlockOffset * this->gridPos.y) + glm::vec2(gridBlockOffset / 2.0f);
	this->sprite->Render();
}

void Block::Promote()
{
}
