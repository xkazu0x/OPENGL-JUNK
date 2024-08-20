#include "Renderer.h"

#include "Config.h"
#include "GLBackend.h"
#include "Game.h"

#include "graphics/Shader.h"
#include "graphics/Material.h"
#include "graphics/Light.h"
#include "graphics/models/Floor.hpp"

namespace Renderer {
	Shader* m_program = nullptr;
	PointLight m_pointLight = { glm::vec3(0.0f, 0.15f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.0f, 1.0f, 0.4f };
	SpotLight m_spotLight = { Game::GetCameraPosition(), Game::GetCameraTarget(), glm::vec3(1.0f, 1.0f, 1.0f),
		glm::cos(glm::radians(12.0f)), glm::cos(glm::radians(20.0f)), 0.0f, 1.0f, 0.5f};
	Floor m_floor(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(2.0f), 1.5f);

	void Init() {
		m_program = new Shader("default.vert", "default.frag");
		m_floor.Init();
	}

	void RenderFrame() {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 view = Game::GetCameraView();
		glm::mat4 projection = Game::GetCameraProjection();
		glm::vec3 cameraPos = Game::GetCameraPosition();

		m_program->Bind();
		m_program->SetMat4f("view", view);
		m_program->SetMat4f("projection", projection);
		m_program->SetVec3f("viewPos", cameraPos);

		m_pointLight.Render(*m_program);

		m_spotLight.position = Game::GetCameraPosition();
		m_spotLight.direction = Game::GetCameraTarget();
		//m_spotLight.Render(*m_program);

		/*
		for (float x = -1.0f; x < 2.0f; x++) {
			for (float z = -1.0f; z < 2.0f; z++) {
				m_floor.m_position = glm::vec3(x, 0.0f, z);
				m_floor.Render(*m_program);
			}
		}*/

		m_floor.Render(*m_program);
	}

	void Release() {
		m_floor.CleanUp();

		delete m_program;
		m_program = nullptr;
	}
}