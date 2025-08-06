#include "ColliderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"

dae::ColliderComponent::ColliderComponent(GameObject* pOwner) 
	: BaseComponent(pOwner)
{
}

void dae::ColliderComponent::Update()
{
	UpdatePosition();
}

void dae::ColliderComponent::Render() const
{
	if (!m_showCollisions) return;

	const auto renderer = Renderer::GetInstance().GetSDLRenderer();

	SDL_Rect rect;
	rect.x = static_cast<int>(m_position.x);
	rect.y = static_cast<int>(m_position.y);
	rect.w = static_cast<int>(m_size.x);
	rect.h = static_cast<int>(m_size.y);

	SDL_SetRenderDrawColor(renderer, static_cast<Uint8>(m_color.r), static_cast<Uint8>(m_color.g), static_cast<Uint8>(m_color.b), static_cast<Uint8>(m_color.a));
	SDL_RenderDrawRect(renderer, &rect);
}

bool dae::ColliderComponent::IsOverlapping(ColliderComponent* other)
{
    UpdatePosition();

    const auto otherPosition = other->GetOwner()->GetPosition();
	const auto otherSize = other->GetSize();

    if (m_position.x > otherPosition.x + otherSize.x ||
		m_position.x + m_size.x < otherPosition.x ||
		m_position.y > otherPosition.y + otherSize.y ||
		m_position.y + m_size.y < otherPosition.y)
    {
        return false;
    }
    return true;
}

void dae::ColliderComponent::UpdatePosition()
{
	m_position = GetOwner()->GetPosition();
}
