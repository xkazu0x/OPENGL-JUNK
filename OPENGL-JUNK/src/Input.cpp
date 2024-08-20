#include "Input.h"

#include "GLBackend.h"

namespace Input {
	bool m_keyPressed[372];
	bool m_keyDown[372];
	bool m_keyDownLastFrame[372];

	void Update() {
		GLFWwindow* window = GLBackend::GetWindowPointer();
		for (int i = 32; i < 349; i++) {
			m_keyDown[i] = (glfwGetKey(window, i) == GLFW_PRESS);
			m_keyPressed[i] = (m_keyDown[i] && !m_keyDownLastFrame[i]);
			m_keyDownLastFrame[i] = m_keyDown[i];
		}
	}

	bool KeyPressed(unsigned int keycode) {
		return m_keyPressed[keycode];
	}

	bool KeyDown(unsigned int keycode) {
		return m_keyDown[keycode];
	}
}
