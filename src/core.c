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

int rjy_core_symbol(void *dst, RJY_LIBRARY_T library, const char *name)
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

      success &= RJY_LOAD_SYMBOL(retro_run);

      return success;
    }
  }

  return false;
}
