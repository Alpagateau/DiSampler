#include "sampler.hpp"

Sampler::Sampler(Sound* s)
{
  sound = s;
}

void Sampler::playRegion(u8 idx)
{
  if(idx >= 8) return;
  sound->current_pos = regions[idx];
  sound->play();
}
