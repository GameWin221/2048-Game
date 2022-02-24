#include "game/Grid.hpp"

Texture* gridTexture = nullptr;

glm::ivec2 DirToVec(const Direction& dir)
{
	glm::ivec2 vec(0);

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

bool Grid::CanMergeAnyBlock()
{
	int bID = 0;
	for (const auto& block : this->blocks)
	{
		int cbID = 0;
		for (const auto& checkedBlock : this->blocks)
		{
			// If not checking itself
			if (bID != cbID)
			{
				// If the checked block is within one block distance (not diagonally) to the block
				const glm::vec2 diff = block.targetGridPos - checkedBlock.targetGridPos;
				const int diffSum = abs(diff.x) + abs(diff.y);
				if (diffSum == 1 && checkedBlock.value == block.value)
					return true;
			}
			cbID++;
		}
		bID++;
	}

	return false;
}
void Grid::SortBlocks(const Direction& dir)
{
	bool checkX = true;
	bool checkGreater = false;

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
	}

	if (checkX) //Right / Left
	{
		if (checkGreater) // Right
		{
			auto compareType = [](const Block& lhs, const Block& rhs) {
				return lhs.targetGridPos.x > rhs.targetGridPos.x;
			};

			std::sort(blocks.begin(), blocks.end(), compareType);
		}
		else // Left
		{
			auto compareType = [](const Block& lhs, const Block& rhs) {
				return lhs.targetGridPos.x < rhs.targetGridPos.x;
			};

			std::sort(blocks.begin(), blocks.end(), compareType);
		}
	}
	else // Up / Down
	{
		if (checkGreater) // Up
		{
			auto compareType = [](const Block& lhs, const Block& rhs) {
				return lhs.targetGridPos.y > rhs.targetGridPos.y;
			};
			std::sort(blocks.begin(), blocks.end(), compareType);
		}
		else // Down
		{
			auto compareType = [](const Block& lhs, const Block& rhs) {
				return lhs.targetGridPos.y < rhs.targetGridPos.y;
			};

			std::sort(blocks.begin(), blocks.end(), compareType);
		}
	}
}
bool Grid::CheckLose()
{
	// If there's no free space on the grid and can't merge any block
	if (this->blocks.size() >= gridSize * gridSize && !CanMergeAnyBlock())
		this->shouldLose = true;

	return this->shouldLose;
}

Grid::Grid(unsigned int size)
{
	gridTexture = new Texture("Resources/Textures/TileRound.png");

	int wX, wH;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wH);

	this->gridSize = size;
	this->gridOffset = float(wX) / gridSize;

	this->sprite = new Sprite(gridTexture, glm::vec2(0), glm::vec2(wX));
	this->sprite->texture->tiling = glm::vec2(gridSize*2);
	this->sprite->color = glm::vec3(0.4f);

	this->shouldLose = false;
	this->lost = false;

	this->canSpawnBlock = false;

	this->blockMoveSpeed = 2600.0f * (wX / 900.0f); // Scale the block movement speed relatively to the window size
}

#define PI 3.1415926

// 0.0f - 0.999f
#define Smoothing 0.75f

void Grid::Update(const double& deltaTime, ScoreDisplay* scoreDisplay)
{
	if (this->blocksShouldMove)
	{
		// Used for fps-independant movement speed
		const float dtFloat = static_cast<float>(deltaTime);

		// Required to check if all of the blocks are at their target's position
		int blocksOnTarget = 0;
		const int blocksSize = blocks.size();

		const float speed = blockMoveSpeed * dtFloat;

		// Update all of the blocks
		for (int i = 0; i < blocks.size(); i++)
		{
			Block& block = blocks[i];

			// If the block isn't at its target yet
			if (block.target.distanceTravelled < block.target.distanceTarget)
			{
				const float norm = block.target.distanceTravelled / block.target.distanceTarget;
				float mult = (1.0f - Smoothing) + (std::sin(norm * PI) * Smoothing);
				
				// Move the block towards its target
				block.target.distanceTravelled += speed * mult;
				block.sprite->position += -block.target.targetDir * speed * mult;
			}

			// If the block reached its target
			if (block.target.distanceTravelled >= block.target.distanceTarget)
			{
				// Align the block to the grid
				block.sprite->position = block.target.targetPos;

				// If the block needs to be deleted (merged with another)
				if (block.deleteQueued)
				{
					// Promote the another block
					blocks[block.mergeToID].Promote();

					scoreDisplay->AddScore(blocks[block.mergeToID].value);

					// Lower 'mergeToID' in each block by 1
					for (auto& b : this->blocks)
					{
						if (b.mergeToID >= i)
							b.mergeToID--;
					}

					// Delete the block pointers
					delete block.sprite;
					delete block.valueText;

					// Delete the block and lower 'i' by 1
					blocks.erase(blocks.begin() + i--);

					// 'i' and 'mergeToID' are being lowered by 1 because as a block gets erased from 
					// the 'blocks' vector, every other block behind the erased one gets moved 1 index to the left
				}

				blocksOnTarget++;
			}
		}

		// If all blocks are on their targets
		if (blocksOnTarget == blocksSize)
			this->blocksShouldMove = false;

		// When stopped moving blocks (1 frame)
		if (!this->blocksShouldMove && this->canSpawnBlock)
		{
			this->SpawnRandomBlock();
			this->canSpawnBlock = false;

			this->CheckLose();
		}
	}
}
void Grid::Render()
{
	this->sprite->Render();
}

void Grid::MoveBlocks(const Direction dir)
{
	if (!this->blocksShouldMove)
	{
		const glm::ivec2 vDir = DirToVec(dir);

		// Sort the blocks to move them in a correct order
		this->SortBlocks(dir);

		volatile bool anyBlockWillMove = false;

		int bID = 0;
		for (auto& block : this->blocks)
		{
			bool isOccupied = false;
			
			// Move the block as far as possible
			while (!isOccupied)
			{
				const glm::ivec2 newPos = block.targetGridPos + vDir;

				// Check if the block will go outside of the map
				if (newPos.x < 0 || newPos.y < 0 || newPos.x >= this->gridSize || newPos.y >= this->gridSize)
					break;
				
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
								checkedBlock.promoteQueued = true;
								block.deleteQueued = true;
								block.mergeToID = cbID;
								block.targetGridPos = checkedBlock.targetGridPos;
								
								anyBlockWillMove = true;
							}

							break;
						}
					}
					cbID++;
				}
				
				// Move the block if possible
				if (!isOccupied)
				{
					block.targetGridPos = newPos;
					anyBlockWillMove = true;
				}
			}

			bID++;
		}

		// Cache the blocks targets and distances to travel
		for (auto& block : this->blocks)
		{
			const glm::vec2 targetPos = glm::vec2(gridOffset * block.targetGridPos.x, gridOffset * block.targetGridPos.y) + glm::vec2(gridOffset / 2.0f);
			const glm::vec2 targetDir = glm::normalize(block.sprite->position - targetPos);

			const float distanceTarget = glm::length(block.sprite->position - targetPos);
			const float distanceTravelled = 0.0f;

			block.target.targetPos = targetPos;
			block.target.targetDir = targetDir;
			block.target.distanceTarget = distanceTarget;
			block.target.distanceTravelled = distanceTravelled;
		}
		
		if (anyBlockWillMove)
		{
			this->canSpawnBlock = true;
			this->blocksShouldMove = true;
		}
	}
}

void Grid::Reset()
{
	for (auto& block : this->blocks)
	{
		delete block.sprite;
		delete block.valueText;
	}

	this->blocks.clear();
	this->blocks.shrink_to_fit();

	this->canSpawnBlock = false;
	this->blocksShouldMove = false;
	this->lost = false;

	this->SpawnRandomBlock();
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
}
void Grid::AddBlock(glm::ivec2 spawnPos, int spawnValue)
{
	this->blocks.emplace_back(Block(spawnPos, this->gridOffset, spawnValue));
}