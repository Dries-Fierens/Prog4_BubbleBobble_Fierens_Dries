#pragma once
#include "Audio.h"

class NullAudio final : public Audio
{
public:
    virtual void Update() override {};

    virtual void PlaySound(int /*soundID*/) override {};
    virtual void StopSound(int /*soundID*/) override {};
    virtual void StopAllSounds() override {};
    virtual int LoadSound(const char* /*file*/) override { return 0; };
};
