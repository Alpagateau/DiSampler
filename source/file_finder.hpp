#ifndef FILE_FINDER_HPP
#define FILE_FINDER_HPP

#ifndef ARM9
#define ARM9
#endif

#include <nds.h>
#include <dirent.h>

class FileFinder
{
  public:
    FileFinder();
    void selectFile(char* result);
  private:
    char current_path[512] = {};
    DIR* dir = NULL;
    struct dirent* ent;
    
    void openDir(char* path);
    void listDir();
};

#endif
