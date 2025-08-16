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

void dae::PhysicsComponent::SetPhysics(bool hasGravity, bool hasCollision, bool isStatic)
{
	m_hasGravity = hasGravity;
	m_hasCollision = hasCollision;
	m_isStatic = isStatic;
}

void dae::PhysicsComponent::Update()
{
    m_collisionState = CollisionState{};

    glm::vec2 velocity{ m_horizontalSpeed, m_verticalSpeed };

	DoGravity(velocity);
    MoveAndCollide(velocity);
}

void dae::PhysicsComponent::DoGravity(glm::vec2& velocity)
{
    if (!m_isStatic && m_hasGravity)
    {
        const float deltaTime = Timer::GetInstance().GetDeltaTime();
        m_verticalSpeed += m_gravityAcceleration * deltaTime;
        m_verticalSpeed = std::min(m_fallSpeed, m_verticalSpeed);
        velocity.y = m_verticalSpeed;
    }
}

void dae::PhysicsComponent::MoveAndCollide(const glm::vec2& velocity)
{
    if (m_isStatic || !m_hasCollision) return;

    auto collider = GetOwner()->GetComponent<ColliderComponent>();
    if (!collider) return;

    glm::vec2 position = GetOwner()->GetPosition();
    position += velocity * Timer::GetInstance().GetDeltaTime();
    GetOwner()->SetLocalPosition(position);
    collider->UpdatePosition();

    Scene* scene = SceneManager::GetInstance().GetCurrentScene();

    for (auto object : scene->GetGameObjects())
    {
        if (object.get() == GetOwner()) continue;

        auto otherPhysics = object->GetComponent<PhysicsComponent>();
        auto otherCollider = object->GetComponent<ColliderComponent>();
        if (otherCollider && otherPhysics && otherPhysics->m_hasCollision)
        {
            if (collider->IsOverlapping(otherCollider.get()))
            {
                position -= velocity * Timer::GetInstance().GetDeltaTime();
                GetOwner()->SetLocalPosition(position);
                collider->UpdatePosition();

                if (velocity.x > 0)
                {
                    m_horizontalSpeed = 0.f;
                    m_collisionState.Right = true;
                }
                else if (velocity.x < 0)
                {
                    m_horizontalSpeed = 0.f;
                    m_collisionState.Left = true;
                }

                if (velocity.y > 0)
                {
                    m_verticalSpeed = 0.f;
                    m_collisionState.Bottom = true;
                }
                else if (velocity.y < 0)
                {
                    m_verticalSpeed = 0.f;
                    m_collisionState.Top = true;
                }
            }
        }
    }
}


