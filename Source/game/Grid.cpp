#include "game/Grid.hpp"

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

bool Grid::CanMergeAnyBlock()
{
	int bID = 0;
	for (auto& block : this->blocks)
	{
		int cbID = 0;
		for (auto checkedBlock : this->blocks)
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
void Grid::SortBlocks(Direction& dir)
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
	gridTexture = new Texture("Resources/Textures/Grid.png");

	int wX, wH;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wH);

	this->gridSize = size;
	this->gridOffset = float(wX) / gridSize;

	this->sprite = new Sprite(gridTexture, glm::vec2(0), glm::vec2(wX));
	this->sprite->texture->tiling = glm::vec2(gridSize*2);
	this->sprite->color = glm::vec3(0.0f, 0.0f, 0.0f);

	this->canSpawnBlock = false;
	this->blocksMoving = false;

	this->blockMoveSpeed = 2500.0f * (wX / 1024.0f); // Scale the block movement speed relatively to the window size (the game was developed on a 1024x1224 window)
}
Grid::~Grid(){}

void Grid::Update(const double& deltaTime, ScoreDisplay* scoreDisplay)
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

		// If the block isn't at its target yet (or won't be at the next frame)
		if (block.target.distanceTravelled + speed < block.target.distanceTarget)
		{
			// Move the block towards its target
			block.target.distanceTravelled += speed;
			block.sprite->position += -block.target.targetDir * speed;
		}
		// If the block is at its target
		else
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
		this->blocksMoving = false;
	else
		this->blocksMoving = true;

	// When stopped moving blocks (1 frame)
	if (!this->blocksMoving && this->canSpawnBlock)
	{
		this->SpawnRandomBlock();
		this->canSpawnBlock = false;

		this->blocks.shrink_to_fit();
		this->lastBlocks.shrink_to_fit();
		
		// If there's no free space on the grid
		if(this->blocks.size() >= gridSize*gridSize)
		{
			if (!CanMergeAnyBlock())
			{
				std::cout << "You lost! (Zmien to pozniej w Grid::Update())\n";
				std::this_thread::sleep_for(std::chrono::seconds(1));

				this->Reset();
				scoreDisplay->SaveBestScore();
				scoreDisplay->SetScore(0);
			}
		}
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
		this->lastBlocks.clear();
		this->lastBlocks = this->blocks;

		this->canSpawnBlock = true;

		const glm::ivec2 vDir = DirToVec(dir);

		// Sort the blocks in order to move them in a correct order
		this->SortBlocks(dir);

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
								checkedBlock.promoteQueued = true;
								block.deleteQueued = true;
								block.mergeToID = cbID;
								block.targetGridPos = checkedBlock.targetGridPos;
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

		// Cache the blocks targets and distances to travel
		for (auto& block : this->blocks)
		{
			glm::vec2 targetPos = glm::vec2(gridOffset * block.targetGridPos.x, gridOffset * block.targetGridPos.y) + glm::vec2(gridOffset / 2.0f);
			glm::vec2 targetDir = glm::normalize(block.sprite->position - targetPos);

			float distanceTarget = glm::length(block.sprite->position - targetPos);
			float distanceTravelled = 0.0f;

			block.target.targetPos = targetPos;
			block.target.targetDir = targetDir;
			block.target.distanceTarget = distanceTarget;
			block.target.distanceTravelled = distanceTravelled;
		}
	}
}

void Grid::Reset()
{
	this->blocks.clear();

	this->canSpawnBlock = false;
	this->blocksMoving = false;

	this->SpawnRandomBlock();
}

void Grid::UndoBlocks()
{
	std::cout << "Grid::UndoBlocks() - linijka 318 - wylaczone bo jest memory leak w tej funkcji\n";
	/*
	this->blocks.clear();
	this->blocks.shrink_to_fit();
	this->blocks.reserve(0);

	for (auto& bl : this->lastBlocks)
	{
		this->blocks.push_back(
		Block(bl.targetGridPos, this->gridOffset, bl.value)
		);
	}

	this->lastBlocks.clear();
	this->lastBlocks.shrink_to_fit();
	this->lastBlocks.reserve(0);
	*/
}

// RNG
std::random_device device;
std::mt19937 gen(device());

Block* newBlock=nullptr;
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
void Grid::AddBlock(glm::vec2 spawnPos, int spawnValue)
{
	newBlock = new Block(spawnPos, this->gridOffset, spawnValue);
	this->blocks.emplace_back(*newBlock);
}