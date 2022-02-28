#include "Core/Button.hpp"

Button::Button(){} // For inheritance
Button::Button(Sprite* buttonSprite)
{
	this->sprite = buttonSprite;
	this->mouseWasPressed = false;

	this->defaultColor = glm::vec3(1);
	this->highlightedColor = glm::vec3(0.8f);
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
		if (!mouseWasPressed)
		{
			this->mouseWasPressed = true;

			if (distToCenter.x < this->sprite->size.x &&
				distToCenter.y < this->sprite->size.y)
			{
				this->OnPress();
			}
		}
	}
	else
		this->mouseWasPressed = false;
}

void Button::Render()
{
	this->sprite->Render();
}