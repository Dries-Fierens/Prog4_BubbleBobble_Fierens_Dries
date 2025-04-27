#pragma once
#include "Audio.h"
#include <mutex>
#include <queue>

class ConsoleAudio final : public Audio
{
public:
    ConsoleAudio();

    virtual void Update() override;

    virtual void PlaySound(int soundID) override;
    virtual void StopSound(int soundID) override;
    virtual void StopAllSounds() override;
    virtual int LoadSound(const char* file) override;

private:
    void Initialize();

    bool m_running;
    std::mutex m_mutex;
    std::condition_variable m_conditionVariable;
    std::queue<int> m_queue;
    std::vector<Mix_Chunk*> m_pSounds;
};

