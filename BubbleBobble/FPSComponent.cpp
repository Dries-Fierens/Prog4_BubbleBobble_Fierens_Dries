#include "FPSComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Timer.h"

namespace dae
{
    FPSComponent::FPSComponent(std::shared_ptr<Font> font, GameObject* pOwner) :
        BaseComponent(pOwner),
        m_FPS(0.f),
        m_Timer{},
        m_textComponent(std::make_unique<TextComponent>("0 FPS", font, pOwner))
    {
    }

    void FPSComponent::Update()
    {
        float deltaTime = dae::Timer::GetInstance().GetDeltaTime();
        const float TIME_BETWEEN{ 0.20f };
        m_Timer += deltaTime;
        if (m_Timer < TIME_BETWEEN) return;
        m_Timer -= TIME_BETWEEN;

        m_FPS = (1.0f / deltaTime);
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << m_FPS;
        std::string fps = ss.str() + " FPS";

        m_textComponent->SetText(fps);

        m_textComponent->Update();
    }

    void FPSComponent::Render() const
    {
        m_textComponent->Render();
    }
    void FPSComponent::SetPosition(float x, float y)
    {
        m_position.SetPosition(x, y);
    }
}