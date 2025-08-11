#pragma once  
#include "Audio.h"  

class NullAudio final : public Audio  
{  
public:
   virtual void PlaySound(const std::string& /*file*/) override {};
};
