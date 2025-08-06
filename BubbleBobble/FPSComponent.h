#pragma once
#include "BaseComponent.h"
#include <memory>
#include <SDL_ttf.h>
#include "Transform.h"
#include "TextComponent.h"

namespace dae
{
    class Font;
    class Texture2D;
    class FPSComponent final : public BaseComponent
    {
    public:
        FPSComponent(std::shared_ptr<Font> font, GameObject* pOwner);
        virtual ~FPSComponent() = default;
        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;

        void Update() override;
        void Render() const override;
        void SetPosition(float x, float y);

    private:
        Transform m_position{};
        float m_FPS;
        float m_Timer;
        std::unique_ptr<TextComponent> m_textComponent;
    };
}
