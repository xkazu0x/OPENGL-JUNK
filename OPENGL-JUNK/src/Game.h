#pragma once

#include "Config.h"

namespace Game {
	void Init();
	void Update();
	glm::mat4 GetCameraView();
	glm::mat4 GetCameraProjection();
	glm::vec3 GetCameraPosition();
	glm::vec3 GetCameraTarget();
};
