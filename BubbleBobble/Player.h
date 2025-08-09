#pragma once
#include <windows.h>
#include "GameObject.h"

class Player final
{
public:
	static std::shared_ptr<dae::GameObject> Create(float x, float y, bool isGreen);
};

