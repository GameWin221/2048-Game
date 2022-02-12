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


void Grid::MoveBlocksSmooth(float speed)
{
	for (this->blocks)
	{

	}
}

Grid::Grid(unsigned int size)
{
	gridTexture = new Texture("Textures/Grid.jpg");

	this->gridSize = size;
	this->gridOffset = 1024.0f / gridSize;

	this->sprite = new Sprite(gridTexture, glm::vec2(0), glm::vec2(1024.0f));
	this->sprite->texture->tiling = glm::vec2(gridSize*2);
}
Grid::~Grid(){}

void Grid::Render()
{
	this->sprite->Render();
}

void Grid::MoveBlocks(Direction dir)
{
	const glm::ivec2 vDir = DirToVec(dir);

	// Sort the blocks in order to move them in a correct order
	SortBlocks(dir, this->blocks);

	int bID = 0;
	for (auto& block : this->blocks)
	{
		bool isOccupied = false;

		// Move the block as far as possible
		while (!isOccupied)
		{
			const glm::ivec2 newPos = block.gridPos + vDir;

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
					if (checkedBlock.gridPos == newPos && !checkedBlock.deleteQueued)
					{
						isOccupied = true;

						// Check if the block can merge with the checkedBlock
						if (checkedBlock.value == block.value)
						{
							checkedBlock.Promote();		// Promote the hit block
							block.deleteQueued = true;	// Mark the block that hit as deleted
						}

						break;
					}
				}
				cbID++;
			}

			// Move the block if possible
			if (!isOccupied)
				block.gridPos = newPos;
		}

		bID++;
	}

	// Delete blocks marked as deleted
	for (int i = 0; i < blocks.size(); i++)
		if (blocks[i].deleteQueued)
			blocks.erase(blocks.begin() + i--);

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
		spotsVec[b.gridPos.x][b.gridPos.y] = false;
	
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