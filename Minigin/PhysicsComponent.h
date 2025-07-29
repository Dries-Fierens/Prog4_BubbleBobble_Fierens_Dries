#pragma once
#include "BaseComponent.h"

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

		void SetPhysics(bool hasGravity, bool hasCollision, bool isStatic);
		void Jump(float speed);

	private:
		float m_verticalSpeed{};
		const float m_gravityAcceleration{ 450 };
		const float m_fallSpeed{ 900 };
		CollisionState m_collisionState{};

		bool m_hasGravity{ false };
		bool m_hasCollision{ true };
		bool m_isStatic{ true };

		void DoGravity();
		void DoCollision();
	};
}

