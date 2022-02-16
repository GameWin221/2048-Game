#pragma once

#include "Block.hpp"
#include "Direction.hpp"
#include "ScoreDisplay.hpp"

#include <vector>
#include <map>
#include <random>

class Grid
{
private:
	Sprite* sprite;

	unsigned int gridSize;
	float gridOffset;

	bool canSpawnBlock;
	bool blocksMoving;
	const float blockMoveSpeed = 2500.0f;

public:
	Grid(unsigned int size);
	~Grid();

	std::vector<Block> blocks;

	void Update(double& deltaTime, ScoreDisplay* scoreDisplay);
	void Render();
	void SpawnRandomBlock();

	void AddBlock(glm::vec2 spawnPos, int spawnValue);

	void MoveBlocks(Direction dir);
};