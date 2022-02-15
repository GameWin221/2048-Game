#include "Grid.hpp"

Texture* gridTexture = nullptr;

glm::ivec2 DirToVec(Direction& dir)
{
	glm::ivec2 vec;

	switch (dir)
	{
	case Up:
		vec = glm::ivec2(0, 1);
		break;
	case Down:
		vec = glm::ivec2(0, -1);
		break;

	case Right:
		vec = glm::ivec2(1, 0);
		break;
	case Left:
		vec = glm::ivec2(-1, 0);
		break;
	default: break;
	}

	return vec;
}
void Switch(std::vector<Block>& blocks, int &index)
{
	Block c = blocks[index];
	blocks[index] = blocks[index+1];
	blocks[index+1] = c;
}

void SortBlocks(Direction& dir, std::vector<Block>& blocks)
{
	bool checkX;
	bool checkGreater;

	switch (dir)
	{
	case Up:
		checkX = false;
		checkGreater = true;
		break;
	case Down:
		checkX = false;
		checkGreater = false;
		break;
	case Left:
		checkX = true;
		checkGreater = false;
		break;
	case Right:
		checkX = true;
		checkGreater = true;
		break;
	default: break;
	}
	
	
	// I know it's unefficient... I may change it later
	for (auto& b : blocks)
	{
		for (int i = 0; i < blocks.size() - 1; i++)
		{
			if (checkX)
			{
				if (checkGreater)
				{
					if (blocks[i].targetGridPos.x < blocks[i + 1].targetGridPos.x)
						Switch(blocks, i);
				}
				else
				{
					if (blocks[i].targetGridPos.x > blocks[i + 1].targetGridPos.x)
						Switch(blocks, i);
				}
			}
			else
			{
				if (checkGreater)
				{
					if (blocks[i].targetGridPos.y < blocks[i + 1].targetGridPos.y)
						Switch(blocks, i);
				}
				else
				{
					if (blocks[i].targetGridPos.y > blocks[i + 1].targetGridPos.y)
						Switch(blocks, i);
				}	
			}
		}
	}
}

Grid::Grid(unsigned int size)
{
	gridTexture = new Texture("Textures/Grid.jpg");

	this->gridSize = size;
	this->gridOffset = 1024.0f / gridSize;

	this->sprite = new Sprite(gridTexture, glm::vec2(0), glm::vec2(1024.0f));
	this->sprite->texture->tiling = glm::vec2(gridSize*2);

	this->SpawnRandomBlock();
}
Grid::~Grid(){}

void Grid::Update(double& deltaTime)
{
	float dtFloat = static_cast<float>(deltaTime);

	if (targetPosCache.size() > 0)
	{
		int blocksOnTarget = 0;
		const int blocksSize = blocks.size();

		for (int i = 0; i < blocks.size(); i++)
		//for (int i = blocks.size()-1; i > 0; i--)
		{
			if (distanceTravelledCache[i] < distanceTargetCache[i])
			{
				distanceTravelledCache[i] += blockMoveSpeed * dtFloat;
				blocks[i].sprite->position += -targetDirCache[i] * blockMoveSpeed * dtFloat;
			}
			else
			{
				blocks[i].sprite->position = targetPosCache[i];

				if (blocks[i].deleteQueued)
				{
					blocks.erase(blocks.begin() + i);
					targetPosCache.erase(targetPosCache.begin() + i);
					targetDirCache.erase(targetDirCache.begin() + i);
					distanceTargetCache.erase(distanceTargetCache.begin() + i);
					distanceTravelledCache.erase(distanceTravelledCache.begin() + i);
					i--;
					//i++;

					std::cout << "delete";
				}
				//tu nie dziala
				// The blocks cannot merge until promoted
				else if (blocks[i].promoteQueued)
				{
					std::cout << "promote";
					//blocks[i].promoteQueued = false;
					blocks[i].Promote();
				}

				blocksOnTarget++;
			}
		}

		if (blocksOnTarget == blocksSize)
			this->blocksMoving = false;
		else
			this->blocksMoving = true;
	}
}
void Grid::Render()
{
	this->sprite->Render();
}

void Grid::MoveBlocks(Direction dir)
{
	if (!this->blocksMoving)
	{
		const glm::ivec2 vDir = DirToVec(dir);

		// Sort the blocks in order to move them in a correct order
		SortBlocks(dir, this->blocks);

		targetPosCache.clear();
		targetDirCache.clear();
		distanceTargetCache.clear();
		distanceTravelledCache.clear();

		int bID = 0;
		for (auto& block : this->blocks)
		{
			bool isOccupied = false;

			// Move the block as far as possible
			while (!isOccupied)
			{
				const glm::ivec2 newPos = block.targetGridPos + vDir;

				// Check if the block won't go outside of the map
				if (newPos.x < 0 || newPos.y < 0 || newPos.x >= this->gridSize || newPos.y >= this->gridSize)
					isOccupied = true;

				int cbID = 0;
				// Check if the block won't collide with other
				for (auto& checkedBlock : this->blocks)
				{
					// If not checking itself
					if (bID != cbID)
					{
						// If collided with a block that isn't marked as deleted
						if (checkedBlock.targetGridPos == newPos && !checkedBlock.deleteQueued)
						{
							isOccupied = true;

							// If the 'block' can merge with 'checkedBlock'
							if (checkedBlock.value == block.value && !checkedBlock.promoteQueued)
							{
								block.deleteQueued = true;
								block.targetGridPos = checkedBlock.targetGridPos; // Move the block inside the other one to create an effect of merging
								checkedBlock.promoteQueued = true;
							}

							break;
						}
					}
					cbID++;
				}

				// Move the block if possible
				if (!isOccupied)
					block.targetGridPos = newPos;
			}

			bID++;
		}

		this->SpawnRandomBlock();

		// Cache the blocks targets and distances to travel
		for (auto& block : this->blocks)
		{
			glm::vec2 targetPos = glm::vec2(gridOffset * block.targetGridPos.x, gridOffset * block.targetGridPos.y) + glm::vec2(gridOffset / 2.0f);
			glm::vec2 targetDir = glm::normalize(block.sprite->position - targetPos);

			targetPosCache.push_back(targetPos);
			targetDirCache.push_back(targetDir);

			float distanceTarget = glm::length(block.sprite->position - targetPos);
			float distanceTravelled = 0.0f;

			distanceTargetCache.push_back(distanceTarget);
			distanceTravelledCache.push_back(distanceTravelled);
		}
	}
}

// RNG
std::random_device device;
std::mt19937 gen(device());

void Grid::SpawnRandomBlock()
{
	std::vector<std::vector<bool>> spotsVec;

	for (int x = 0; x < this->gridSize; x++)
	{
		std::vector<bool> vec;

		for (int y = 0; y < this->gridSize; y++)
			vec.push_back(true);
		
		spotsVec.push_back(vec);
	}

	for (auto& b : this->blocks)
		spotsVec[b.targetGridPos.x][b.targetGridPos.y] = false;
	
	std::vector<glm::ivec2> freeSpotsVec;

	for (int x = 0; x < spotsVec.size(); x++)
		for (int y = 0; y < spotsVec[x].size(); y++)
			if (spotsVec[x][y])
				freeSpotsVec.push_back(glm::ivec2(x, y));
		
	

	if (freeSpotsVec.size() > 0)
	{
		std::uniform_int_distribution<int> posDist(0, freeSpotsVec.size() - 1);

		glm::ivec2 position = freeSpotsVec[posDist(gen)];

		this->AddBlock(position, 2);
	}
	else
	{
		// lose
	}
}

void Grid::AddBlock(glm::vec2 spawnPos, int spawnValue)
{
	Block block(spawnPos, this->gridOffset, spawnValue);
	this->blocks.push_back(block);
}