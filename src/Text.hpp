#pragma once

#ifndef TEXT_HPP
#define TEXT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H 

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include "Shader.hpp"

struct point {
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;
};

class Text
{
private:
	GLuint VAO, VBO;

	std::vector<point> vertices;

	std::string text;

	// Size of the text's bounds in pixels
	glm::vec2 textBounds;

public:
	Text(std::string newText, float newScale = 1.0f, glm::vec3 newColor = glm::vec3(0));
	~Text();

	static void InitInstancing();

	void SetString(std::string newText);
	std::string GetString();

	bool centered;

	glm::vec3 color;
	glm::vec2 position;
	float scale;

	void Render();
};

#endif