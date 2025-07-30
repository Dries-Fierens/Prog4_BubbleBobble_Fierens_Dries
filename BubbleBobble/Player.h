#pragma once
#include <windows.h>
#include "GameObject.h"

class Player final
{
public:
	static std::shared_ptr<dae::GameObject> CreatePlayer(float x, float y, bool isGreen, bool coop);
};

