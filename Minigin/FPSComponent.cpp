#include "FPSComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>

namespace dae
{
    FPSComponent::FPSComponent(std::shared_ptr<Font> font)
        : m_font(std::move(font)), m_textTexture(nullptr), m_FPS(0.f)
    {
    }

    void FPSComponent::Update(float deltaTime)
    {
        m_FPS = ((int)((1.0f / deltaTime) * 100.f) / 100.f);
        std::string fps = std::to_string(m_FPS) + " FPS";

        const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
        const auto surf = TTF_RenderText_Blended(m_font->GetFont(), fps.c_str(), color);
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
        m_textTexture = std::make_shared<Texture2D>(texture);
    }

    void FPSComponent::Render() const
    {
        if (m_textTexture != nullptr)
        {
            const auto& pos = m_transform.GetPosition();
            Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
        }
    }

    void FPSComponent::SetPosition(const float x, const float y)
    {
        m_transform.SetPosition(x, y, 0.0f);
    }
}
