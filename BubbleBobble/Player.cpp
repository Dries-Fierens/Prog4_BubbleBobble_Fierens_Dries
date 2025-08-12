#include "Player.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Controller.h"
#include "PlayerComponent.h"
#include "MoveCommand.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "PhysicsComponent.h"
#include "JumpCommand.h"
#include "ShootCommand.h"
#include "GameManager.h"

std::shared_ptr<dae::GameObject> Player::Create(float x, float y, bool isGreen)
{
	auto pPlayer = std::make_shared<dae::GameObject>();
	pPlayer->SetLocalPosition(x, y);

	std::shared_ptr<dae::SpriteComponent> sprite;
	if (isGreen)
	{
		sprite = std::make_shared<dae::SpriteComponent>("../Data/Player/Bubby/Idle_Anim.png", pPlayer.get());
		sprite->Animate(1, 2, 8, 0, 1);
	}
	else {
		sprite = std::make_shared<dae::SpriteComponent>("../Data/Player/Bobby/Idle_Anim.png", pPlayer.get());
		sprite->Animate(1, 2, 8, 0, 1);
	}

	auto collider = std::make_shared<dae::ColliderComponent>(pPlayer.get());
	collider->SetSize(sprite.get()->GetSize());
	auto physics = std::make_shared<dae::PhysicsComponent>(pPlayer.get());
	physics->SetPhysics(true, true, false);
	auto playerComponent = std::make_shared<dae::PlayerComponent>(3, 100.f, isGreen, pPlayer.get());

	pPlayer->AddComponent(sprite);
	pPlayer->AddComponent(collider);
	pPlayer->AddComponent(physics);
	pPlayer->AddComponent(playerComponent);

	if (GameManager::GetInstance().GetGameState() == GameManager::GameState::Singleplayer)
	{
		dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MoveCommand>(pPlayer.get(), -200.f), 'a', dae::InputManager::InputType::OnPressed);
		dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MoveCommand>(pPlayer.get(), 200.f), 'd', dae::InputManager::InputType::OnPressed);
		dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<JumpCommand>(pPlayer.get(), -450.f), 'w', dae::InputManager::InputType::OnPressed);
		dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<ShootCommand>(pPlayer.get()), ' ', dae::InputManager::InputType::OnDown);

		dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), -200.f), dae::Controller::ButtonState::Left, 0, dae::InputManager::InputType::OnPressed);
		dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), 200.f), dae::Controller::ButtonState::Right, 0, dae::InputManager::InputType::OnPressed);
		dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<JumpCommand>(pPlayer.get(), -450.f), dae::Controller::ButtonState::A, 0, dae::InputManager::InputType::OnPressed);
		dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<ShootCommand>(pPlayer.get()), dae::Controller::ButtonState::B, 0, dae::InputManager::InputType::OnDown);
	}
	else
	{
		if (isGreen)
		{
			dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MoveCommand>(pPlayer.get(), -200.f), 'a', dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MoveCommand>(pPlayer.get(), 200.f), 'd', dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<JumpCommand>(pPlayer.get(), -450.f), 'w', dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<ShootCommand>(pPlayer.get()), ' ', dae::InputManager::InputType::OnDown);

			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), -200.f), dae::Controller::ButtonState::Left, 1, dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), 200.f), dae::Controller::ButtonState::Right, 1, dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<JumpCommand>(pPlayer.get(), -450.f), dae::Controller::ButtonState::A, 1, dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<ShootCommand>(pPlayer.get()), dae::Controller::ButtonState::B, 1, dae::InputManager::InputType::OnDown);
		}
		else
		{
			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), -200.f), dae::Controller::ButtonState::Left, 0, dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), 200.f), dae::Controller::ButtonState::Right, 0, dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<JumpCommand>(pPlayer.get(), -450.f), dae::Controller::ButtonState::A, 0, dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<ShootCommand>(pPlayer.get()), dae::Controller::ButtonState::B, 0, dae::InputManager::InputType::OnDown);
		}
	}

	return pPlayer;
}