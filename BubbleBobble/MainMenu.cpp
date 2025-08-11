#include "MainMenu.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "StartSingleplayerCommand.h"
#include "StartCoopCommand.h"

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
	dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<StartSingleplayerCommand>(), '1', dae::InputManager::InputType::OnDown);
	dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<StartCoopCommand>(), '2', dae::InputManager::InputType::OnDown);
	//dae::InputManager::GetInstance().AddKeyboardCommand(std::make_unique<StartVersusCommand>(), '3', dae::InputManager::InputType::OnDown);

   
	auto go = std::make_shared<dae::GameObject>();
    auto logoDAE = std::make_shared<dae::RenderComponent>("logo.tga", go.get());
    go->AddComponent(logoDAE);
    go->SetLocalPosition(10, 740);
    currentScene->Add(go);

	go = std::make_shared<dae::GameObject>();
	auto logoBubbleBobble = std::make_shared<dae::RenderComponent>("../Data/HUD/logo.png", go.get());
	go->AddComponent(logoBubbleBobble);
	go->SetLocalPosition(800.f / 2 - logoBubbleBobble.get()->GetSize().x / 2, 50);
	currentScene->Add(go);

	auto fontPang = dae::ResourceManager::GetInstance().LoadFont("../Data/Fonts/Pang.ttf", 20);
    auto fpsTextObject = std::make_shared<dae::GameObject>();
    auto fpsComponent = std::make_shared<dae::FPSComponent>(fontPang, fpsTextObject.get());
    fpsTextObject->SetLocalPosition(10, 10);
    fpsTextObject->AddComponent(fpsComponent);
    currentScene->Add(fpsTextObject);

	auto fontNES = dae::ResourceManager::GetInstance().LoadFont("../Data/Fonts/Pixel_NES.otf", 32);

	auto singleplayer = std::make_shared<dae::GameObject>();
	auto singleplayerText = std::make_shared<dae::TextComponent>("PRESS 1 FOR SINGLEPLAYER", fontNES, singleplayer.get());
	singleplayerText->Update(); // Texture isn't initialized until Update is called
	singleplayer->SetLocalPosition(800.f / 2 - singleplayerText.get()->GetSize().x / 2, 500);
	singleplayer->AddComponent(singleplayerText);
	currentScene->Add(singleplayer);

	auto coop = std::make_shared<dae::GameObject>();
	auto coopText = std::make_shared<dae::TextComponent>("PRESS 2 FOR CO-OP", fontNES, coop.get());
	coopText->Update(); // Texture isn't initialized until Update is called
	coop->SetLocalPosition(800.f / 2 - coopText.get()->GetSize().x / 2, 570);
	coop->AddComponent(coopText);
	currentScene->Add(coop);

	auto versus = std::make_shared<dae::GameObject>();
	auto versusText = std::make_shared<dae::TextComponent>("PRESS 3 FOR VERSUS", fontNES, versus.get());
	versusText->Update(); // Texture isn't initialized until Update is called
	versus->SetLocalPosition(800.f / 2 - versusText.get()->GetSize().x / 2, 640);
	versus->AddComponent(versusText);
	currentScene->Add(versus);
}
