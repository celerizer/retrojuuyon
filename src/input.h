#ifndef RETROJUUYON_INPUT_H
#define RETROJUUYON_INPUT_H

#include <libretro.h>

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

typedef struct
{
  rjy_input_buttons_t buttons[4];
  unsigned max_users;
} rjy_input_t;

void rjy_input_poll(rjy_input_t *input);

int16_t rjy_input_state(const rjy_input_t *input, unsigned port,
                        unsigned device, unsigned index, unsigned id);

#endif
