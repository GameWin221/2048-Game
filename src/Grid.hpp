#pragma once

#include "Block.hpp"
#include "Direction.hpp"
#include <vector>
#include <map>
#include <random>

class Grid
{
private:
	Sprite* sprite;

	unsigned int gridSize;

	float gridOffset;

	void MoveBlocksSmooth(float speed);

public:
	Grid(unsigned int size);
	~Grid();

	std::vector<Block> blocks;

	void Render();
	void SpawnRandomBlock();

	void AddBlock(glm::vec2 spawnPos, int spawnValue);

	void MoveBlocks(Direction dir);
};