#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include "InputManager.h"

namespace dae {
	class PlayerComponent final : public BaseComponent
	{
	public:
		enum class PlayerState
		{
			Idle,
			Moving,
			Jumping,
			Falling,
			Dead
		};

		PlayerComponent(int health, float speed, GameObject* pOwner);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		void SetColor(bool isGreen);
		PlayerState GetPlayerState() const { return m_playerState; }
		void SetPlayerState(PlayerState state) { m_playerState = state; }

	private:
		float m_speed;
		int m_health;
		bool m_isGreen;
		PlayerState m_playerState{ PlayerState::Moving };
	};
}

