#pragma once

#include "../Model.h"
#include "../Material.h"

class Floor : public Model {
public:
	Floor(glm::vec3 position, glm::vec3 size, float shininess)
		: m_position(position), m_size(size), m_shininess(shininess) {}

	void Init() {
		std::vector<Vertex> vertices = {
			{ glm::vec3(-0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
			{ glm::vec3( 0.5f, 0.0f,  0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 2.0f) },
			{ glm::vec3( 0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(2.0f, 2.0f) },
			{ glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(2.0f, 0.0f) }
		};

		std::vector<unsigned int> indices = {
			0, 1, 3,
			3, 1, 2
		};
		
		Texture ambient("res/textures/planks.png", "material.ambient");
		ambient.Load();
		Texture diffuse("res/textures/planks.png", "material.diffuse");
		diffuse.Load();
		Texture specular("res/textures/planksSpec.png", "material.specular");
		specular.Load();

		m_meshes.push_back(Mesh(vertices, indices, { ambient, diffuse, specular }));
	}

	void Render(Shader shader) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, m_position);
		model = glm::scale(model, m_size);
		model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		shader.SetMat4f("model", model);

		shader.SetFloat("material.shininess", m_shininess);

		for (Mesh mesh : m_meshes) {
			mesh.Render(shader);
		}
	}

public:
	glm::vec3 m_position;
	glm::vec3 m_size;
	float m_shininess;
};