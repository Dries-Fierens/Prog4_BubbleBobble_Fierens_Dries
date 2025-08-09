#pragma once
#include <windows.h>
#include "GameObject.h"

class Tile final
{
public:
	static std::shared_ptr<dae::GameObject> Create(float x, float y, int level, bool isBigTile);
};

