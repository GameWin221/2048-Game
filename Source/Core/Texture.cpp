#include "Core/Gfx/Texture.hpp"

void Texture::Use(unsigned int textureID)
{
	glActiveTexture(GL_TEXTURE0 + textureID);
	glBindTexture(GL_TEXTURE_2D, this->texture);
}

Texture::Texture(std::string name)
{
	stbi_set_flip_vertically_on_load(true);

	this->tiling = glm::vec2(1.0f);

	unsigned char* data = stbi_load(name.c_str(), &this->size.x, &this->size.y, &this->channels, 0);

	if (this->channels == 4)
		this->format = GL_RGBA;
	else if (this->channels == 3)
		this->format = GL_RGB;
	else
		this->format = 0;

	if (data)
	{
		glGenTextures(1, &this->texture);
		glBindTexture(GL_TEXTURE_2D, this->texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, this->format, this->size.x, this->size.y, 0, this->format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture: \"" << name << "\"\n";

	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->texture);
}
