#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Sprite.hpp"
#include "Text.hpp"

class Block
{
private:
	Sprite* sprite;

	float gridBlockOffset;

public:
	void Render();
	void Promote();

	int value;

	bool deleteQueued;

	glm::ivec2 gridPos;

	Text* valueText;

	Block(glm::ivec2 pos, const float& gridOffset, int val);
	~Block();
};

#endif 