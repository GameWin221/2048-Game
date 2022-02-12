#pragma once

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glew.h>
#include <glfw3.h>

#include <stb_image.h>

#include <glm.hpp>

#include <string>
#include <iostream>

class Texture
{
private:
	int channels;

	GLuint texture;

public:
	glm::ivec2 size;
	glm::vec2 tiling;

	GLenum format;

	void Use(unsigned int textureID);

	Texture(std::string name);
	~Texture();
};

#endif