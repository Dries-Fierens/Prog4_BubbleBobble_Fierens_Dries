#include "PlayerComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"

dae::PlayerComponent::PlayerComponent(int health, float speed, GameObject* pOwner) : BaseComponent(pOwner), m_health(health), m_speed(speed), m_isGreen(true), m_playerState(PlayerState::Moving), m_lastPosition(glm::vec2(0,0))
{
}

void dae::PlayerComponent::Update()
{
	switch (m_playerState)	
	{
	case dae::PlayerComponent::PlayerState::Moving:
		Rotate();
		break;
	case dae::PlayerComponent::PlayerState::Hit:
		break;
	case dae::PlayerComponent::PlayerState::Dead:
		break;
	default:
		break;
	}
}

void dae::PlayerComponent::Render() const
{
}

void dae::PlayerComponent::SetColor(bool isGreen)
{
	m_isGreen = isGreen;
}

void dae::PlayerComponent::Rotate()
{
	auto sprite = GetOwner()->GetComponent<dae::SpriteComponent>();
	if (sprite)
	{
		glm::vec2 position = GetOwner()->GetPosition();
		if (m_lastPosition.x < position.x)
		{
			sprite->IsFlipped(false);
		}
		else if (m_lastPosition.x > position.x)
		{
			sprite->IsFlipped(true);
		}
		m_lastPosition = position;
	}
}
