#include "JumpCommand.h"
#include "PhysicsComponent.h"
#include "PlayerComponent.h"

void JumpCommand::Execute()
{
	if (m_pGameObject)
	{
		auto player = m_pGameObject->GetComponent<dae::PlayerComponent>();
		if (player && player.get()->GetPlayerState() != dae::PlayerComponent::PlayerState::Moving) return;

		auto physics = m_pGameObject->GetComponent<dae::PhysicsComponent>();
		if (physics && physics.get()->GetCollisionState().Bottom)
		{
			physics->Jump(m_Speed);
		}
	}
}
