#pragma once
#include <memory>
#include "GameObject.h"

class Level final
{
public:
	static std::vector<std::shared_ptr<dae::GameObject>> Create(int levelNumber);
};

