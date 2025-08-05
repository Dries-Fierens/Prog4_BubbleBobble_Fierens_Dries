#include "PlayerComponent.h"

dae::PlayerComponent::PlayerComponent(int health, float speed, GameObject* pOwner) : BaseComponent(pOwner), m_health(health), m_speed(speed), m_isGreen(true)
{
}

void dae::PlayerComponent::Update()
{
}

void dae::PlayerComponent::Render() const
{
}

void dae::PlayerComponent::SetColor(bool isGreen)
{
	m_isGreen = isGreen;
}