#include "Model.h"

Model::Model() {}

void Model::Init() {}

void Model::Render(Shader shader) {
	for (Mesh mesh : m_meshes) {
		mesh.Render(shader);
	}
}

void Model::CleanUp() {
	for (Mesh mesh : m_meshes) {
		mesh.CleanUp();
	}
}