#include "MoveCommand.h"  
#include "Timer.h"  
#include "PlayerComponent.h"  

void MoveCommand::Execute()  
{  
   if (m_pGameObject)
   {  
       auto pPlayerComponent = m_pGameObject->GetComponent<dae::PlayerComponent>();
       if (pPlayerComponent)
       {
		   if (pPlayerComponent->GetPlayerState() == dae::PlayerComponent::PlayerState::Moving)
		   {
               glm::vec3 position = m_pGameObject->GetPosition();
               position.x += m_Speed * dae::Timer::GetInstance().GetDeltaTime();
               m_pGameObject->SetLocalPosition(position);
		   } 
       }  
   }  
}
