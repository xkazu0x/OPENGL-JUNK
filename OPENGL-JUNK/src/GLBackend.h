#pragma once

#include "Config.h"

namespace GLBackend {
	void Init(int width, int height, std::string title);
	void CreateGLFWWindow(const char* title, bool FULLSCREEN);
	void BeginFrame();
	void EndFrame();
	void SetWindowShouldClose(bool value);
	void CleanUp();
	GLFWwindow* GetWindowPointer();
	int GetWindowWidth();
	int GetWindowHeight();
	bool WindowIsOpen();
	void GetOpenGLVersionInfo();
};
