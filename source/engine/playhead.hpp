#ifndef ENGINE_PLAYHEAD
#define ENGINE_PLAYHEAD

#ifndef ARM9
#define ARM9
#endif

#include <stddef.h>
#include <nds.h>
#include "waveform.hpp"

class Playhead{
  public:
    void setSamplePosition(size_t sample);
    void update(Waveform& w, u16* bgBuffer);
  private:

    size_t getFinalX(Waveform& w);

    u16 color = (u16)ARGB16(1, 31, 0, 0);
    size_t pos = -1;
    size_t target = 0;
    u16 hidden_val = 0;
};

#endif
