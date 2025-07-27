#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	if (m_currentScene >= 0)
	{
		m_scenes[m_currentScene]->Update();
	}
}

void dae::SceneManager::Render()
{
	if (m_currentScene >= 0)
	{
		m_scenes[m_currentScene]->Render();
	}
}

void dae::SceneManager::SetCurrentScene(const Scene* pScene)
{
	for (size_t i = 0; i < m_scenes.size(); ++i)
	{
		if (m_scenes[i].get() == pScene) m_currentScene = static_cast<int>(i);
	}
}

dae::Scene* dae::SceneManager::GetCurrentScene() const
{
	if (m_currentScene != -1 && m_scenes.size() != 0) return m_scenes[m_currentScene].get();
	return nullptr;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
