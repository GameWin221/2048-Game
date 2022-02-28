#pragma once

#ifndef GRID_HPP
#define GRID_HPP

#include "Game/Block.hpp"
#include "Core/Direction.hpp"
#include "Game/ScoreDisplay.hpp"

#include <thread>
#include <vector>
#include <map>
#include <random>

class Grid
{
private:
	Sprite* sprite;

	float gridOffset;

	bool canSpawnBlock;
	bool blocksShouldMove;

	float blockMoveSpeed;

	bool CanMergeAnyBlock();
	void SortBlocks(const Direction& dir);

public:
	Grid(unsigned int size);

	std::vector<Block> blocks;

	unsigned int gridSize;

	bool shouldLose, lost;
	
	bool CheckLose();

	void Update(const double& deltaTime, ScoreDisplay* scoreDisplay);
	void Render();

	void Reset();

	void AddBlock(glm::ivec2 spawnPos, int spawnValue);
	void SpawnRandomBlock();

	void MoveBlocks(const Direction dir);
};

#endif