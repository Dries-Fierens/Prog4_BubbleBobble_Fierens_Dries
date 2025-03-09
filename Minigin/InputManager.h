#pragma once
#include "Singleton.h"
#include "Command.h"
#include <SDL.h>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();

		bool ProcessInput(float delta_time);
		Command* handleKeyBoardInput(SDL_Event e);

	private:
		GameActor* m_actor;

		LeftCommand* buttonLeft_;
		RightCommand* buttonRight_;
		UpCommand* buttonUp_;
		DownCommand* buttonDown_;
		//FireCommand* buttonX_;
		//Command* buttonY_;
		//Command* buttonA_;
		//Command* buttonB_;
	};
}
