#include "Game/Block.hpp"

Texture* blockTexture = nullptr;
Texture* blurTexture = nullptr;

constexpr glm::vec3 ColorLUT(int& value) // Colors are still not final
{
	switch (value)
	{
	case 2:
		return glm::vec3(27, 134, 242) / 255.0f;
		break;
	case 4:
		return glm::vec3(255, 255, 20) / 255.0f;
		break;
	case 8:
		return glm::vec3(101, 232, 0) / 255.0f;
		break;
	case 16:
		return glm::vec3(174, 0, 232) / 255.0f;
		break;
	case 32:
		return glm::vec3(247, 118, 5) / 255.0f;
		break;
	case 64:
		return glm::vec3(247, 55, 30) / 255.0f;
		break;
	case 128:
		return glm::vec3(250, 135, 35) / 255.0f;
		break;
	case 256:
		return glm::vec3(247, 30, 182) / 255.0f;
		break;
	case 512:
		return glm::vec3(222, 33, 140) / 255.0f;
		break;
	case 1024:
		return glm::vec3(197, 33, 222) / 255.0f;
		break;
	case 2048:
		return glm::vec3(162, 33, 222) / 255.0f;
		break;
	case 4096:
		return glm::vec3(150, 25, 252) / 255.0f;
		break;

	default:
		return glm::vec3(33, 55, 255)/255.0f;
		break;
	}
}

Block::Block(glm::ivec2 pos, const float& gridOffset, int val)
{
	if (!blockTexture)
		blockTexture = new Texture("Resources/Textures/TileRound.png");

	if (!blurTexture)
		blurTexture = new Texture("Resources/Textures/BlockBlur.png");

	this->targetGridPos = pos;
	this->value = val;

	this->deleteQueued  = false;
	this->promoteQueued = false;

	this->sprite		   = new Sprite(blockTexture);
	this->sprite->color	   = ColorLUT(this->value);
	this->sprite->position = glm::vec2(gridOffset * this->targetGridPos.x, gridOffset * this->targetGridPos.y) + glm::vec2(gridOffset / 2.0f);
	this->sprite->size	   = glm::vec2(gridOffset / 2.0f);

	this->blur			 = new Sprite(blurTexture);
	this->blur->color	 = this->sprite->color;
	this->blur->position = this->sprite->position;
	this->blur->size	 = this->sprite->size * 1.02f;
	this->blur->opacity  = 0.4f;

	this->valueText			  = new Text(Font::DefaultFont(), std::to_string(this->value));
	this->valueText->scale    = this->sprite->size.x*0.008f;
	this->valueText->centered = true;

	this->target.targetPos         = this->sprite->position;
	this->target.targetDir         = glm::vec2(0);
	this->target.distanceTarget    = 0.0f;
	this->target.distanceTravelled = 0.0f;

	this->mergeToID = -1;
}

void Block::RenderSprite()
{
	this->blur->color = this->sprite->color;
	this->blur->position = this->sprite->position;
	this->blur->Render();

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

	this->sprite->color = ColorLUT(this->value);
	this->valueText->SetString(std::to_string(this->value));

	this->promoteQueued = false;
}