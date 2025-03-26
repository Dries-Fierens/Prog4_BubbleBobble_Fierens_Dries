#pragma once
#include "Singleton.h"
#include "Command.h"
#include <SDL.h>

namespace dae
{
	enum class Direction
	{
		Up,
		Down,
		Left,
		Right
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:

		void SetDirection(Direction direction) { m_direction = direction; };

		bool ProcessInput(float delta_time);
		Command* handleKeyBoardInput(SDL_Event e);

	private:
		Direction m_direction;
		Move* buttonMove_;
		//FireCommand* buttonX_;
		//Command* buttonY_;
		//Command* buttonA_;
		//Command* buttonB_;
	};
}
