#include <common.h>
#include <utils.h>
#include <SDL2/SDL.h>

void init_map();
void init_serial();
void init_rtc();

/*
void send_key(uint8_t, bool);
void vga_update_screen();

// 这里实现的是定期刷新设备，目前还不需要这个功能
void device_update() {
  static uint64_t last = 0;
  uint64_t now = get_time();
  if (now - last < 1000000 / TIMER_HZ) {
    return;
  }
  last = now;

  IFDEF(CONFIG_HAS_VGA, vga_update_screen());

#ifndef CONFIG_TARGET_AM
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        nemu_state.state = NEMU_QUIT;
        break;
      default: break;
    }
  }
#endif
}



void sdl_clear_event_queue() {
#ifndef CONFIG_TARGET_AM
  SDL_Event event;
  while (SDL_PollEvent(&event));
#endif
}
*/


void init_device() {
  init_map();
  init_serial();
  init_rtc();
}
