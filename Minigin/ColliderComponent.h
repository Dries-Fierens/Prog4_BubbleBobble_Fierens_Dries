#pragma once
#include "BaseComponent.h"
#include <glm.hpp>

namespace dae 
{
	class ColliderComponent final : public BaseComponent
	{
	public:
		ColliderComponent(GameObject* pOwner);
		~ColliderComponent() override = default;
		ColliderComponent(const ColliderComponent& other) = delete;
		ColliderComponent operator=(const ColliderComponent& other) = delete;
		ColliderComponent(ColliderComponent&& other) = delete;
		ColliderComponent operator=(ColliderComponent&& other) = delete;

		void Update() override;
		void Render() const override;

		const glm::vec2& GetPosition() const { return m_position; }
		const glm::vec2& GetSize() const { return m_size; }
		void SetSize(const glm::vec2& size) { m_size = size; }
		void ShowCollisions(bool show) { m_showCollisions = show; }
		bool GetShowCollisions() const { return m_showCollisions; }
		bool IsOverlapping(ColliderComponent* other);
		void UpdatePosition();

	private:
		glm::vec2 m_position{};
		glm::vec2 m_size{};
		glm::vec4 m_color{ 1.f, 1.f, 1.f, 1.f };
		bool m_showCollisions{ false };
	};
}

