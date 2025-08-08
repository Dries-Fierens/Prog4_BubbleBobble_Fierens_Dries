#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, GameObject* pOwner) : BaseComponent(pOwner), 
m_needsUpdate(true), 
m_text(text), 
m_font(std::move(font)),
m_renderComponent(std::make_unique<RenderComponent>(static_cast<std::shared_ptr<Texture2D>>(nullptr), pOwner))
{ }

void dae::TextComponent::Update()
{
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 };
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_renderComponent->SetTexture(std::make_shared<Texture2D>(texture));
		m_needsUpdate = false;
	}
}

void dae::TextComponent::Render() const
{
	m_renderComponent->Render();
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void dae::TextComponent::SetPosition(const float x, const float y)
{
	m_transform.SetPosition(x, y);
}

glm::vec2 dae::TextComponent::GetSize() const
{
	return m_renderComponent.get()->GetSize();
}
