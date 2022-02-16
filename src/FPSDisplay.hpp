#pragma once

#ifndef FPSDISPLAY_HPP
#define FPSDISPLAY_HPP

#include "Text.hpp"

#include <chrono>

class FPSDisplay
{
private:
	Text* fpsText;

	std::chrono::time_point<std::chrono::high_resolution_clock> lastTick;

public:
	double deltaTime;
	double fps;

	void UpdateDT();
	void Render();

	FPSDisplay();
	~FPSDisplay();
};

#endif