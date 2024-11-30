#include <libdragon.h>

#include "audio.h"
#include "config.h"

void rjy_audio_init(const int frequency)
{
#if RETROJUUYON_HAVE_AUDIO
  audio_init(frequency, 4);
#endif
}

void rjy_audio_sample(int16_t left, int16_t right)
{
#if RETROJUUYON_HAVE_AUDIO
  int16_t sample[2] = { left, right };

  audio_push(sample, 1, true);
#endif
}

size_t rjy_audio_sample_batch(const int16_t *data, size_t frames)
{
#if RETROJUUYON_HAVE_AUDIO
  return audio_push(data, frames, true);
#else
  return 0;
#endif
}
