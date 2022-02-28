#include "Game/GameLoader.hpp"

namespace GameLoader
{
	const std::string saveName = "Game";
	const std::string saveExtension = ".save";
	const std::string saveFolder = "Saves/";

	// First line - Score
	// Every other line - Blocks

	bool SaveExists(const Grid* grid)
	{
		std::ifstream file(saveFolder + saveName + std::to_string(grid->gridSize) + saveExtension);

		int lineCount = 0;

		if (file)
		{
			std::string str;

			while (std::getline(file, str))
				lineCount++;

			if (lineCount >= 2)
				return true;
		}

		return false;
	}

	void Load(Grid* grid, ScoreDisplay* scoreDisplay)
	{
		std::vector<Block>& blocks = grid->blocks;

		blocks.clear();
		blocks.shrink_to_fit();

		std::ifstream file(saveFolder + saveName + std::to_string(grid->gridSize) + saveExtension);

		if (file)
		{
			std::string str;
			std::getline(file, str);
			scoreDisplay->SetScore(std::stoi(str));

			while (std::getline(file, str))
			{
				std::istringstream ss(str);
				std::string bX, bY, bV;

				ss >> bX;
				ss >> bY;
				ss >> bV;

				int blockXPos, blockYPos, blockValue;

				blockXPos = std::stoi(bX);
				blockYPos = std::stoi(bY);
				blockValue = std::stoi(bV);

				grid->AddBlock(glm::ivec2(blockXPos, blockYPos), blockValue);
			}
		}
		else
		{
			std::ofstream newFile(saveFolder + saveName + std::to_string(grid->gridSize) + saveExtension);
			newFile.close();
		}
	}

	void Save(const Grid* grid, const ScoreDisplay* scoreDisplay)
	{
		const std::vector<Block>& blocks = grid->blocks;

		std::ofstream file(saveFolder + saveName + std::to_string(grid->gridSize) + saveExtension);
		if (file)
		{
			file << scoreDisplay->GetScore() << "\n";

			for (auto& block : blocks)
				file << block.targetGridPos.x << " " << block.targetGridPos.y << " " << block.value << "\n";

			file.close();
		}
		else
			std::cout << "Failed to open \"" << saveFolder + saveName + std::to_string(grid->gridSize) + saveExtension << "\" for saving!\n";
	}
}