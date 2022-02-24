#include "gfx/Framebuffer.hpp"

Shader* screenShader = nullptr;

float fbVertices[] = {
	// Positions   // TexCoords
	1.0f,  1.0f,  1.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f,
   -1.0f,  1.0f,  0.0f, 1.0f,


   -1.0f, -1.0f,  0.0f, 0.0f,
   -1.0f,  1.0f,  0.0f, 1.0f,
	1.0f, -1.0f,  1.0f, 0.0f
};

Framebuffer::Framebuffer(glm::uvec2 fbSize, unsigned int MSAALevel)
{
	this->size = fbSize;

	if (screenShader == nullptr)
		screenShader = new Shader("Resources/Shaders/fb_vertex.glsl", "Resources/Shaders/fb_fragment.glsl");

	// VAO / VBO for the screen quad
	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &this->quadVBO);

	glBindVertexArray(this->quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(fbVertices), &fbVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));


	// MSAA Color Texture
	glGenTextures(1, &this->colorTextureMSAA);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, this->colorTextureMSAA);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, MSAALevel, GL_RGB, size.x, size.y, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

	// MSAA Framebuffer
	glGenFramebuffers(1, &this->framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, this->colorTextureMSAA, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Failed to create a framebuffer!\n";


	// Final Color Texture
	glGenTextures(1, &this->screenTexture);
	glBindTexture(GL_TEXTURE_2D, this->screenTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Intermediate Framebuffer
	glGenFramebuffers(1, &this->intermediateFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, this->intermediateFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->screenTexture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Failed to create an intermediate framebuffer!\n";

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &this->framebuffer);
	glDeleteFramebuffers(1, &this->intermediateFBO);

	glDeleteTextures(1, &this->colorTextureMSAA);
	glDeleteTextures(1, &this->screenTexture);
}

// Render Functions
void Framebuffer::Use()
{
	glViewport(0, 0, this->size.x, this->size.y);
	glBindFramebuffer(GL_FRAMEBUFFER, this->framebuffer);
}
void Framebuffer::Clear(glm::vec3 clearColor)
{
	glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Framebuffer::Display(unsigned int textureID)
{
	// GL_READ_FRAMEBUFFER is the framebuffer that will be converted to a GL_DRAW_FRAMEBUFFER (MSAA FBO to FBO)
	glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediateFBO);

	// Converting the multisampled framebuffer to a normal framebuffer ('framebuffer' to 'intermediateFBO')
	int w = this->size.x,
		h = this->size.y;

	glBlitFramebuffer(0, 0, w, h, 0, 0, w, h, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	// Unbinding the GL_FRAMEBUFFER in order to render the screenTexture to the main window
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	screenShader->Use();
	screenShader->SetInt("screenTexture", 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, screenTexture);

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}