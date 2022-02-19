#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>

#include <string>
#include <iostream>

class Window
{
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);


public:
	GLFWwindow* glfwWindow;

	Window(glm::uvec2 size, std::string name);
	~Window();

	bool IsOpen();

	void Clear(glm::vec4 color);
	void Display();

	void PollEvents();
	void Close();
};

#endif