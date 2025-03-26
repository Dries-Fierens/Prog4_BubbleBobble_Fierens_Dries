#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

bool dae::InputManager::ProcessInput(float /*delta_time*/)
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			dae::Command* command = handleKeyBoardInput(e);
			if(command) command->Execute();
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
	if (e.key.keysym.sym == SDLK_w) 
	{ 
		SetDirection(Direction::Up);
		return buttonMove_;
	}
	if (e.key.keysym.sym == SDLK_a) 
	{ 
		SetDirection(Direction::Left);
		return buttonMove_;
	}
	if (e.key.keysym.sym == SDLK_s) 
	{ 
		SetDirection(Direction::Down);
		return buttonMove_; 
	}
	if (e.key.keysym.sym == SDLK_d)
	{
		SetDirection(Direction::Right);
		return buttonMove_;
	}
	//if(e.key.keysym.sym == SDLK_c) return buttonRight_;
	//if(e.key.keysym.sym == SDLK_z && e.key.keysym.sym == SDLK_x) return buttonRight_;

	return nullptr;
}
