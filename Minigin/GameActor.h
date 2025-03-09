#pragma once
#include <iostream>
#include "BaseComponent.h"

namespace dae
{
	class GameActor
	{
	public:
		void Fire() { std::cout << "Fired" << std::endl; };
		void MoveLeft() { std::cout << "Moving left" << std::endl; };
		void MoveRight() { std::cout << "Moving right" << std::endl; };
		void MoveUp() { std::cout << "Moving up" << std::endl; };
		void MoveDown() { std::cout << "Moving down" << std::endl; };
	};
}


