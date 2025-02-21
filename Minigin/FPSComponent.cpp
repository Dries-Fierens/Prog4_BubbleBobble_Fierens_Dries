#include "FPSComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <sstream>
#include <iomanip>

namespace dae
{
	FPSComponent::FPSComponent(std::shared_ptr<Font> font, GameObject* pOwner) : 
        BaseComponent(pOwner), 
        m_FPS(0.f), 
        m_textComponent(std::make_unique<TextComponent>("0 FPS", font, pOwner))
    {
    }

    void FPSComponent::Update(float deltaTime)
    {
        m_FPS = (1.0f / deltaTime);
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << m_FPS;
        std::string fps = ss.str() + " FPS";

		m_textComponent->SetText(fps);

		m_textComponent->Update(deltaTime);
    }

    void FPSComponent::Render() const
    {
        m_textComponent->Render();
    }

    void FPSComponent::SetPosition(const float x, const float y)
    {
        m_transform.SetPosition(x, y, 0.0f);
    }
}
