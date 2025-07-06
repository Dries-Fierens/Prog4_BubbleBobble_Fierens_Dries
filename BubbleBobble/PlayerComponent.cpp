#include "PlayerComponent.h"

dae::PlayerComponent::PlayerComponent(int health, float speed, GameObject* pOwner) : BaseComponent(pOwner), m_health(health), m_speed(speed), m_inputManager(dae::InputManager::GetInstance())
{
}

void dae::PlayerComponent::Update(float delta_time)
{
   m_inputManager.ProcessInput(delta_time);
}

void dae::PlayerComponent::Render() const
{
}
