#pragma once

#include "../Config.h"
#include "Shader.h"
#include "Texture.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

class Mesh {
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

	void Render(Shader shader);
	void CleanUp();

private:
	void Setup();

public:
	std::vector<Vertex> m_vertices = {};
	std::vector<unsigned int> m_indices = {};
	std::vector<Texture> m_textures = {};

private:
	unsigned int m_vao = 0;
	unsigned int m_vbo = 0;
	unsigned int m_ebo = 0;
};

