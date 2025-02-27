#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include "Transform.h"
#include "RenderComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:
		void Update(float delta_time) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		TextComponent(const std::string& text, std::shared_ptr<Font> font, GameObject* pOwner);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_needsUpdate;
		std::string m_text;
		Transform m_transform{};
		std::shared_ptr<Font> m_font;
		//std::shared_ptr<Texture2D> m_texture;
		std::unique_ptr<RenderComponent> m_renderComponent;
	};
}
