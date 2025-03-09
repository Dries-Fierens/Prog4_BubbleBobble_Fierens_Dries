#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

dae::InputManager::InputManager()
{
	m_actor = new GameActor();
	buttonDown_ = new DownCommand();
	buttonLeft_ = new LeftCommand();
	buttonRight_ = new RightCommand();
	buttonUp_ = new UpCommand();
}

dae::InputManager::~InputManager()
{
	delete m_actor;
	delete buttonDown_;
	delete buttonLeft_;
	delete buttonRight_;
	delete buttonUp_;
}

bool dae::InputManager::ProcessInput(float /*delta_time*/)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			dae::Command* command = handleKeyBoardInput(e);
			if(command) command->Execute(*m_actor);
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			// Handle mouse button down events
		}

		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	return true;
}

dae::Command* dae::InputManager::handleKeyBoardInput(SDL_Event e)
{
	if(e.key.keysym.sym == SDLK_w) return buttonUp_;
	if(e.key.keysym.sym == SDLK_a) return buttonLeft_;
	if(e.key.keysym.sym == SDLK_s) return buttonDown_;
	if(e.key.keysym.sym == SDLK_d) return buttonRight_;

	return nullptr;
}
