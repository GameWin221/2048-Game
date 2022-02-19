#include "game/Input.hpp"

bool upWasPressed    = false;
bool downWasPressed  = false;
bool rightWasPressed = false;
bool leftWasPressed  = false;

#define UpDirKeyPress    (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP   ) == GLFW_PRESS)
#define DownDirKeyPress  (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS)
#define RightDirKeyPress (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
#define LeftDirKeyPress  (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS)

namespace Input
{
	void UpdateOldInputs()
	{
		GLFWwindow* window = glfwGetCurrentContext();

		if (UpDirKeyPress)
			upWasPressed = true;
		else
			upWasPressed = false;

		if (DownDirKeyPress)
			downWasPressed = true;
		else
			downWasPressed = false;

		if (RightDirKeyPress)
			rightWasPressed = true;
		else
			rightWasPressed = false;

		if (LeftDirKeyPress)
			leftWasPressed = true;
		else
			leftWasPressed = false;
	}
	bool Clicked(Direction directionKey)
	{
		GLFWwindow* window = glfwGetCurrentContext();

		switch (directionKey)
		{
		case Up:
			if (!upWasPressed && UpDirKeyPress)
				return true;
			else return false;
			break;

		case Down:
			if (!downWasPressed && DownDirKeyPress)
				return true;
			else return false;
			break;

		case Right:
			if (!rightWasPressed && RightDirKeyPress)
				return true;
			else return false;
			break;
		case Left:
			if (!leftWasPressed && LeftDirKeyPress)
				return true;
			else return false;
			break;
		default: break;
		}
	}

}