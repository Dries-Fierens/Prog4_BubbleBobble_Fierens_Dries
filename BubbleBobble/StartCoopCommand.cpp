#include "StartCoopCommand.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Level.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Locator.h"

void StartCoopCommand::Execute()
{
	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetCurrentScene();
	
	dae::InputManager::GetInstance().RemoveInputs();
	currentScene->RemoveAll();
	currentScene->SetName("Level 1");
	for (auto& gameObject : Level::Create(1)) currentScene->Add(gameObject);

	GameManager::GetInstance().SetGameState(GameManager::GameState::Coop);

	Locator::GetAudio()->PlayMusic("../Data/MainTheme.mp3", 40, -1);
	Locator::GetAudio()->PauseMusic(false);
}

