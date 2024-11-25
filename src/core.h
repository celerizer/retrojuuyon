#ifndef RETROJUUYON_CORE_H
#define RETROJUUYON_CORE_H

#include "../libretro-common/include/libretro.h"

#define RJY_LIBRARY_T void*

typedef struct
{
  /* libretro function pointers */
  void (*retro_init)(void);
  void (*retro_deinit)(void);
  unsigned (*retro_api_version)(void);
  void (*retro_get_system_info)(struct retro_system_info*);
  void (*retro_get_system_av_info)(struct retro_system_av_info*);
  void (*retro_set_environment)(retro_environment_t);
  void (*retro_set_video_refresh)(retro_video_refresh_t);
  void (*retro_set_audio_sample)(retro_audio_sample_t);
  void (*retro_set_audio_sample_batch)(retro_audio_sample_batch_t);
  void (*retro_set_input_poll)(retro_input_poll_t);
  void (*retro_set_input_state)(retro_input_state_t);
  void (*retro_set_controller_port_device)(unsigned, unsigned);
  void (*retro_reset)(void);
  void (*retro_run)(void);
  size_t (*retro_serialize_size)(void);
  bool (*retro_serialize)(void*, size_t);
  bool (*retro_unserialize)(const void*, size_t);
  void (*retro_cheat_reset)(void);
  void (*retro_cheat_set)(unsigned, bool, const char*);
  bool (*retro_load_game)(const struct retro_game_info*);
  bool (*retro_load_game_special)(unsigned, const struct retro_game_info*, size_t);
  void (*retro_unload_game)(void);
  unsigned (*retro_get_region)(void);
  void *(*retro_get_memory_data)(unsigned);
  size_t (*retro_get_memory_size)(unsigned);

  RJY_LIBRARY_T library;

  /* libretro structs */
  struct retro_audio_callback audio_callback;
  struct retro_fastforwarding_override fastforwarding_override;
  struct retro_frame_time_callback frame_time_callback;
  struct retro_game_info game_info;
  struct retro_get_proc_address_interface get_proc_address_interface;
  struct retro_hw_render_callback hw_render;
  struct retro_keyboard_callback keyboard;
  enum retro_pixel_format pixel_format;
  struct retro_system_av_info av_info;
  struct retro_system_info system_info;

  /* Additional information */
  unsigned poll_type;
  bool inited;
  bool symbols_inited;
  bool content_loaded;
  bool input_polled;
  bool has_set_subsystems;
  bool has_set_input_descriptors;
  uint64_t serialization_quirks_v;
} rjy_core_t;

int rjy_core_close(rjy_core_t *core);

int rjy_core_open(rjy_core_t *core, RJY_LIBRARY_T library);

int rjy_core_symbol(void *dst, RJY_LIBRARY_T library, const char *name);

#endif
