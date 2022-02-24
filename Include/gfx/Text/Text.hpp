#pragma once

#ifndef TEXT_HPP
#define TEXT_HPP

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <glew.h>
#include <glfw3.h>

#include <iostream>
#include <vector>

#include "gfx/Shader.hpp"
#include "gfx/Text/Font.hpp"

struct point {
	GLfloat x;
	GLfloat y;
	GLfloat s;
	GLfloat t;

	point operator=(const point& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->s = other.s;
		this->t = other.t;

		return *this;
	}
};

class Text
{
private:
	GLuint VAO, VBO;

	std::vector<point> vertices;

	std::string text;

	Font* font;

	// Size of the text's bounds in pixels
	glm::vec2 textBounds;

public:
	Text(Font* newFont, std::string newText, float newScale = 1.0f, glm::vec3 newColor = glm::vec3(0));
	~Text();

	static void InitInstancing();

	void SetString(std::string newText);
	const std::string& GetString() const;

	void SetFont(Font* newFont);
	Font* GetFont();

	bool centered;

	glm::vec3 color;
	glm::vec2 position;
	float scale;
	const glm::vec2& GetBounds() const;


	void Render();
};

#endif