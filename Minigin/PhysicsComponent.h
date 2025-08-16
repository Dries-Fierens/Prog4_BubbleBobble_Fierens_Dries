#pragma once
#include "BaseComponent.h"
#include <glm.hpp>

namespace dae 
{
	struct CollisionState
	{
		bool Left{};
		bool Right{};
		bool Top{};
		bool Bottom{};
	};

	class PhysicsComponent final : public dae::BaseComponent
	{
	public:
		PhysicsComponent(GameObject* pOwner);
		~PhysicsComponent() override = default;
		PhysicsComponent(const PhysicsComponent& other) = delete;
		PhysicsComponent operator=(const PhysicsComponent& other) = delete;
		PhysicsComponent(PhysicsComponent&& other) = delete;
		PhysicsComponent operator=(PhysicsComponent&& other) = delete;

		void Update() override;
		void Render() const override {};

		CollisionState GetCollisionState() const { return m_collisionState; }
		void SetPhysics(bool hasGravity, bool hasCollision, bool isStatic);
		void Jump(float speed) { m_verticalSpeed = speed; }
		void SetHorizontalSpeed(float speed) { m_horizontalSpeed = speed; };

	private:
		float m_verticalSpeed{};
		float m_horizontalSpeed{};
		const float m_gravityAcceleration{ 450 };
		const float m_fallSpeed{ 900 };
		CollisionState m_collisionState{};

		bool m_hasGravity{ false };
		bool m_hasCollision{ true };
		bool m_isStatic{ true };

		void DoGravity(glm::vec2& velocity);
		void MoveAndCollide(const glm::vec2& velocity);
	};
}

