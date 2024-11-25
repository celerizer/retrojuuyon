#include <libdragon.h>

#include "core.h"
//#include "main.h"

static rjy_core_t core;

typedef union
{
  struct
  {
    uint16_t r3 : 1;
    uint16_t l3 : 1;
    uint16_t r2 : 1;
    uint16_t l2 : 1;
    uint16_t r1 : 1;
    uint16_t l1 : 1;
    uint16_t x : 1;
    uint16_t a : 1;
    uint16_t d_right : 1;
    uint16_t d_left : 1;
    uint16_t d_down : 1;
    uint16_t d_up : 1;
    uint16_t start : 1;
    uint16_t select : 1;
    uint16_t y : 1;
    uint16_t b : 1;
  } bits;
  int16_t raw;
  uint16_t uraw;
} rjy_input_buttons_t;

static unsigned rjy_input_max_users = 4;
static rjy_input_buttons_t rjy_input_joypad[4];

static void core_audio_sample(int16_t left, int16_t right)
{
  /** @todo */
}

static size_t core_audio_sample_batch(const int16_t *data, size_t frames)
{
  /** @todo */
  return 0;
}

static void core_input_poll(void)
{
  rjy_input_buttons_t retro_buttons;
  joypad_buttons_t n64_buttons;
  unsigned i;

  joypad_poll();
  for (i = 0; i < rjy_input_max_users; i++)
  {
    n64_buttons = joypad_get_buttons_pressed(i);
    retro_buttons.raw = 0;

    retro_buttons.bits.d_right = n64_buttons.d_right;
    retro_buttons.bits.d_down = n64_buttons.d_down;
    retro_buttons.bits.d_up = n64_buttons.d_up;
    retro_buttons.bits.d_left = n64_buttons.d_left;
    retro_buttons.bits.a = n64_buttons.c_right;
    retro_buttons.bits.b = n64_buttons.c_down;
    retro_buttons.bits.x = n64_buttons.c_up;
    retro_buttons.bits.y = n64_buttons.c_left;
    retro_buttons.bits.l1 = n64_buttons.l;
    retro_buttons.bits.r1 = n64_buttons.r;
    retro_buttons.bits.start = n64_buttons.start;
    retro_buttons.bits.select = n64_buttons.z;

    rjy_input_joypad[i] = retro_buttons;
  }
}

static int16_t core_input_state(unsigned port, unsigned device, unsigned index,
                                unsigned id)
{
  if (port < rjy_input_max_users)
  {
    switch (device)
    {
    case RETRO_DEVICE_JOYPAD:
      if (id == RETRO_DEVICE_ID_JOYPAD_MASK)
        return rjy_input_joypad[port].raw;
      else
        return rjy_input_joypad[port].uraw << id;
    }
  }
}

int main(void)
{
  core.library = dlopen("sd:/retrojuuyon/cores/tamalibretro.dso", RTLD_NOW);

  while (1)
  {
    core.retro_run();
  }
}
