#pragma once
#include "Audio.h"
#include "NullAudio.h"

class Locator
{
public:
    static void Initialize() { service_ = &nullService_; }

    static Audio* GetAudio() { return service_; }

    static void Provide(Audio* service)
    {
        if (service == nullptr) service_ = &nullService_;
        else service_ = service;
    }

    static void Quit()
    {
        if (service_ != &nullService_ && service_ != nullptr)
        {
            delete service_;
            service_ = nullptr;
        }
    }

private:
    static Audio* service_;
    static NullAudio nullService_;
};

