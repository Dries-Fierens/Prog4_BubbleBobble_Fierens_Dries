#include "Maita.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "EnemyComponent.h"

std::shared_ptr<dae::GameObject> Maita::Create(float x, float y)
{
    auto pMaita = std::make_shared<dae::GameObject>();
    pMaita->SetLocalPosition(x, y);

	auto sprite = std::make_shared<dae::SpriteComponent>("../Data/Enemies/Maita/Run_Anim.png", pMaita.get());
	sprite->Animate(2, 2, 4, 0, 3);

	auto collider = std::make_shared<dae::ColliderComponent>(pMaita.get());
	collider->SetSize(sprite.get()->GetSize());

	auto physics = std::make_shared<dae::PhysicsComponent>(pMaita.get());
	physics->SetPhysics(true, true, false);

	auto enemyComponent = std::make_shared<dae::EnemyComponent>(pMaita.get());

	pMaita->AddComponent(sprite);
	pMaita->AddComponent(collider);
	pMaita->AddComponent(physics);
	pMaita->AddComponent(enemyComponent);

    return pMaita;
}
