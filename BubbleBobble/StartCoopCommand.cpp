#include "StartCoopCommand.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Level.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Locator.h"
#include "MuteCommand.h"

void StartCoopCommand::Execute()
{
	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetCurrentScene();
	
	dae::InputManager::GetInstance().RemoveInputs();
	dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<MuteCommand>(), SDLK_F2, dae::InputManager::InputType::OnDown);

	currentScene->RemoveAll();
	currentScene->SetName("Level 1");
	GameManager::GetInstance().SetGameState(GameManager::GameState::Coop);
	for (auto& gameObject : Level::Create(1)) currentScene->Add(gameObject);

	Locator::GetAudio()->PlayMusic("../Data/MainTheme.mp3", 40, -1);
	Locator::GetAudio()->PauseMusic(false);
}

