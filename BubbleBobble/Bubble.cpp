#include "Bubble.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"

std::shared_ptr<dae::GameObject> Bubble::Create(const dae::GameObject* /*gameObject*/)
{
	//auto player = gameObject->GetComponent<dae::PlayerComponent>();

	//if (player) {
	//	auto bubble = std::make_shared<dae::GameObject>();
	//	bubble->SetLocalPosition(gameObject->GetPosition().x, gameObject->GetPosition().y);
	//	
	//	std::shared_ptr<dae::SpriteComponent> sprite;
	//	if (player.get()->GetColor()) {
	//		sprite = std::make_shared<dae::SpriteComponent>("../Data/Player/Bubby/Bubble_Anim.png", bubble.get());
	//		sprite->Animate(1, 3, 12, 0, 2);
	//	}
	//	else {
	//		sprite = std::make_shared<dae::SpriteComponent>("../Data/Player/Bobby/Bubble_Anim.png", bubble.get());
	//		sprite->Animate(1, 3, 12, 0, 2);
	//	}

	//	auto collider = std::make_shared<dae::ColliderComponent>(player.get());
	//	collider->SetSize(sprite.get()->GetSize());

	//	bubble->AddComponent(sprite);
	//	bubble->AddComponent(collider);

	//	return bubble;
	//}

	//// If the player component is not found, return nullptr
    return nullptr;
}
