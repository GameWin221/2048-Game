#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "gfx/Sprite.hpp"
#include "gfx/Text/Text.hpp"

struct Target
{
	glm::vec2 targetPos;
	glm::vec2 targetDir;
	float distanceTarget;
	float distanceTravelled;
};

class Block
{
public:
	void RenderSprite();
	void RenderText();
	void Promote();

	int value;

	bool promoteQueued;
	bool deleteQueued;
	
	Sprite* sprite;
	Text* valueText;
	Target target;

	// The index of a block it's going to merge with
	int mergeToID;


	glm::ivec2 targetGridPos;

	Block(glm::ivec2 pos, const float& gridOffset, int val);

	Block(const Block& other) 
	{
		this->valueText = other.valueText;
		this->value = other.value;
		this->promoteQueued = other.promoteQueued;
		this->deleteQueued = other.deleteQueued;
		this->sprite = other.sprite;
		this->target = other.target;
		this->mergeToID = other.mergeToID;
		this->targetGridPos = other.targetGridPos;
	};

	Block& operator=(const Block& other)
	{
		this->valueText = other.valueText;
		this->value = other.value;
		this->promoteQueued = other.promoteQueued;
		this->deleteQueued = other.deleteQueued;
		this->sprite = other.sprite;
		this->target = other.target;
		this->mergeToID = other.mergeToID;
		this->targetGridPos = other.targetGridPos;

		return *this;
	}
};

#endif 