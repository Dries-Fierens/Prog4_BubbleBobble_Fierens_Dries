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
#include "AudioComponent.h"
#include "Player.h"

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

    //auto baseObject = std::make_shared<dae::GameObject>();
    //baseObject->SetLocalPosition(256, 280);
    //scene.Add(baseObject);

    //auto bubbyObject = std::make_shared<dae::GameObject>(baseObject.get());
    //auto bubbyRender = std::make_shared<dae::RenderComponent>("Player/Bubby/Idle_Anim.png", bubbyObject.get());
    //auto rotator1 = std::make_shared<dae::RotatorComponent>(800.f, 90.f, 10.f, bubbyObject.get());
    //bubbyObject->AddComponent(bubbyRender);
    //bubbyObject->AddComponent(rotator1);
    //scene.Add(bubbyObject);

    //auto baseObject2 = std::make_shared<dae::GameObject>();
    //baseObject2->SetLocalPosition(356, 280);
    //scene.Add(baseObject2);

    //auto bobbyObject = std::make_shared<dae::GameObject>(baseObject2.get());
    //auto bobbyRender = std::make_shared<dae::RenderComponent>("Player/Bobby/Idle_Anim.png", bobbyObject.get());
    //auto rotator2 = std::make_shared<dae::RotatorComponent>(300.f, 90.f, 50.f, bobbyObject.get());
    //bobbyObject->AddComponent(bobbyRender);
    //bobbyObject->AddComponent(rotator2);
    //scene.Add(bobbyObject);

	auto player1 = Player::CreatePlayer(100.f, 300.f, true, true);
    scene.Add(player1);
    auto player2 = Player::CreatePlayer(200.f, 300.f, false, true);
    scene.Add(player2);
}

int main(int, char* []) {
    dae::Minigin engine("../Data/");
    engine.Run(load);

    return 0;
}
