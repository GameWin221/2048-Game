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
	float deltaTime;
	float fps;

	void UpdateDT();
	void RenderFPS();

	FPSDisplay(glm::vec2 position, float scale);
	~FPSDisplay();
};

#endif