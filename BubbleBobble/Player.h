#pragma once
#include <string>
#include "Scene.h"
#include <windows.h>

class GameObject;
class Player final
{
public:
	static std::shared_ptr<dae::GameObject> CreatePlayer(float x, float y, bool isGreen, bool coop);
};

