#include "Config.h"
#include "GLBackend.h"
#include "Input.h"
#include "Game.h"
#include "Renderer.h"

int main() {
	GLBackend::Init(1920/2, 1080/2, "UNTIL I FUCKING DIE");

	Game::Init();
	Renderer::Init();

	while (GLBackend::WindowIsOpen()) {
		GLBackend::BeginFrame();

		Input::Update();
		Game::Update();
		Renderer::RenderFrame();

		GLBackend::EndFrame();
	}

	Renderer::Release();
	GLBackend::CleanUp();

	return 0;
}