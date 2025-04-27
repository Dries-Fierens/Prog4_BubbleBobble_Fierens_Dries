#pragma once
#include "BaseComponent.h"
#include "Audio.h"
#include "Locator.h"

namespace dae {
	class GameObject;
	class AudioComponent final : public BaseComponent
	{
	public:
		AudioComponent(GameObject* pOwner);
		virtual ~AudioComponent() = default;

		AudioComponent(const AudioComponent&) = delete;
		AudioComponent(AudioComponent&&) noexcept = delete;
		AudioComponent& operator=(const AudioComponent&) = delete;
		AudioComponent& operator=(AudioComponent&&) noexcept = delete;

		virtual void Update(float /*delta_time*/) override;
		void Render() const override {};

	private:
		Audio* m_pAudioService{ nullptr };

		int m_shootSoundId{};
	};
}

