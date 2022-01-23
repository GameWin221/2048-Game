#pragma once

#include "Block.hpp"
#include <vector>

#include "Direction.hpp"

class Grid
{
private:
	Sprite* sprite;

	unsigned int gridSize;

	float gridOffset;

public:
	Grid(unsigned int size);
	~Grid();

	std::vector<Block> blocks;

	void Render();
	void AddBlock(glm::vec2 spawnPos, int spawnValue);
	void MoveBlocks(Direction dir);
};