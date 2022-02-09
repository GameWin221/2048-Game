#pragma once

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Sprite.hpp"
#include "Text.hpp"

class Block
{
private:
	float gridBlockOffset;

public:
	void Render();
	void RenderText();
	void Promote();

	Sprite* sprite;

	int value;

	bool deleteQueued;

	glm::ivec2 gridPos;

	Text* valueText;

	Block(glm::ivec2 pos, const float& gridOffset, int val);
	~Block();
};

#endif 