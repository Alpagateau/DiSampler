#include "sound.hpp"
#include "mm_types.h"
#include <string.h>
#include <maxmod9.h>
#include <stdlib.h>

Sound *s_sound;

size_t Sound::loadFromFile(const char *path, u16 Hz) {
  this->Hz = Hz;
  FILE *f = fopen(path, "rb");
  if(f == NULL) return 0;
  len = fread(buffer, sizeof(s16), buffer_size, f);
  si = {
        .sampling_rate = Hz,
        .buffer_length = 1024,
        .callback = sound_callback,
        .format = MM_STREAM_16BIT_MONO,
        .timer = MM_TIMER0,
        .manual = true
  };

  return len;
}

void Sound::play() {
  mmStreamClose();
  s_sound = this;
  mmStreamOpen(&si);
}

void Sound::stop() {
  if (s_sound != this)
    return;
  current_pos = 0;
  mmStreamClose();
  s_sound = nullptr;
}

void Sound::pause() {
  if (s_sound != this)
    return;
  mmStreamClose();
}

void Sound::clear()
{
  memset(buffer, 0, buffer_size * sizeof(buffer[0]));
}

mm_word sound_callback(mm_word l, mm_addr a, mm_stream_formats f) {
  if (s_sound == nullptr){
    memset(a, 0, l*2);
    return 0;
  }

  size_t pos = s_sound->current_pos; 
  size_t len = s_sound->getLen();
  s16*   buf = s_sound->getBuffer16();
  s16*   dst = (s16*)a;

  for(size_t i = 0; i < l; i++) 
  {
    if(pos >= len) pos = 0;
    dst[i] = buf[pos++];
  }

  s_sound->display_pos = s_sound->current_pos;
  s_sound->current_pos = pos;
  return l;
}
