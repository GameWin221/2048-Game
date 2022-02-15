#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Sprite.hpp"
#include "Text.hpp"

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

	glm::ivec2 targetGridPos;

	Block(glm::ivec2 pos, const float& gridOffset, int val);
	~Block();
};

#endif 