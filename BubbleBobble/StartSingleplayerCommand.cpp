#include "StartSingleplayerCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Level.h"
#include "SceneLoader.h"
#include "InputManager.h"

void StartSingleplayerCommand::Execute()
{
	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetCurrentScene();

	dae::InputManager::GetInstance().RemoveInputs();
	currentScene->RemoveAll();
	currentScene->SetName("Level 1");
	for (auto& gameObject : Level::CreateLevel(1, false)) currentScene->Add(gameObject);

	SceneLoader::GetInstance().SetGameState(SceneLoader::GameState::Singleplayer);
}
