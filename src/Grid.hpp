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

	std::vector<glm::vec2> targetPosCache;
	std::vector<glm::vec2> targetDirCache;
	std::vector<float> distanceTargetCache;
	std::vector<float> distanceTravelledCache;

	unsigned int gridSize;
	float gridOffset;

	bool blocksMoving;
	const float blockMoveSpeed = 1700.0f;

public:
	Grid(unsigned int size);
	~Grid();

	std::vector<Block> blocks;

	void Update(double& deltaTime);
	void Render();
	void SpawnRandomBlock();

	void AddBlock(glm::vec2 spawnPos, int spawnValue);

	void MoveBlocks(Direction dir);
};