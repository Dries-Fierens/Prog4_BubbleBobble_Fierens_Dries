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
#include "SceneLoader.h"

void load()
{
	SceneLoader::GetInstance().Initialize();
}

int main(int, char* []) {
    dae::Minigin engine("../Data/");
    engine.Run(load);

    return 0;
}
