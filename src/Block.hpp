#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Sprite.hpp"
#include "Text.hpp"

struct Target
{
	glm::vec2 targetPos;
	glm::vec2 targetDir;
	float distanceTarget;
	float distanceTravelled;
};

class Block
{
private:
	Text* valueText;

public:
	void Render();
	void RenderText();
	void Promote();

	int value;

	bool promoteQueued;
	bool deleteQueued;
	
	Sprite* sprite;
	Target target;

	// The index of a block it's going to merge with
	int mergeToID;


	glm::ivec2 targetGridPos;

	Block(glm::ivec2 pos, const float& gridOffset, int val);
	~Block();
};

#endif 