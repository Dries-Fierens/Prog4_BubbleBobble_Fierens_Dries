#pragma once
#include "Command.h"

class ShowCollisionsCommand : public dae::Command
{
public:
	ShowCollisionsCommand() {}
	void Execute() override;
};

