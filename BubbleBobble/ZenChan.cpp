#include "ZenChan.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "EnemyComponent.h"

std::shared_ptr<dae::GameObject> ZenChan::Create(float x, float y)
{
	auto pZenChan = std::make_shared<dae::GameObject>();
	pZenChan->SetLocalPosition(x, y);

	auto sprite = std::make_shared<dae::SpriteComponent>("../Data/Enemies/ZenChan/Run_Anim.png", pZenChan.get());
	sprite->Animate(2, 2, 4, 0, 3);

	auto collider = std::make_shared<dae::ColliderComponent>(pZenChan.get());
	collider->SetSize(sprite.get()->GetSize());

	auto physics = std::make_shared<dae::PhysicsComponent>(pZenChan.get());
	physics->SetPhysics(true, true, false);

	auto enemyComponent = std::make_shared<dae::EnemyComponent>(pZenChan.get());

	pZenChan->AddComponent(sprite);
	pZenChan->AddComponent(collider);
	pZenChan->AddComponent(physics);
	pZenChan->AddComponent(enemyComponent);

	return pZenChan;
}
