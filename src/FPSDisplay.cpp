#include "FPSDisplay.hpp"

FPSDisplay::FPSDisplay(glm::vec2 position, float scale)
{
	this->fpsText = new Text("FPS", scale);
	this->fpsText->position = position;

	this->deltaTime = -1.0;

	this->lastTick = std::chrono::high_resolution_clock::now();
}
FPSDisplay::~FPSDisplay()
{
	delete this->fpsText;
};

void FPSDisplay::UpdateDT()
{
	using namespace std::chrono;

	auto nowTick = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(nowTick - lastTick);
	this->deltaTime = duration.count() / 1000000.0;

	this->fps = 1.0 / this->deltaTime;

	this->fpsText->SetString(std::to_string(this->fps));

	this->lastTick = high_resolution_clock::now();
}

void FPSDisplay::RenderFPS()
{
	this->fpsText->Render();
}