#include "DeathCommand.h"
#include "PlayerComponent.h"

void DeathCommand::Execute()
{
	if (m_pGameObject)
	{
		auto playerComponent = m_pGameObject->GetComponent<dae::PlayerComponent>();
		if (playerComponent)
		{
			playerComponent->SetPlayerState(dae::PlayerComponent::PlayerState::Dead);
		}
	}
}
