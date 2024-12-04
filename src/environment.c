#include <libretro.h>

#include "environment.h"

rjy_ctx_t *rjy_current = NULL;

bool rjy_environment(unsigned cmd, void *data)
{
  if (!rjy_current)
    return false;
  else switch (cmd)
  {
  case RETRO_ENVIRONMENT_SET_ROTATION:
  {
    if (data)
      rjy_current->video.rotation = *((unsigned*)data);
    break;
  }
  default:
    return false;
  }

  return true;
}
