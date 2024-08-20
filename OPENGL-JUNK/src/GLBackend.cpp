#include "GLBackend.h"

namespace GLBackend {
	GLFWwindow* m_window;
	GLFWmonitor* m_monitor = nullptr;
	const GLFWvidmode* m_mode = nullptr;
	int m_screenWidth = 0;
	int m_screenHeight = 0;
	int m_windowWidth = 0;
	int m_windowHeight = 0;
	int m_currentWidth = 0;
	int m_currentHeight = 0;
	bool m_full_screen = true;

	void Init(int width, int height, std::string title) {
		glfwInit();
		glfwSetErrorCallback([](int error, const char* description) { std::cout << "GLFW Error (" << std::to_string(error) << "): " << description << "\n"; });

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		m_monitor = glfwGetPrimaryMonitor();
		m_mode = glfwGetVideoMode(m_monitor);
		
		glfwWindowHint(GLFW_RED_BITS, m_mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, m_mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, m_mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, m_mode->refreshRate);

		m_screenWidth = m_mode->width;
		m_screenHeight = m_mode->height;
		m_windowWidth = width;
		m_windowHeight = height;

		CreateGLFWWindow(title.c_str(), m_full_screen);
		
		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD\n";
			glfwTerminate();
			return;
		}

		GetOpenGLVersionInfo();

		glViewport(0, 0, m_currentWidth, m_currentHeight);

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
	}

	void CreateGLFWWindow(const char* title, bool FULLSCREEN) {
		if (FULLSCREEN) {
			m_currentWidth = m_screenWidth;
			m_currentHeight = m_screenHeight;
			m_window = glfwCreateWindow(m_currentWidth, m_currentHeight, title, m_monitor, nullptr);
			if (m_window == nullptr) {
				std::cout << "Failed to create GLFW window\n";
				glfwTerminate();
				return;
			}
		}
		else {
			m_currentWidth = m_windowWidth;
			m_currentHeight = m_windowHeight;
			m_window = glfwCreateWindow(m_currentWidth, m_currentHeight, title, nullptr, nullptr);
			if (m_window == nullptr) {
				std::cout << "Failed to create GLFW window\n";
				glfwTerminate();
				return;
			}
			glfwSetWindowPos(m_window, (m_screenWidth - m_currentWidth) / 2, (m_screenHeight - m_currentHeight) / 2);
		}
	}

	void BeginFrame() {
		glfwPollEvents();
	}

	void EndFrame() {
		glfwSwapBuffers(m_window);
	}

	void SetWindowShouldClose(bool value) {
		glfwSetWindowShouldClose(m_window, value);
	}

	void CleanUp() {
		glfwTerminate();
	}

	GLFWwindow* GetWindowPointer() {
		return m_window;
	}

	int GetWindowWidth() {
		return m_currentWidth;
	}

	int GetWindowHeight() {
		return m_currentHeight;
	}

	bool WindowIsOpen() {
		return !glfwWindowShouldClose(m_window);
	}

	void GetOpenGLVersionInfo() {
		std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
		std::cout << "Version: " << glGetString(GL_VERSION) << "\n";
		std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
	}
}
