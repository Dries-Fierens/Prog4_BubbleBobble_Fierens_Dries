#pragma once
#include "Command.h"

class SkipLevelCommand : public dae::Command
{
public:
	SkipLevelCommand() = default;
	void Execute() override;
};

