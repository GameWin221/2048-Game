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
					if (blocks[i].gridPos.x < blocks[i + 1].gridPos.x)
						Switch(blocks, i);
				}
				else
				{
					if (blocks[i].gridPos.x > blocks[i + 1].gridPos.x)
						Switch(blocks, i);
				}
			}
			else
			{
				if (checkGreater)
				{
					if (blocks[i].gridPos.y < blocks[i + 1].gridPos.y)
						Switch(blocks, i);
				}
				else
				{
					if (blocks[i].gridPos.y > blocks[i + 1].gridPos.y)
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

	this->sprite = new Sprite(gridTexture, glm::vec2(0), glm::vec2(gridOffset/2.0f));
}
Grid::~Grid(){}

void Grid::Render()
{
	for (int x = 0; x < this->gridSize; x++)
	{
		for (int y = 0; y < this->gridSize; y++)
		{
			this->sprite->position = glm::vec2(gridOffset * x, gridOffset * y) + glm::vec2(gridOffset / 2.0f);
			this->sprite->Render();
		}
	}
}

void Grid::MoveBlocks(Direction dir)
{
	const glm::ivec2 vDir = DirToVec(dir);

	// Sort the blocks in order to move them in a correct order
	SortBlocks(dir, this->blocks);

	for (auto& block : this->blocks)
	{
		bool isOccupied = false;

		// Move the block as far as possible
		while (!isOccupied)
		{
			const glm::ivec2 newPos = block.gridPos + vDir;

			// Check if the block won't go outside of the map
			if ((newPos.x < 0 || newPos.y < 0) || ((newPos.x >= this->gridSize || newPos.y >= this->gridSize)))
				isOccupied = true;

			// Check if the block won't collide with other
			for (auto& checkedBlock : this->blocks)
			{
				// If collided with a block that isn't queued to delete
				if (checkedBlock.gridPos == newPos && !checkedBlock.deleteQueued)
				{
					isOccupied = true;

					// Check if the block can merge with the checkedBlock
					if (checkedBlock.value == block.value)
					{
						checkedBlock.Promote();
						block.deleteQueued = true;
					}
					break;
				}
			}

			// Move the block if possible
			if (!isOccupied)
				block.gridPos = newPos;
		}
	}

	// Delete blocks marked as Deleted
	for (int i = 0; i < this->blocks.size(); i++)
	{
		if (this->blocks[i].deleteQueued)
			this->blocks.erase(this->blocks.begin() + i);
	}
	
}

void Grid::AddBlock(glm::vec2 spawnPos, int spawnValue)
{
	Block block(spawnPos, this->gridOffset, spawnValue);
	this->blocks.push_back(block);
}