#include "EnemyComponent.h"
#include "Timer.h"
#include "PhysicsComponent.h"
#include <cstdlib>
#include <ctime>

namespace dae
{
    EnemyComponent::EnemyComponent(GameObject* pOwner)
		: BaseComponent(pOwner),
		m_timeSinceChange(0.f),
		m_direction(0),
		m_changeInterval(1.f + static_cast<float>(rand()) / RAND_MAX * 2.f) // 1–3 sec
    {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    void EnemyComponent::Update()
    {
        float deltaTime = Timer::GetInstance().GetDeltaTime();
        m_timeSinceChange += deltaTime;

        auto physics = GetOwner()->GetComponent<PhysicsComponent>();
        if (!physics) return;

        const auto collision = physics->GetCollisionState();
        if (collision.Left)
        {
            m_direction = 1;
            m_timeSinceChange = 0.f;
        }
        else if (collision.Right)
        {
            m_direction = -1;
            m_timeSinceChange = 0.f;
        }
        else if (m_timeSinceChange > m_changeInterval)
        {
            m_timeSinceChange = 0.f;
            m_changeInterval = 1.0f + static_cast<float>(rand()) / RAND_MAX * 2.0f;
            m_direction = (rand() % 3) - 1;
        }

        const float speed = 50.0f;
        physics->SetHorizontalSpeed(m_direction * speed);

        // Random jump
        if (rand() % 200 == 0) // .5% chance per frame
        {
            if (physics->GetCollisionState().Bottom)
            {
                physics->Jump(-200.0f);
            }
        }
    }


    void EnemyComponent::Render() const
    {
    }
}
