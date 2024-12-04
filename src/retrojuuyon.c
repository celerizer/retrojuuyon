#include <stdio.h>

#include "retrojuuyon.h"

void rjy_get_system_av_info(rjy_ctx_t *rjy)
{
  if (rjy && rjy->core.retro_get_system_av_info)
    rjy->core.retro_get_system_av_info(&rjy->core.av_info);
}

void rjy_get_system_info(rjy_ctx_t *rjy)
{
  if (rjy && rjy->core.retro_get_system_info)
    rjy->core.retro_get_system_info(&rjy->core.system_info);
}

void rjy_init(rjy_ctx_t *rjy)
{
  if (rjy)
    rjy->core.retro_init();
}

bool rjy_load_game(rjy_ctx_t *rjy, struct retro_game_info info)
{
  if (info.data && info.size)
    return rjy->core.retro_load_game(&info);
  else
  {
    FILE *file;

    file = fopen(info.path, "rb");

    if (file)
    {
      /* Read data and size */
      fclose(file);
      return rjy->core.retro_load_game(&info);
    }
  }

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
