#include <libretro.h>

#include "environment.h"

bool rjy_environment(rjy_ctx_t *rjy, unsigned cmd, void *data)
{
  switch (cmd)
  {
  case RETRO_ENVIRONMENT_SET_ROTATION:
  {
    if (data)
      rjy->video.rotation = *((unsigned*)data);
    break;
  }
  default:
    return false;
  }

  return true;
}
