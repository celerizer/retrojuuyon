#include <libdragon.h>

#include "retrojuuyon.h"

static rjy_ctx_t retrojuuyon;

int main(void)
{
  rjy_ctx_t retrojuuyon;
  struct retro_game_info info;

  RJY_LIBRARY_T library = dlopen("rom:/core.dso", RTLD_NOW);
  if (library)
    return -1;
  else if (rjy_core_open(&retrojuuyon.core, library) < 0)
    return -1;

  info.data = NULL;
  info.size = 0;
  info.path = "rom:/rom.bin";

  if (!rjy_load_game(&retrojuuyon, info))
    printf("retro_load_game FAILED\n");

  while (64)
    rjy_run(&retrojuuyon);
}
