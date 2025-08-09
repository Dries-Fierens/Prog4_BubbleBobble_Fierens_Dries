#include "StartSingleplayerCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Level.h"
#include "GameManager.h"
#include "InputManager.h"

void StartSingleplayerCommand::Execute()
{
	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetCurrentScene();

	dae::InputManager::GetInstance().RemoveInputs();
	currentScene->RemoveAll();
	currentScene->SetName("Level 1");
	for (auto& gameObject : Level::Create(1)) currentScene->Add(gameObject);

	GameManager::GetInstance().SetGameState(GameManager::GameState::Singleplayer);
}
