#include "Core/Gfx/Window.hpp"

Window::Window(glm::uvec2 size, std::string name)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glfwWindow = glfwCreateWindow(size.x, size.y, name.c_str(), NULL, NULL);

	if (glfwWindow == NULL)
	{
		std::cout << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(glfwWindow);

	glewInit();
	glewExperimental = true;
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_MULTISAMPLE);

	glfwSwapInterval(1);

	glViewport(0, 0, size.x, size.y);
	glfwSetFramebufferSizeCallback(glfwWindow, framebuffer_size_callback);
}
Window::~Window()
{
	glfwTerminate();
}

bool Window::IsOpen()
{
	return !glfwWindowShouldClose(glfwWindow);
}

void Window::PollEvents()
{
	glfwPollEvents();
}
void Window::Clear(glm::vec4 color)
{
	glClearColor(color.x, color.y, color.z, color.w);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Window::Display()
{
	glfwSwapBuffers(glfwWindow);
}

void Window::Close()
{
	glfwSetWindowShouldClose(glfwWindow, true);
}

// Callbacks
void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}