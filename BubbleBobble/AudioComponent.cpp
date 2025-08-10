//#include "AudioComponent.h"
//#include "BaseComponent.h"
//
//dae::AudioComponent::AudioComponent(GameObject* pOwner) : BaseComponent(pOwner)
//{
//	//Locator::Initialize();
//	m_pAudioService = Locator::GetAudio();
//	if (m_pAudioService == nullptr) return;
//
//	m_shootSoundId = m_pAudioService->LoadSound("../Data/Audio/PlayerShoot.mp3");
//
//	m_pAudioService->PlaySound(m_shootSoundId);
//}
//
//void dae::AudioComponent::Update()
//{
//	if (m_pAudioService == nullptr) {
//		m_pAudioService = Locator::GetAudio();
//		if (m_pAudioService == nullptr) return;
//
//		m_shootSoundId = m_pAudioService->LoadSound("../Data/Audio/PlayerShoot.mp3");
//	}
//
//	m_pAudioService->PlaySound(m_shootSoundId);
//}
