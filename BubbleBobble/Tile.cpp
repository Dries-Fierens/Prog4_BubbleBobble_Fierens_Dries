#include "Tile.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

std::shared_ptr<dae::GameObject> Tile::CreateTile(float x, float y, int level, bool isBigTile)
{
	auto pSurface = std::make_shared<dae::GameObject>();
	pSurface->SetLocalPosition(x, y);

	std::string bigTile = "Levels/" + std::to_string(level) + "/big.png";
	std::string smallTile = "Levels/" + std::to_string(level) + "/small.png";
	std::shared_ptr<dae::RenderComponent> render;
	if (isBigTile)
		render = std::make_shared<dae::RenderComponent>(bigTile, pSurface.get());
	else
		render = std::make_shared<dae::RenderComponent>(smallTile, pSurface.get());

	auto collider = std::make_shared<dae::ColliderComponent>(pSurface.get());
	auto physics = std::make_shared<dae::PhysicsComponent>(pSurface.get());
	physics->SetPhysics(false, true, true);

	pSurface->AddComponent(render);
	pSurface->AddComponent(collider);
	pSurface->AddComponent(physics);

	return pSurface;
}