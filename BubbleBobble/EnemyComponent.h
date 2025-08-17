#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae 
{
	enum class EnemyState
	{
		Moving,
		Dead
	};

	class EnemyComponent final : public BaseComponent
	{
	public:
		EnemyComponent(GameObject* pOwner);
		virtual ~EnemyComponent() = default;
		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;

		void Update() override;
		void Render() const override;
		void Rotate();

	private:
		float m_timeSinceChange{};
		int m_direction{}; // 0 = idle, -1 = left, 1 = right
		float m_changeInterval{};
		EnemyState m_enemyState{ EnemyState::Moving };
		glm::vec2 m_lastPosition{ 0.f, 0.f };
	};
}

