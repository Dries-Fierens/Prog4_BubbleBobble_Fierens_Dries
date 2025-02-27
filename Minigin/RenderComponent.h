#pragma once
#include "BaseComponent.h"
#include <string>
#include <memory>

namespace dae {

	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		void Update(float delta_time) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);

		RenderComponent(const std::string& filename, GameObject* pOwner);
		RenderComponent(std::shared_ptr<Texture2D> texture, GameObject* pOwner);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		std::shared_ptr<Texture2D> m_texture;

	};
}

