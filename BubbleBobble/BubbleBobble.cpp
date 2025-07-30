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
#include "Tile.h"

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

    // Players
    auto player1 = Player::CreatePlayer(92.f, 620.f, true, true);
    scene.Add(player1);
    auto player2 = Player::CreatePlayer(676.f, 620.f, false, true);
    scene.Add(player2);

    // Big tiles left
    scene.Add(Tile::CreateTile(0.f, 672.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 624.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 576.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 528.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 480.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 432.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 384.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 336.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 288.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 240.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 192.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 144.f, 1, true));
    scene.Add(Tile::CreateTile(0.f, 96.f, 1, true));

    // Big tiles right
    scene.Add(Tile::CreateTile(720.f, 672.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 624.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 576.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 528.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 480.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 432.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 384.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 336.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 288.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 240.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 192.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 144.f, 1, true));
    scene.Add(Tile::CreateTile(720.f, 96.f, 1, true));

    // Helper to add a regular tile
    auto AddTile = [&](float x, float y) {
        scene.Add(Tile::CreateTile(x, y, 1, false));
        };

    // Bottom floor tiles
    std::vector<float> x_vals = { 48, 72, 96, 120, 144, 168, 192, 216, 240, 264, 288, 312,
                                 336, 360, 384, 408, 432, 456, 480, 504, 528, 552, 576,
                                 600, 624, 648, 672, 696 };
    for (auto x : x_vals) AddTile(x, 672.f);

    // Floors 1–3
    std::vector<float> y_floors = { 552.f, 432.f, 312.f };
    std::vector<std::vector<float>> x_floors = {
        {48, 72, 168, 192, 216, 240, 264, 288, 312, 336, 360, 384, 408, 432, 456, 480, 504, 528, 552, 576, 672, 696},
        {48, 72, 168, 192, 216, 240, 264, 288, 312, 336, 360, 384, 408, 432, 456, 480, 504, 528, 552, 576, 672, 696},
        {48, 72, 168, 192, 216, 240, 264, 288, 312, 336, 360, 384, 408, 432, 456, 480, 504, 528, 552, 576, 672, 696}
    };

    for (size_t i = 0; i < y_floors.size(); ++i) {
        for (auto x : x_floors[i]) AddTile(x, y_floors[i]);
    }

}

int main(int, char* []) {
    dae::Minigin engine("../Data/");
    engine.Run(load);

    return 0;
}
