#include <libdragon.h>

#include "input.h"

void rjy_input_poll(rjy_input_t *input)
{
  rjy_input_buttons_t *retro_buttons = &input->buttons[0];
  joypad_buttons_t n64_buttons;
  unsigned i;

  joypad_poll();
  for (i = 0; i < input->max_users; i++)
  {
    rjy_input_buttons_t new_buttons;

    n64_buttons = joypad_get_buttons_pressed(i);
    new_buttons.raw = 0;

    new_buttons.bits.d_right = n64_buttons.d_right;
    new_buttons.bits.d_down = n64_buttons.d_down;
    new_buttons.bits.d_up = n64_buttons.d_up;
    new_buttons.bits.d_left = n64_buttons.d_left;
    new_buttons.bits.a = n64_buttons.c_right;
    new_buttons.bits.b = n64_buttons.c_down;
    new_buttons.bits.x = n64_buttons.c_up;
    new_buttons.bits.y = n64_buttons.c_left;
    new_buttons.bits.l1 = n64_buttons.l;
    new_buttons.bits.r1 = n64_buttons.r;
    new_buttons.bits.start = n64_buttons.start;
    new_buttons.bits.select = n64_buttons.z;
    *retro_buttons = new_buttons;

    retro_buttons++;
  }
}

int16_t core_input_state(const rjy_input_t *input, unsigned port,
                         unsigned device, unsigned index, unsigned id)
{
  if (port < input->max_users)
  {
    switch (device)
    {
    case RETRO_DEVICE_JOYPAD:
      if (id == RETRO_DEVICE_ID_JOYPAD_MASK)
        /* Get input bitmask */
        return input->buttons[port].raw;
      else
        /* Get input binary button */
        return (input->buttons[port].uraw & (1 << id)) ? 1 : 0;
    }
  }

  return 0;
}
