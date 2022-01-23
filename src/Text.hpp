#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <map>

#include "Shader.hpp"


class Text
{
private:
	GLuint VAO, VBO;

public:
	Text(std::string newText, float newScale = 1.0f, glm::vec3 newColor = glm::vec3(0));

	glm::vec3 color;
	//glm::vec2 position;
	float scale;

	std::string text;

	void Render(std::string text, float x, float y);
};