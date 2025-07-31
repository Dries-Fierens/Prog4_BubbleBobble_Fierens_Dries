#include "Transform.h"

void dae::Transform::SetPosition(const float x, const float y)
{
	m_position.x = x;
	m_position.y = y;
}

void dae::Transform::SetPosition(const glm::vec2& position)
{
	m_position = position;
}
