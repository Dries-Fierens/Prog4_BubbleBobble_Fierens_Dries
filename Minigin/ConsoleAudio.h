#pragma once
#include "Audio.h"
#include <mutex>
#include <queue>
#include <condition_variable>
#include <iostream>

class ConsoleAudio final : public Audio
{
public:
    ConsoleAudio();
	~ConsoleAudio() override;

    virtual void Update() override;

    virtual void PlaySound(int soundID) override;
    virtual void StopSound(int soundID) override;
    virtual void StopAllSounds() override;
    virtual int LoadSound(const char* file) override;

private:
    class ConsoleAudioImpl;
    std::unique_ptr<ConsoleAudioImpl> m_pImpl{};
};

