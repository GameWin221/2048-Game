#include "Texture.hpp"

void Texture::Use(unsigned int textureID)
{
	glActiveTexture(GL_TEXTURE0 + textureID);
	glBindTexture(GL_TEXTURE_2D, this->texture);
}

Texture::Texture(std::string name)
{
	this->tiling = glm::vec2(1.0f);

	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(name.c_str(), &this->size.x, &this->size.y, &this->nrChannels, 0);

	if (data)
	{
		glGenTextures(1, &this->texture);
		glBindTexture(GL_TEXTURE_2D, this->texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->size.x, this->size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->texture);
}
