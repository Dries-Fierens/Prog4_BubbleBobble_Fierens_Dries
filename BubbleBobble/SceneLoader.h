#pragma once
#include "EventQueue.h"
#include "Singleton.h"

class SceneLoader final : public dae::Singleton<SceneLoader>, public EventListener
{
public:
	enum class GameState
	{
		Menu,
		Singleplayer,
		Coop,
		Versus,
		HighScore
	};

	~SceneLoader() override = default;
	SceneLoader(const SceneLoader& other) = delete;
	SceneLoader operator=(const SceneLoader& rhs) = delete;
	SceneLoader(SceneLoader&& other) = delete;
	SceneLoader operator=(SceneLoader&& rhs) = delete;

	void OnEvent(const Event& e) override;

	void Initialize();
	void SkipLevel();
	void SetGameState(GameState state) { m_GameState = state; }

private:
	friend class Singleton<SceneLoader>;
	SceneLoader() = default;

	GameState m_GameState{ GameState::Menu };
};

