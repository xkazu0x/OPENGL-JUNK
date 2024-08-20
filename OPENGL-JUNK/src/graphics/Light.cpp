#include "Light.h"

void PointLight::Render(Shader shader) {
	std::string name = "pointLight";

	shader.SetVec3f(name + ".position", position);
	shader.SetVec3f(name + ".color", color);

	shader.SetFloat(name + ".ambient", ambient);
	shader.SetFloat(name + ".diffuse", diffuse);
	shader.SetFloat(name + ".specular", specular);
}

void DirectLight::Render(Shader shader) {
	std::string name = "directLight";

	shader.SetVec3f(name + ".direction", direction);
	shader.SetVec3f(name + ".color", color);

	shader.SetFloat(name + ".ambient", ambient);
	shader.SetFloat(name + ".diffuse", diffuse);
	shader.SetFloat(name + ".specular", specular);
}

void SpotLight::Render(Shader shader) {
	std::string name = "spotLight";

	shader.SetVec3f(name + ".position", position);
	shader.SetVec3f(name + ".direction", direction);
	shader.SetVec3f(name + ".color", color);

	shader.SetFloat(name + ".inCutOff", inCutOff);
	shader.SetFloat(name + ".outCutOff", outCutOff);

	shader.SetFloat(name + ".ambient", ambient);
	shader.SetFloat(name + ".diffuse", diffuse);
	shader.SetFloat(name + ".specular", specular);
}
