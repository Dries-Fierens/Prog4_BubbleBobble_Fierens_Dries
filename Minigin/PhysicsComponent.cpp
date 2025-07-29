#include "PhysicsComponent.h"
#include "Timer.h"
#include "GameObject.h"
#include "ColliderComponent.h"
#include "SceneManager.h"
#include "Scene.h"

dae::PhysicsComponent::PhysicsComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

void dae::PhysicsComponent::Update()
{
	m_collisionState = CollisionState{};

	DoGravity();
	DoCollision();
}

void dae::PhysicsComponent::SetPhysics(bool hasGravity, bool hasCollision, bool isStatic)
{
	m_hasGravity = hasGravity;
	m_hasCollision = hasCollision;
	m_isStatic = isStatic;
}

void dae::PhysicsComponent::Jump(float speed)
{
	m_verticalSpeed = speed;
}

void dae::PhysicsComponent::DoGravity()
{
	if (m_isStatic || !m_hasGravity) return;

	const float deltaTime = Timer::GetInstance().GetDeltaTime();

	m_verticalSpeed += m_gravityAcceleration * deltaTime;
	m_verticalSpeed = std::min(m_fallSpeed, m_verticalSpeed);

	auto collider = GetOwner()->GetComponent<ColliderComponent>();
	if (collider)
	{
		float colliderY = -collider->GetSize().y;
		glm::vec2 worldPosition = GetOwner()->GetPosition();
		if (worldPosition.y > 800)
		{
			GetOwner()->SetLocalPosition(worldPosition.x, colliderY);
		}
		else if (worldPosition.y < colliderY)
		{
			GetOwner()->SetLocalPosition(worldPosition.x, 800);
		}
	}

	glm::vec3 position = GetOwner()->GetPosition();
	position.y += m_verticalSpeed * deltaTime;
	GetOwner()->SetLocalPosition(position);
}

void dae::PhysicsComponent::DoCollision()
{
	if (m_isStatic || !m_hasCollision) return;

	auto collider = GetOwner()->GetComponent<ColliderComponent>();
	if (!collider) return;

	Scene* scene = SceneManager::GetInstance().GetCurrentScene();

	for (auto object : scene->GetGameObjects())
	{
		if (object.get() == GetOwner()) continue;

		auto otherCollider = object->GetComponent<ColliderComponent>();
		if (!otherCollider) continue;

		if (collider->IsOverlapping(otherCollider.get()))
		{
			const glm::vec2& position = collider->GetPosition();
			const glm::vec2& size = collider->GetSize();
			m_collisionState.Left = position.x + size.x <= otherCollider->GetPosition().x;
			m_collisionState.Right = position.x >= otherCollider->GetPosition().x + otherCollider->GetSize().x;
			m_collisionState.Top = position.y + size.y <= otherCollider->GetPosition().y;
			m_collisionState.Bottom = position.y >= otherCollider->GetPosition().y + otherCollider->GetSize().y;
		}
	}
}
