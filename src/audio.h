#ifndef RETROJUUYON_AUDIO_H
#define RETROJUUYON_AUDIO_H

#include <libretro.h>

void rjy_audio_sample(int16_t left, int16_t right);

size_t rjy_audio_sample_batch(const int16_t *data, size_t frames);

#endif
