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

	glm::vec2 position = GetOwner()->GetPosition();
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

		auto otherPhysics = object->GetComponent<PhysicsComponent>();
		auto otherCollider = object->GetComponent<ColliderComponent>();
		if (otherCollider && otherPhysics) 
		{
			if (!otherPhysics.get()->m_hasCollision) continue;

			if (collider->IsOverlapping(otherCollider.get()))
			{
				glm::vec2 position = GetOwner()->GetPosition();
				glm::vec2 otherPosition = object->GetPosition();

				// Handle vertical collisions
				if (position.y + collider->GetSize().y > otherPosition.y)
				{
					position.y = otherPosition.y - collider->GetSize().y;
					GetOwner()->SetLocalPosition(position);
					collider.get()->UpdatePosition();
					m_collisionState.Bottom = true;
					m_verticalSpeed = 0.f;
				}
				else if (position.y < otherPosition.y + otherCollider->GetSize().y)
				{
					//position.y = otherPosition.y + otherCollider->GetSize().y;
					//GetOwner()->SetLocalPosition(position);
					//collider.get()->UpdatePosition();
					m_collisionState.Top = true;
					//m_verticalSpeed = 0.f;
				}

				// Handle horizontal collisions
				else if (position.x < otherPosition.x + otherCollider->GetSize().x)
				{
					position.x = (otherPosition.x + otherCollider->GetSize().x);
					GetOwner()->SetLocalPosition(position);
					collider.get()->UpdatePosition();
					m_collisionState.Right = true;
				}
				else if (position.x > otherPosition.x)
				{
					position.x = otherPosition.x;
					GetOwner()->SetLocalPosition(position);
					collider.get()->UpdatePosition();
					m_collisionState.Left = true;
				}
			}
		}
	}
}
