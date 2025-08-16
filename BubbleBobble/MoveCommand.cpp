#include "MoveCommand.h"  
#include "Timer.h"   
#include "PhysicsComponent.h"

void MoveCommand::Execute()
{
    if (m_pGameObject)
    {
        auto pPhysics = m_pGameObject->GetComponent<dae::PhysicsComponent>();
        if (pPhysics)
        {
            pPhysics->SetHorizontalSpeed(m_Speed);
        }
    }
}

