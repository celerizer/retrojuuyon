#ifndef RETROJUUYON_H
#define RETROJUUYON_H

#include <libretro.h>

#include "config.h"
#include "core.h"
#include "environment.h"
#include "input.h"

typedef struct
{
  rjy_core_t core;
  rjy_input_t input;
} rjy_ctx_t;

bool rjy_load_game(rjy_ctx_t *rjy, struct retro_game_info info);

void rjy_reset(rjy_ctx_t *rjy);

void rjy_run(rjy_ctx_t *rjy);

void rjy_set_environment(rjy_ctx_t *rjy);

#endif
