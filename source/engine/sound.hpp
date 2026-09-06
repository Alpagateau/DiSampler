#ifndef SOUND_HPP
#define SOUND_HPP

#ifndef ARM9
#define ARM9
#endif

#include "mm_types.h"
#include <nds.h>
#include <stddef.h>
#include <maxmod9.h>

class Sound
{
  public:
    size_t loadFromFile(const char* path, u16 Hz);

    s8*    getBuffer8(){return (s8*)buffer;};
    s16*   getBuffer16(){return (s16*)buffer;};
    size_t getLen(){return len;};

    void clear();

    void recordStart();
    void recordEnd();

    void play();
    void pause();
    void resume();
    void stop();
    static const u32 buffer_size = 5000000;

    volatile size_t current_pos = 0;
    volatile size_t display_pos = 0;
  private:
    u16    Hz;
    s16    buffer[buffer_size];
    size_t len;

    //stream info
    mm_stream si;
};

mm_word sound_callback(mm_word l, mm_addr a, mm_stream_formats f);

#endif
