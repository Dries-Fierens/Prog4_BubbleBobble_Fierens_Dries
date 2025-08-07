#include "SceneLoader.h"
#include "MainMenu.h"

void SceneLoader::OnEvent(const Event& e)
{
}

void SceneLoader::Initialize()
{
	MainMenu::Create();

	dae::EventQueue::GetInstance().AddListener(this);
}

void SceneLoader::SkipLevel()
{
}
