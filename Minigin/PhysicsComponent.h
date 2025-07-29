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

		void Jump(float speed);

	private:
		float m_verticalSpeed{};
		const float m_gravityAcceleration{ 450 };
		const float m_fallSpeed{ 900 };
		CollisionState m_collisionState{};

		void DoGravity();
		void DoCollision();
	};
}

