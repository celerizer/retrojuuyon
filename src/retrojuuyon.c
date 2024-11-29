#include <stdio.h>

#include "retrojuuyon.h"

bool rjy_load_game(rjy_ctx_t *rjy, struct retro_game_info info)
{
  FILE *file;

  file = fopen(info.path, "rb");
  
  if (file)
    return true;
  else
    return false;
}

void rjy_set_environment(rjy_ctx_t *rjy)
{
  if (!rjy || !rjy->core.retro_set_environment)
    return;
  rjy->core.retro_set_environment(rjy_environment);
}

void rjy_reset(rjy_ctx_t *rjy)
{
  if (!rjy || !rjy->core.retro_reset)
    return;
  rjy->core.retro_reset();
}

void rjy_run(rjy_ctx_t *rjy)
{
#if RETROJUUYON_SAFETY
  if (!rjy || !rjy->core.retro_run)
    return;
#endif
  rjy->core.retro_run();
}
