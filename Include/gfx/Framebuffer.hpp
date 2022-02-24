#pragma once

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "gfx/Shader.hpp"

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>

class Framebuffer
{
public:
	Framebuffer(glm::uvec2 fbSize, unsigned int MSAALevel);
	~Framebuffer();

	void Use();
	void Clear(glm::vec3 clearColor = glm::vec3(0, 0, 0));
	void Display(unsigned int textureID = 0);

	glm::uvec2 size;

private:
	// Vertex Array, Vertex Buffer
	GLuint quadVAO, quadVBO;
	
	// Multisampled Objects
	GLuint framebuffer;
	GLuint colorTextureMSAA;

	// "Converter" for converting a multisampled texture to a non-multisampled one
	GLuint intermediateFBO;

	// Final Texture
	GLuint screenTexture;
};

#endif