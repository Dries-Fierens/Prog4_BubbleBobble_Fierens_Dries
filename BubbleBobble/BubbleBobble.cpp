#include <SDL.h>

#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"
#include "InputManager.h"
#include "PlayerComponent.h"
#include "AudioComponent.h"
#include "Player.h"
#include "Tile.h"
#include "Level.h"

void load()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    auto go = std::make_shared<dae::GameObject>();
    auto backgroundRender = std::make_shared<dae::RenderComponent>("background.tga", go.get());
    auto audio = std::make_shared<dae::AudioComponent>(go.get());
    go->AddComponent(audio);
    go->AddComponent(backgroundRender);
    scene.Add(go);

    go = std::make_shared<dae::GameObject>();
    auto logoRender = std::make_shared<dae::RenderComponent>("logo.tga", go.get());
    go->AddComponent(logoRender);
    go->SetLocalPosition(216, 180);
    scene.Add(go);

    auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
    auto textObject = std::make_shared<dae::GameObject>();
    auto textComponent = std::make_shared<dae::TextComponent>("Programming 4 Assignment", font, textObject.get());
    textObject->SetLocalPosition(80, 50);
    textObject->AddComponent(textComponent);
    scene.Add(textObject);

    auto fpsTextObject = std::make_shared<dae::GameObject>();
    auto fpsComponent = std::make_shared<dae::FPSComponent>(font, fpsTextObject.get());
    fpsTextObject->SetLocalPosition(10, 10);
    fpsTextObject->AddComponent(fpsComponent);
    scene.Add(fpsTextObject);

    for (auto& gameObject : Level::CreateLevel(1)) scene.Add(gameObject);
}

int main(int, char* []) {
    dae::Minigin engine("../Data/");
    engine.Run(load);

    return 0;
}
