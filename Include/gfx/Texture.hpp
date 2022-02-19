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
	glm::ivec2 size;

	GLint channels;
	GLuint texture;
	GLenum format;

public:
	Texture(std::string name);
	~Texture();

	void Use(unsigned int textureID);

	const glm::ivec2& GetSize()      const { return this->size;     };
	const GLenum&	  GetFormat()    const { return this->format;   };
	const GLint&	  GetChannels()  const { return this->channels; };
	const GLuint&	  GetTextureID() const { return this->texture;  };

	glm::vec2 tiling;
};

#endif