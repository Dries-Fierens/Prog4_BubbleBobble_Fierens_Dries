#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include "InputManager.h"

namespace dae {
	class PlayerComponent final : public BaseComponent
	{
	public:
		void Update(float delta_time) override;
		void Render() const override;

		PlayerComponent(float speed, GameObject* pOwner);
		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

	private:
		InputManager& m_inputManager;
		float m_speed;
	};
}

