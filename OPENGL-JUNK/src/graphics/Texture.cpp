#include "Texture.h"
#include "stb_image.h"

int Texture::m_currentId = 0;

Texture::Texture(const char* path, const char* name)
	: m_path(path), m_name(name), m_id(m_currentId++) {
	Generate();
}

void Texture::Generate() {
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::Load(bool flip) {
	stbi_set_flip_vertically_on_load(flip);
	unsigned char* data = stbi_load(m_path, &m_width, &m_height, &m_channels, 0);
	if (data) {
		GLenum format = GL_NONE;
		if (m_channels == 1) format = GL_RED;
		else if (m_channels == 3) format = GL_RGB;
		else if (m_channels == 4) format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, m_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else {
		std::cout << "Failed to load Image::" << m_path << "\n";
	}
	stbi_image_free(data);
}

void Texture::Bind() {
	glBindTexture(GL_TEXTURE_2D, m_id);
}