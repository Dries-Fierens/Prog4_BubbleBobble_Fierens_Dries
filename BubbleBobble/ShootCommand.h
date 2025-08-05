#pragma once
#include "Command.h"
#include "GameObject.h"

class ShootCommand final : public dae::Command
{
public:
	explicit ShootCommand(dae::GameObject* gameObject)
		: m_pGameObject(gameObject) {
	}
	void Execute() override;

private:
	dae::GameObject* m_pGameObject{};

};

