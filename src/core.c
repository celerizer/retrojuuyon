#include <dlfcn.h>
#include <string.h>

#include "core.h"

int rjy_core_close(rjy_core_t *core)
{
  if (core)
    return dlclose(core->library);
  else
    return 1;
}

static int rjy_core_symbol(void *dst, RJY_LIBRARY_T library, const char *name)
{
  if (dst && library && name)
  {
    void *symbol = dlsym(library, name);

    if (symbol)
    {
      memcpy(dst, symbol, sizeof(uintptr_t));
      return 1;
    }
  }

  return 0;
}

#define RJY_LOAD_SYMBOL(a) rjy_core_symbol(core->a, library, "a")
int rjy_core_open(rjy_core_t *core, const char *path)
{
  if (core && path)
  {
    RJY_LIBRARY_T library = dlopen(path, RTLD_NOW);
    if (library)
    {
      bool success = true;

      success &= RJY_LOAD_SYMBOL(retro_init);
      success &= RJY_LOAD_SYMBOL(retro_deinit);
      success &= RJY_LOAD_SYMBOL(retro_api_version);
      success &= RJY_LOAD_SYMBOL(retro_get_system_info);
      success &= RJY_LOAD_SYMBOL(retro_get_system_av_info);
      success &= RJY_LOAD_SYMBOL(retro_set_environment);
      success &= RJY_LOAD_SYMBOL(retro_set_video_refresh);
      success &= RJY_LOAD_SYMBOL(retro_set_audio_sample);
      success &= RJY_LOAD_SYMBOL(retro_set_audio_sample_batch);
      success &= RJY_LOAD_SYMBOL(retro_set_input_poll);
      success &= RJY_LOAD_SYMBOL(retro_set_input_state);
      success &= RJY_LOAD_SYMBOL(retro_set_controller_port_device);
      success &= RJY_LOAD_SYMBOL(retro_reset);
      success &= RJY_LOAD_SYMBOL(retro_run);
      success &= RJY_LOAD_SYMBOL(retro_serialize_size);
      success &= RJY_LOAD_SYMBOL(retro_serialize);
      success &= RJY_LOAD_SYMBOL(retro_unserialize);
      success &= RJY_LOAD_SYMBOL(retro_cheat_reset);
      success &= RJY_LOAD_SYMBOL(retro_cheat_set);
      success &= RJY_LOAD_SYMBOL(retro_load_game);
      success &= RJY_LOAD_SYMBOL(retro_load_game_special);
      success &= RJY_LOAD_SYMBOL(retro_unload_game);
      success &= RJY_LOAD_SYMBOL(retro_get_region);
      success &= RJY_LOAD_SYMBOL(retro_get_memory_data);
      success &= RJY_LOAD_SYMBOL(retro_get_memory_size);

      return success;
    }
  }

  return false;
}
