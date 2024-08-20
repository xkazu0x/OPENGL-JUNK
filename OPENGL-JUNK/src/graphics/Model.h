#pragma once

#include "../Config.h"
#include "Mesh.h"

class Model {
public:
	Model();

	void Init();
	void Render(Shader shader);
	void CleanUp();

public:
	std::vector<Mesh> m_meshes = {};
};
