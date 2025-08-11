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

    virtual void PlaySound(const std::string& file) override;

private:
    class ConsoleAudioImpl;
    std::unique_ptr<ConsoleAudioImpl> m_pImpl{};
};

