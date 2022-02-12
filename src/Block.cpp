#include "Block.hpp"

Texture* blockTexture = nullptr;

const glm::vec3 ValueToColor(int& value)
{
	switch (value)
	{
	case 2:
		return glm::vec3(0.5f, 0.9f, 0.1f);
		break;
	case 4:
		return glm::vec3(0.5f, 0.1f, 0.9f);
		break;
	case 8:
		return glm::vec3(0.0f, 1.0f, 0.7f);
		break;
	case 16:
		return glm::vec3(1.0f, 1.0f, 0.0f);
		break;
	case 32:
		return glm::vec3(1.0f, 0.7f, 0.0f);
		break;
	case 64:
		return glm::vec3(1.0f, 0.1f, 0.1f);
		break;
	case 128:
		return glm::vec3(0.1f, 1.0f, 0.0f);
		break;
	case 256:
		return glm::vec3(1.0f, 0.0f, 0.0f);
		break;
	case 512:
		return glm::vec3(0.5f, 0.8f, 0.8f);
		break;
	case 1024:
		return glm::vec3(0.0f, 0.9f, 0.9f);
		break;
	case 2048:
		return glm::vec3(0.0f, 1.0f, 1.0f);
		break;

	default:
		return glm::vec3(0.0f, 1.0f, 1.0f);
		break;
	}
}

Block::Block(glm::ivec2 pos, const float& gridOffset, int val)
{
	// Load the 'blockTexture' texture
	if (!blockTexture)
		blockTexture = new Texture("Textures/Tile.jpg");

	this->gridPos = pos;
	this->gridBlockOffset = gridOffset;
	this->value = val;

	this->deleteQueued = false;

	// Create the block's sprite
	this->sprite = new Sprite(blockTexture, glm::vec2(0), 0.95f * glm::vec2(gridOffset/2.0));
	this->sprite->color = ValueToColor(this->value);

	this->valueText = new Text(std::to_string(this->value));
	this->valueText->scale = this->sprite->size.x*0.008f;
	this->valueText->centered = true;
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
void Block::RenderText()
{
	this->valueText->position = this->sprite->position;
	this->valueText->Render();
}

void Block::Promote()
{
	this->value *= 2;
	this->sprite->color = ValueToColor(this->value);
	this->valueText->SetString(std::to_string(this->value));
}