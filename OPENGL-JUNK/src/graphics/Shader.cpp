#include "Shader.h"

Shader::Shader(std::string vertexPath, std::string fragmentPath) {
	Load(vertexPath, fragmentPath);
	GetUniformsLocation();
}

Shader::~Shader() {
	Release();
}

void Shader::Load(std::string vertexPath, std::string fragmentPath) {
	std::string vsSource = ReadTextFromFile("res/shaders/" + vertexPath);
	std::string fsSource = ReadTextFromFile("res/shaders/" + fragmentPath);

	const char* vsCode = vsSource.c_str();
	const char* fsCode = fsSource.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vsCode, NULL);
	glCompileShader(vertex);
	CheckErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fsCode, NULL);
	glCompileShader(fragment);
	CheckErrors(fragment, "FRAGMENT");

	int tempID = glCreateProgram();
	glAttachShader(tempID, vertex);
	glAttachShader(tempID, fragment);
	glLinkProgram(tempID);
	if (CheckErrors(tempID, "PROGRAM")) {
		m_uniformsLocations.clear();
		m_id = tempID;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::GetUniformsLocation() {
	glGetProgramiv(m_id, GL_ACTIVE_UNIFORMS, &m_uniform_count);

	if (m_uniform_count != 0) {
		GLint max_name_len = 0;
		GLsizei length = 0;
		GLsizei count = 0;
		GLenum type = GL_NONE;
		glGetProgramiv(m_id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_name_len);

		auto uniform_name = std::make_unique<char[]>(max_name_len);

		for (GLint i = 0; i < m_uniform_count; ++i) {
			glGetActiveUniform(m_id, i, max_name_len, &length, &count, &type, uniform_name.get());

			UniformInfo uniformInfo = {};
			uniformInfo.location = glGetUniformLocation(m_id, uniform_name.get());
			uniformInfo.count = count;

			m_uniformsLocations.emplace(std::make_pair(std::string(uniform_name.get(), length), uniformInfo));
		}
	}
}

void Shader::Bind() {
	glUseProgram(m_id);
}

void Shader::Release() {
	glDeleteProgram(m_id);
}

void Shader::SetInt(const std::string& name, int& value) {
	glProgramUniform1i(m_id, m_uniformsLocations[name].location, value);
}

void Shader::SetFloat(const std::string& name, float& value) {
	glProgramUniform1f(m_id, m_uniformsLocations[name].location, value);
}

void Shader::SetMat4f(const std::string& name, glm::mat4& value) {
	glProgramUniformMatrix4fv(m_id, m_uniformsLocations[name].location, m_uniformsLocations[name].count, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetVec3f(const std::string& name, const glm::vec3& value) {
	glProgramUniform3fv(m_id, m_uniformsLocations[name].location, m_uniformsLocations[name].count, glm::value_ptr(value));
}

int Shader::CheckErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
		}
	}
	return success;
}

std::string Shader::ReadTextFromFile(std::string path) {
	std::ifstream file(path);
	std::string str;
	std::string line;
	while (std::getline(file, line)) {
		str += line + "\n";
	}
	return str;
}