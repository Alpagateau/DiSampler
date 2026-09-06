#ifndef ENGINE_WAVEFORM
#define ENGINE_WAVEFORM

#ifndef ARM9
#define ARM9
#endif

#include <nds.h>
#include <stddef.h>

class Waveform
{
  public:
    void setRect(u16 x, u16 y, u16 w, u16 h)
    {
      xpos = x;
      ypos = y;
      width = w;
      height = h;
      redraw_wave = true;
    };

    void setBuffer(const s16* buffer, size_t len);
    u16 heightAt(size_t x);
    void drawWaveColumn(u16* buffer, size_t x, u16 height);

    size_t getX(){return xpos;};
    size_t getY(){return ypos;};
    size_t getWidth(){return width;};
    size_t getHeight(){return height;};
    size_t getRight(){return xpos + width;};
    size_t getBottom(){return ypos + height;};

    void update(u16* bgBuffer);
    size_t bucket_size = 1;
    size_t buffer_len = 0;
  private:
    u16 xpos = 0, ypos = 0, width = 256, height = 192;

    bool redraw_wave;
    const s16* buffer = NULL;
};

#endif
