#include "FPSDisplay.hpp"

FPSDisplay::FPSDisplay(glm::vec2 position, float scale)
{
	this->fpsText = new Text(Font::DefaultFont(), "FPS: ", scale);
	this->fpsText->position = position;
	this->fpsText->color = glm::vec3(0.9f, 0.0, 0.5f);
	this->fpsText->scale = 0.5f;

	this->deltaTime = 0.0;
	this->fps = 0.0;

	this->lastTick = std::chrono::high_resolution_clock::now();
}
FPSDisplay::~FPSDisplay()
{
	delete this->fpsText;
};

void FPSDisplay::UpdateDT()
{
	using namespace std::chrono;

	auto now = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(now - lastTick);

	this->deltaTime = duration.count() / 1000000.0;

	this->fps = 1.0 / this->deltaTime;

	this->fpsText->SetString("FPS: " + std::to_string(this->fps));

	this->lastTick = high_resolution_clock::now();
}

void FPSDisplay::RenderFPS()
{
	this->fpsText->Render();
}