#pragma once

#include "../Config.h"

struct UniformInfo {
	GLint location;
	GLsizei count;
};

class Shader {
public:
	Shader(std::string vertexPath, std::string fragmentPath);
	~Shader();

	void Bind();
	void Release();

	void SetInt(const std::string& name, int& value);
	void SetFloat(const std::string& name, float& value);
	void SetMat4f(const std::string& name, glm::mat4& value);
	void SetVec3f(const std::string& name, const glm::vec3& value);

	int CheckErrors(unsigned int shader, std::string type);
	std::string ReadTextFromFile(std::string path);

private:
	void Load(std::string vertexPath, std::string fragmentPath);
	void GetUniformsLocation();

private:
	int m_id = -1;
	GLint m_uniform_count = 0;
	std::unordered_map<std::string, UniformInfo> m_uniformsLocations;
};
