#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>
#include <glm.hpp>
#include <SDL_rect.h>
#include "ResourceManager.h"

namespace dae {

	class Texture2D;
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(const std::string& filename, GameObject* pOwner);
		SpriteComponent(std::shared_ptr<Texture2D> texture, GameObject* pOwner);
		virtual ~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void Update() override;
		void Render() const override;
		void Animate(int rows, int columns, int frames, int startIndex, int endIndex);
		void AnimateOnce(int rows, int columns, int frames, int startIndex, int endIndex);
		void SetTexture(const std::string& filename) { m_texture = ResourceManager::GetInstance().LoadTexture(filename); };
		void SetTexture(std::shared_ptr<Texture2D> texture) { m_texture = texture; };
		glm::vec2 GetSize() const { return glm::vec2(m_width, m_height); };
		bool IsAnimatingOnce() const { return m_isAnimatingOnce; };
		void SetOffset(const glm::vec2& offset) { m_offset = offset; };

	private:
		std::shared_ptr<Texture2D> m_texture;
		glm::vec2 m_position{};
		glm::vec2 m_offset{};
		float m_width{};
		float m_height{};
		int m_rows{};
		int m_columns{};
		int m_currentIndex{};
		int m_startIndex{};
		int m_endIndex{};
		SDL_Rect m_rect{};

		float m_currentTime{};
		float m_animationTime{};

		bool m_isAnimatingOnce{ false };
		float m_animationTimeOnce{};
		int m_startIndexOnce{};
		int m_endIndexOnce{};
	};
}