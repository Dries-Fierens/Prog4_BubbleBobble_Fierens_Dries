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
#include "Transform.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"
#include "InputManager.h"
#include "PlayerComponent.h"

void load()
{
    auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

    auto go = std::make_shared<dae::GameObject>();
    auto backgroundRender = std::make_shared<dae::RenderComponent>("background.tga", go.get());
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

    auto baseObject = std::make_shared<dae::GameObject>();
    baseObject->SetLocalPosition(256, 280);
    scene.Add(baseObject);

    auto shipObject1 = std::make_shared<dae::GameObject>(baseObject.get());
    auto shipRender1 = std::make_shared<dae::RenderComponent>("ship.png", shipObject1.get());
    auto player1 = std::make_shared<dae::PlayerComponent>(3, 100.f, shipObject1.get());
    auto rotator1 = std::make_shared<dae::RotatorComponent>(800.f, 90.f, 10.f, shipObject1.get());
    shipObject1->AddComponent(shipRender1);
    shipObject1->AddComponent(rotator1);
    scene.Add(shipObject1);

    auto shipObject2 = std::make_shared<dae::GameObject>(shipObject1.get());
    auto shipRender2 = std::make_shared<dae::RenderComponent>("ship.png", shipObject2.get());
    auto rotator2 = std::make_shared<dae::RotatorComponent>(300.f, 90.f, 50.f, shipObject2.get());
    shipObject2->AddComponent(shipRender2);
    shipObject2->AddComponent(rotator2);
    scene.Add(shipObject2);
}

int main(int, char* []) {
    dae::Minigin engine("../Data/");
    engine.Run(load);

    return 0;
}
