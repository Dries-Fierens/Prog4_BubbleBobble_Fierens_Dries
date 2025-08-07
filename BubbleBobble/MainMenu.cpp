#include "MainMenu.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"

void MainMenu::Create()
{
	dae::Scene* currentScene = dae::SceneManager::GetInstance().GetCurrentScene();

	if (currentScene)
	{
		currentScene->RemoveAll();
		currentScene->SetName("Main Menu");
	}
	else {
		currentScene = &dae::SceneManager::GetInstance().CreateScene("Main Menu");
	}
	dae::SceneManager::GetInstance().SetCurrentScene(currentScene);

	dae::InputManager::GetInstance().RemoveInputs();
	//dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<StartSingleplayerCommand>(), SDL_SCANCODE_1, dae::InputManager::InputType::OnDown);
}
