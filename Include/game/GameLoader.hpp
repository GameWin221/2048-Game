#ifndef GAMELOADER_HPP
#define GAMELOADER_HPP

#include "game/Grid.hpp"
#include "game/ScoreDisplay.hpp"

#include <fstream>
#include <string>
#include <sstream>

namespace GameLoader
{
	bool SaveExists(const Grid* grid);
	void Load(Grid* grid, ScoreDisplay* scoreDisplay);
	void Save(const Grid* grid, const ScoreDisplay* scoreDisplay);
}

#endif