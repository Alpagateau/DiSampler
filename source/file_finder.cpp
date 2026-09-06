#include "file_finder.hpp"
#include "nds/interrupts.h"
#include <dirent.h>
#include <string.h>

FileFinder::FileFinder()
{
  current_path[0] = 0;
}

void FileFinder::selectFile(char* result)
{
  while(1)
  {
    swiWaitForVBlank();   
  }

  strcpy(result, current_path);
}

void FileFinder::openDir(char* path)
{
  if(dir != NULL){
    closedir(dir);
    dir = NULL;
  }
}
