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
	int nrChannels;

	GLuint texture;

public:
	glm::ivec2 size;

	void Use(unsigned int textureID);

	Texture(std::string name);
	~Texture();
};

#endif