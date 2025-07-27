#pragma once
#include "Command.h"
#include "GameObject.h"

class MoveCommand : public dae::Command
{
public:
	MoveCommand(dae::GameObject* pGameObject, float speed)
		: m_pGameObject(pGameObject), m_Speed(speed) {}
	void Execute() override;

private:
	dae::GameObject* m_pGameObject;
	float m_Speed;
};

