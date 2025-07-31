#include "Tile.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

std::shared_ptr<dae::GameObject> Tile::CreateTile(float x, float y, int level, bool isBigTile)
{
	auto pSurface = std::make_shared<dae::GameObject>();
	pSurface->SetLocalPosition(x, y);

	std::shared_ptr<dae::RenderComponent> render;
	if (isBigTile)
		render = std::make_shared<dae::RenderComponent>("../Data/Levels/" + std::to_string(level) + "/big.png", pSurface.get());
	else
		render = std::make_shared<dae::RenderComponent>("../Data/Levels/" + std::to_string(level) + "/small.png", pSurface.get());

	auto collider = std::make_shared<dae::ColliderComponent>(pSurface.get());
	auto physics = std::make_shared<dae::PhysicsComponent>(pSurface.get());
	physics->SetPhysics(false, true, true);

	pSurface->AddComponent(render);
	pSurface->AddComponent(collider);
	pSurface->AddComponent(physics);

	return pSurface;
}