#pragma once
#include "Scene.h"

class Bubble final
{
public:
	static std::shared_ptr<dae::GameObject> Create(const dae::GameObject* gameObject);
};

