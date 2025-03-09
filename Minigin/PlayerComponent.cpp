#include "PlayerComponent.h"

dae::PlayerComponent::PlayerComponent(float speed, GameObject* pOwner) : BaseComponent(pOwner), m_speed(speed), m_inputManager(dae::InputManager::GetInstance())
{
}

void dae::PlayerComponent::Update(float delta_time)
{
   m_inputManager.ProcessInput(delta_time);
}

void dae::PlayerComponent::Render() const
{
}
