#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Sprite.hpp"

class Block
{
private:
	Sprite* sprite;

	float gridBlockOffset;

public:
	void Render();
	void Promote();

	int value;

	glm::ivec2 gridPos;

	Block(glm::ivec2 pos, const float& gridOffset, unsigned int val);
	~Block();
};

#endif 