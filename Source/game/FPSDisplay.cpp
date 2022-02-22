#include "game/FPSDisplay.hpp"

FPSDisplay::FPSDisplay()
{
	int wX, wY;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &wX, &wY);
	glm::vec2 position(wX, wY);
	position.x *= 0.85f;
	position.y *= 0.95f;

	this->fpsText = new Text(Font::DefaultFont(), "");
	this->fpsText->position = position;
	this->fpsText->color = glm::vec3(0.97f, 0.18, 0.18f);
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

	int fpsRounded = (int)std::trunc(this->fps + 0.5);
	this->fpsText->SetString(std::to_string(fpsRounded));

	this->lastTick = high_resolution_clock::now();
}

void FPSDisplay::Render()
{
	this->fpsText->Render();
}