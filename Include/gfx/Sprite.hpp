#pragma once

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "gfx/Shader.hpp"
#include "gfx/Texture.hpp"

class Sprite
{
public:
	Sprite(Texture* tex, glm::vec2 pos = glm::vec2(0.0f, 0.0f), glm::vec2 siz = glm::vec2(100.0f, 100.0f), glm::vec3 col = glm::vec3(1.0f, 1.0f, 1.0f));
	~Sprite();

	Texture* texture;

	glm::vec2 position;
	glm::vec2 size;
	glm::vec3 color;

	float opacity;

	static void InitInstancing();

	void Render();
};

#endif