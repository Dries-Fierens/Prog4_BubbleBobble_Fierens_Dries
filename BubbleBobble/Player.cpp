#include "Player.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Controller.h"
#include "PlayerComponent.h"
#include "MoveCommand.h"
#include "RenderComponent.h"

std::shared_ptr<dae::GameObject> Player::CreatePlayer(float x, float y, bool isGreen, bool coop)
{
	auto pPlayer = std::make_shared<dae::GameObject>();
	pPlayer->SetLocalPosition(x, y);

	if (!coop)
	{
		dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MoveCommand>(pPlayer.get(), -200.f), 'a', dae::InputManager::InputType::OnPressed);
		dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MoveCommand>(pPlayer.get(), 200.f), 'd', dae::InputManager::InputType::OnPressed);
		//dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<JumpCommand>(pPlayer.get(), -450.f), 'w', dae::InputManager::InputType::OnPressed);
		//dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<ShootCommand>(pPlayer.get()), ' ', dae::InputManager::InputType::OnDown);

		dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), -200.f), dae::Controller::ButtonState::Left, 0, dae::InputManager::InputType::OnPressed);
		dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), 200.f), dae::Controller::ButtonState::Right, 0, dae::InputManager::InputType::OnPressed);
		//dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<JumpCommand>(pPlayer.get(), -450.f), dae::Controller::ButtonState::A, 0, dae::InputManager::InputType::OnPressed);
		//dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<ShootCommand>(pPlayer.get()), dae::Controller::ButtonState::B, 0, dae::InputManager::InputType::OnDown);
	}
	else
	{
		if (isGreen) 
		{
			dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MoveCommand>(pPlayer.get(), -200.f), 'a', dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MoveCommand>(pPlayer.get(), 200.f), 'd', dae::InputManager::InputType::OnPressed);
			//dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<JumpCommand>(pPlayer.get(), -450.f), 'w', dae::InputManager::InputType::OnPressed);
			//dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<ShootCommand>(pPlayer.get()), ' ', dae::InputManager::InputType::OnDown);

			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), -200.f), dae::Controller::ButtonState::Left, 1, dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), 200.f), dae::Controller::ButtonState::Right, 1, dae::InputManager::InputType::OnPressed);
			//dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<JumpCommand>(pPlayer.get(), -450.f), dae::Controller::ButtonState::A, 1, dae::InputManager::InputType::OnPressed);
			//dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<ShootCommand>(pPlayer.get()), dae::Controller::ButtonState::B, 1, dae::InputManager::InputType::OnDown);
		}
		else 
		{
			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), -200.f), dae::Controller::ButtonState::Left, 0, dae::InputManager::InputType::OnPressed);
			dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<MoveCommand>(pPlayer.get(), 200.f), dae::Controller::ButtonState::Right, 0, dae::InputManager::InputType::OnPressed);
			//dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<JumpCommand>(pPlayer.get(), -450.f), dae::Controller::ButtonState::A, 0, dae::InputManager::InputType::OnPressed);
			//dae::InputManager::GetInstance().AddControllerCommand(std::make_unique<ShootCommand>(pPlayer.get()), dae::Controller::ButtonState::B, 0, dae::InputManager::InputType::OnDown);
		}
	}

	std::shared_ptr<dae::RenderComponent> render;
	if (isGreen)
		render = std::make_shared<dae::RenderComponent>("Player/Bubby/Idle_Anim.png", pPlayer.get());
	else
		render = std::make_shared<dae::RenderComponent>("Player/Bobby/Idle_Anim.png", pPlayer.get());

	auto playerComponent = std::make_shared<dae::PlayerComponent>(3, 100.f, pPlayer.get());

	pPlayer->AddComponent(render);
	pPlayer->AddComponent(playerComponent);

	return pPlayer;
}
