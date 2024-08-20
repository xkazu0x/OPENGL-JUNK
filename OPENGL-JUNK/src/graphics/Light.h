#pragma once

#include "../Config.h"
#include "Shader.h"

struct PointLight {
	glm::vec3 position;
	glm::vec3 color;

	float ambient;
	float diffuse;
	float specular;

	void Render(Shader shader);
};

struct DirectLight {
	glm::vec3 direction;
	glm::vec3 color;

	float ambient;
	float diffuse;
	float specular;

	void Render(Shader shader);
};

struct SpotLight {
	glm::vec3 position;
	glm::vec3 direction;
	glm::vec3 color;

	float inCutOff;
	float outCutOff;

	float ambient;
	float diffuse;
	float specular;

	void Render(Shader shader);
};