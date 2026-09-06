#ifndef ARM9
#define ARM9
#endif

#include "mm_types.h"
#include "nds/arm9/input.h"
#include "nds/fifocommon.h"
#include "nds/input.h"
#include "engine/sampler.hpp"

#include <nds.h>
#include "nds/arm9/console.h"
#include "nds/interrupts.h"

#include <stdio.h>
#include <dirent.h>
#include "fat.h"

#include "engine/waveform.hpp"
#include "engine/sound.hpp"
#include "engine/playhead.hpp"
#include "file_finder.hpp"


int main(int argc, char *argv[])
{
    defaultExceptionHandler();
    consoleDemoInit();
    soundEnable();
    mm_ds_system ds_sys = {
      .mod_count = 0,
      .samp_count = 0,
      .mem_bank = 0,
      .fifo_channel = FIFO_MAXMOD,
    };
    mmInit(&ds_sys);

    videoSetMode(MODE_FB0);
    vramSetBankA(VRAM_A_LCD);

    if (!fatInitDefault())
    {
      printf("Couldnt load FAT Filesystem\n");
    }
    
    Sound* s = new Sound();
    size_t len = s->loadFromFile("fat:/amen.raw", 48000);


    Playhead ph;
    Waveform wave;
    wave.setBuffer(s->getBuffer16(), len);
    wave.setRect(10, 10, 236, 172);
    ph.setSamplePosition(0);
    printf("Hello World\n");

    //s.play();
    Sampler sampler(s);

    bool playing = false;
    while(1)
    {
      mmStreamUpdate();
      swiWaitForVBlank();
      consoleClear();
      wave.update(VRAM_A);
      ph.update(wave, VRAM_A);
      ph.setSamplePosition(s->current_pos);
      
      scanKeys();
      if(keysDown() & KEY_START)
      {
        if(playing)
          s->stop();
        else
          s->play();
        playing = !playing;
      }

      if(keysHeld() & KEY_SELECT)
      {
        if(keysDown() & KEY_UP)
        {
          sampler.setRegion(0, s->current_pos);
        }
        if(keysDown() & KEY_LEFT)
        {
          sampler.setRegion(1, s->current_pos);
        }
        if(keysDown() & KEY_DOWN)
        {
          sampler.setRegion(2, s->current_pos);
        }
        if(keysDown() & KEY_RIGHT)
        {
          sampler.setRegion(3, s->current_pos);
        }
        if(keysDown() & KEY_A)
        {
          sampler.setRegion(4, s->current_pos);
        }
        if(keysDown() & KEY_B)
        {
          sampler.setRegion(5, s->current_pos);
        }
        if(keysDown() & KEY_X)
        {
          sampler.setRegion(6, s->current_pos);
        }
        if(keysDown() & KEY_Y)
        {
          sampler.setRegion(7, s->current_pos);
        }
      }
      else
      {
        if(keysDown() & KEY_UP)
        {
          sampler.playRegion(0);
        }
        if(keysDown() & KEY_LEFT)
        {
          sampler.playRegion(1);
        }
        if(keysDown() & KEY_DOWN)
        {
          sampler.playRegion(2);
        }
        if(keysDown() & KEY_RIGHT)
        {
          sampler.playRegion(3);
        }
        if(keysDown() & KEY_A)
        {
          sampler.playRegion(4);
        }
        if(keysDown() & KEY_B)
        {
          sampler.playRegion(5);
        }
        if(keysDown() & KEY_X)
        {
          sampler.playRegion(6);
        }
        if(keysDown() & KEY_Y)
        {
          sampler.playRegion(7);
        }
      }
      
      printf("loaded %u / %u samples\n", len, 1000000);

      if(keysHeld() & KEY_SELECT)
      {
        printf("REGION_EDIT MODE\n");
      }
      else if(keysHeld() & KEY_L)
      {
        printf("SAMPLE_EDIT MODE\n");
      }
      else
      {
        printf("PLAYBACK MODE\n");
      }

      printf("[ UP  ] %ld\n", sampler.getRegion(0));
      printf("[LEFT ] %ld\n", sampler.getRegion(1));
      printf("[DOWN ] %ld\n", sampler.getRegion(2));
      printf("[RIGHT] %ld\n", sampler.getRegion(3));
      printf("[  A  ] %ld\n", sampler.getRegion(4));
      printf("[  B  ] %ld\n", sampler.getRegion(5));
      printf("[  X  ] %ld\n", sampler.getRegion(6));
      printf("[  Y  ] %ld\n", sampler.getRegion(7));

    }

    return 0;
}
