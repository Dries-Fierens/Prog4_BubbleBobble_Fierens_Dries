#pragma once
#include "BaseComponent.h"
#include <glm.hpp>

namespace dae {
	class PlayerComponent final : public BaseComponent
	{
	public:
		enum class PlayerState
		{
			Moving,
			Hit,
			Dead
		};

		PlayerComponent(int health, bool isGreen, GameObject* pOwner);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		bool GetColor() const { return m_isGreen; }
		PlayerState GetPlayerState() const { return m_playerState; }
		void SetPlayerState(PlayerState state) { m_playerState = state; }
		void ResetPosition(const glm::vec2& pos);

	private:
		int m_health;
		bool m_isGreen;
		PlayerState m_playerState;
		glm::vec2 m_lastPosition;
		glm::vec2 m_spawnPosition;

		void Rotate();
	};
}