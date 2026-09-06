#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#ifndef ARM9
#define ARM9
#endif

#include "sound.hpp"

class Sampler
{
  public:
    Sampler(Sound* s);

    void setRegion(u8 idx, u32 sample){regions[idx] = sample;};
    u32  getRegion(u8 idx){return regions[idx];};
    void playRegion(u8 idx);
  private:
    Sound* sound;
    u32 regions[8] = {};
};

#endif
