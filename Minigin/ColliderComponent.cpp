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

	const glm::vec2& aPos = this->GetPosition();
	const glm::vec2& aSize = this->GetSize();
	const glm::vec2& bPos = other->GetPosition();
	const glm::vec2& bSize = other->GetSize();

	return (aPos.x < bPos.x + bSize.x &&
		aPos.x + aSize.x > bPos.x &&
		aPos.y < bPos.y + bSize.y &&
		aPos.y + aSize.y > bPos.y);
}

void dae::ColliderComponent::UpdatePosition()
{
	m_position = GetOwner()->GetPosition();
}
