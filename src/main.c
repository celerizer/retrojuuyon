#include <libdragon.h>

#include "retrojuuyon.h"

static rjy_ctx_t retrojuuyon;

int main(void)
{
  struct retro_game_info info;

  joypad_init();
  console_init();
  console_set_render_mode(RENDER_MANUAL);

  dfs_init(DFS_DEFAULT_LOCATION);

  memset(&retrojuuyon, 0, sizeof(retrojuuyon));

  if (rjy_core_open(&retrojuuyon.core, "rom:/core.dso") < 0)
    return -1;
  else
  {
    console_clear();
    printf("retro_run: %p\n retro_init: %p",
           retrojuuyon.core.retro_run,
           retrojuuyon.core.retro_init);
    console_render();
  }

  rjy_get_system_info(&retrojuuyon);

  rjy_set_environment(&retrojuuyon);

  rjy_init(&retrojuuyon);

  info.data = NULL;
  info.size = 0;
  info.path = "rom:/content.bin";

  if (!rjy_load_game(&retrojuuyon, info))
    printf("retro_load_game FAILED\n");

  rjy_get_system_av_info(&retrojuuyon);

  while (64)
    rjy_run(&retrojuuyon);
}
