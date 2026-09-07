#include "waveform.hpp"
// #include "nds/interrupts.h"

void Waveform::setBuffer(const s16 *buffer, size_t len) {
  if (buffer != this->buffer || len != buffer_len)
    redraw_wave = true;

  this->buffer = buffer;
  buffer_len = len;
}

//void Waveform::update(u16 *bgBuffer) {
//  if (redraw_wave) {
//    if (bucket_size == 1) {
//      bucket_size = buffer_len / (width * 2);
//    }
//    size_t samples_per_bucket = bucket_size;
//
//    u32 current_sum = 0;
//    u16 current_x = xpos;
//
//    for (size_t s = 0; s < buffer_len; s++) {
//      if (current_x >= xpos + width) {
//        break;
//      }
//      current_sum += abs(buffer[s]);
//
//      if (s % samples_per_bucket == 0) {
//        u16 wave_height = sqrt32((current_sum / samples_per_bucket) >> 1);
//        drawWaveColumn(bgBuffer, current_x, wave_height);
//        current_x++;
//        current_sum = 0;
//      }
//    }
//  }
//
//  redraw_wave = false;
//}

void Waveform::update(u16 *bgBuffer) {
  if (!redraw_wave || !buffer || width == 0) return;

  bucket_size = buffer_len / width;
  if (bucket_size == 0) bucket_size = 1;

  for (size_t x = 0; x < width; x++) {
    size_t start_idx = x * bucket_size;
    u32 current_sum = 0;

    for (size_t i = 0; i < bucket_size; i++) {
      if (start_idx + i >= buffer_len) break;
      current_sum += abs(buffer[start_idx + i]);
    }

    u16 wave_height = sqrt32((current_sum / bucket_size) >> 1);
    drawWaveColumn(bgBuffer, xpos + x, wave_height);
  }

  redraw_wave = false;
}

//u16 Waveform::heightAt(size_t x) {
//  // bucket_size = buffer_len / (width * 2);
//  size_t idx = x * (bucket_size);
//  u32 sum = 0;
//  for (size_t i = 0; i < bucket_size; i++) {
//    if (i + idx >= buffer_len)
//      break;
//    sum += abs(buffer[i + idx]);
//  }
//  return sqrt32((sum / bucket_size) >> 1);
//}

u16 Waveform::heightAt(size_t x) {
  if (!buffer || bucket_size == 0) return 0;

  size_t idx = x * bucket_size;
  u32 sum = 0;

  for (size_t i = 0; i < bucket_size; i++) {
    if (idx + i >= buffer_len) break;
    sum += abs(buffer[idx + i]);
  }

  return sqrt32((sum / bucket_size) >> 1);
}

void Waveform::drawWaveColumn(u16 *buffer, size_t x, u16 wheight) {
  for (int y = 0; y < height; y++) {
    if (abs((height / 2)  - y) > wheight)
      buffer[x + (y+ypos) * 256] = bgColor;
    else
      buffer[x + (y+ypos) * 256] = (u16)ARGB16(1, 31, 31, 31);
  }
}
