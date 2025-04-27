#pragma once  
#include "../3rdParty/SDL2_mixer-2.8.1/include/SDL_mixer.h"
#include <SDL.h>

class Audio  
{  
public:  
   Audio() = default;  
   virtual ~Audio() {};  

   Audio(const Audio&) = delete;  
   Audio(Audio&&) noexcept = delete;  

   Audio& operator=(const Audio&) = delete;  
   Audio& operator=(Audio&&) noexcept = delete;  

   virtual void Update() = 0;  

   virtual void PlaySound(int soundID) = 0;  
   virtual void StopSound(int soundID) = 0;  
   virtual void StopAllSounds() = 0;  
   virtual int LoadSound(const char* file) = 0;  
};
