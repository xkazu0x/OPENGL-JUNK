#include "Game.h"
#include "GLBackend.h"
#include "Input.h"

struct Camera {
	float NEAR_PLANE = 0.1f;
	float FAR_PLANE = 10.0f;
	float FOV = 45.0f;

	glm::vec3 position = glm::vec3(0.0f);
	glm::vec3 target = glm::vec3(0.0f);
	glm::vec3 up = glm::vec3(0.0f);

	glm::mat4 view = glm::mat4(0.0f);
	glm::mat4 projection = glm::mat4(0.0f);
};

namespace Game {
	Camera m_camera;
	float m_camSpeed = 0.0001f;
	float m_rotateSpeed = 0.01f;

	void Init() {
		m_camera.position = glm::vec3(0.0f, 1.0f, 2.0f);
		m_camera.target = glm::vec3(0.0f, 0.0f, -1.0f);
		m_camera.up = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	void Update() {
		if (Input::KeyPressed(GLFW_KEY_ESCAPE)) {
			GLBackend::SetWindowShouldClose(true);
		}

		// TRANSLATE CAMERA
		if (Input::KeyDown(GLFW_KEY_W)) {
			m_camera.position += m_camera.target * m_camSpeed;
		}
		if (Input::KeyDown(GLFW_KEY_S)) {
			m_camera.position -= m_camera.target * m_camSpeed;
		}
		if (Input::KeyDown(GLFW_KEY_A)) {
			m_camera.position += -glm::normalize(glm::cross(m_camera.target, m_camera.up)) * m_camSpeed;
		}
		if (Input::KeyDown(GLFW_KEY_D)) {
			m_camera.position += glm::normalize(glm::cross(m_camera.target, m_camera.up)) * m_camSpeed;
		}

		// ROTATE CAMERA
		if (Input::KeyDown(GLFW_KEY_I)) {
			glm::vec3 newCenter = glm::rotate(m_camera.target, glm::radians(m_rotateSpeed), glm::normalize(glm::cross(m_camera.target, m_camera.up)));
			if (!(glm::angle(newCenter, m_camera.up) <= glm::radians(5.0f) || glm::angle(newCenter, -m_camera.up) <= glm::radians(5.0f))) {
				m_camera.target = newCenter;
			}
		}
		if (Input::KeyDown(GLFW_KEY_K)) {
			glm::vec3 newCenter = glm::rotate(m_camera.target, glm::radians(-m_rotateSpeed), glm::normalize(glm::cross(m_camera.target, m_camera.up)));
			if (!(glm::angle(newCenter, m_camera.up) <= glm::radians(5.0f) || glm::angle(newCenter, -m_camera.up) <= glm::radians(5.0f))) {
				m_camera.target = newCenter;
			}
		}
		if (Input::KeyDown(GLFW_KEY_J)) {
			m_camera.target = glm::rotate(m_camera.target, glm::radians(m_rotateSpeed), m_camera.up);
		}
		if (Input::KeyDown(GLFW_KEY_L)) {
			m_camera.target = glm::rotate(m_camera.target, glm::radians(-m_rotateSpeed), m_camera.up);
		}

		m_camera.view = glm::lookAt(m_camera.position, m_camera.position + m_camera.target, m_camera.up);
		m_camera.projection = glm::perspective(m_camera.FOV, (float)GLBackend::GetWindowWidth() / (float)GLBackend::GetWindowHeight(), m_camera.NEAR_PLANE, m_camera.FAR_PLANE);
	}

	glm::mat4 GetCameraView() {
		return m_camera.view;
	}

	glm::mat4 GetCameraProjection() {
		return m_camera.projection;
	}

	glm::vec3 GetCameraPosition() {
		return m_camera.position;
	}
	
	glm::vec3 GetCameraTarget() {
		return m_camera.target;
	}
}
