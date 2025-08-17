#include "ShowCollisionsCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "ColliderComponent.h"

void ShowCollisionsCommand::Execute()
{
	auto scene = dae::SceneManager::GetInstance().GetCurrentScene();
	for (auto go : scene->GetGameObjects())
	{
		if (go->HasComponent<dae::ColliderComponent>())
		{
			auto collisionComponent = go->GetComponent<dae::ColliderComponent>();
			collisionComponent->ShowCollisions(!collisionComponent->GetShowCollisions());
		}
	}
}
