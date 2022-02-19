#include "game/Button/Button.hpp"

Button::Button(){} // For inheritance
Button::Button(Sprite* buttonSprite)
{
	this->sprite = buttonSprite;
	this->wasPressed = false;
}

void Button::OnPress()
{
}

void Button::CheckPress()
{
	GLFWwindow* window = glfwGetCurrentContext();

	double mX, mY;
	glfwGetCursorPos(window, &mX, &mY);

	int wX, wY;
	glfwGetFramebufferSize(window, &wX, &wY);

	// Inverting the mouse Y axis
	const double mYNormalized = mY / (double)wY;
	mY = wY - (wY * mYNormalized);

	glm::vec2 distToCenter = this->sprite->position - glm::vec2(mX, mY);
	distToCenter.x = abs(distToCenter.x);
	distToCenter.y = abs(distToCenter.y);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		if (!wasPressed)
		{
			if (distToCenter.x < this->sprite->size.x &&
				distToCenter.y < this->sprite->size.y)
			{
				this->wasPressed = true;
				this->OnPress();
			}
		}
	}
	else
		this->wasPressed = false;
}

void Button::Render()
{
	this->sprite->Render();
}