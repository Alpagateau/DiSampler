#include "playhead.hpp"
#include "waveform.hpp"

void Playhead::setSamplePosition(size_t sample)
{
  target = sample;
}

void Playhead::update(Waveform& w, u16* bgBuffer)
{
  if(target == pos) return;
  u16 wave_height = w.heightAt(getFinalX(w));
  w.drawWaveColumn(bgBuffer, getFinalX(w), wave_height);

  pos = target;

  for (int y = w.getY(); y < w.getBottom(); y++) {
    bgBuffer[w.getX() + getFinalX(w) + y * 256] = (u16)ARGB16(1, 31, 0, 0);
  }
}

size_t Playhead::getFinalX(Waveform& w)
{
  return (((pos << 4) / w.bucket_size) >> 4);
}
