#include "ShootCommand.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "SceneManager.h"

void ShootCommand::Execute()
{
	auto player = m_pGameObject->GetComponent<dae::PlayerComponent>();
	auto sprite = m_pGameObject->GetComponent<dae::SpriteComponent>();

	if (player && sprite)
	{
		if (player->GetPlayerState() == dae::PlayerComponent::PlayerState::Moving)
		{
			//dae::Scene* scene = dae::SceneManager::GetInstance().GetCurrentScene();

			if (player.get()->GetColor()) {
				sprite->SetTexture("../Data/Player/Bubby/Shoot_Anim.png");
				sprite->AnimateOnce(1, 4, 8, 0, 3);
			}
			else {
				sprite->SetTexture("../Data/Player/Bobby/Shoot_Anim.png");
				sprite->AnimateOnce(1, 4, 8, 0, 3);
			}
		}
	}
}