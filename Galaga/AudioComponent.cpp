#include "AudioComponent.h"

dae::AudioComponent::AudioComponent(GameObject* pOwner) : BaseComponent(pOwner)
{
	m_pAudioService = Locator::GetAudio();
	if (m_pAudioService == nullptr) return;

	m_shootSoundId = m_pAudioService->LoadSound("../Data/Audio/PlayerShoot.mp3");

	m_pAudioService->PlaySound(m_shootSoundId);
}

void dae::AudioComponent::Update(float)
{
	if (m_pAudioService == nullptr) {
		m_pAudioService = Locator::GetAudio();
		if (m_pAudioService == nullptr) return;

		m_shootSoundId = m_pAudioService->LoadSound("../Data/Audio/PlayerShoot.mp3");
	}

	m_pAudioService->PlaySound(m_shootSoundId);
}
