#include <am.h>
#include <nemu.h>
#define CONFIG_ADDR (VGACTL_ADDR + 0)
#define SYNC_ADDR (VGACTL_ADDR + 4)
void __am_gpu_init() {
  /*
  int i;
  uint32_t data = inl(CONFIG_ADDR);
  int w = data >> 16;  // TODO: get the correct width
  int h = data & 0x0000ffffu;  // TODO: get the correct height
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (i = 0; i < w * h; i ++) fb[i] = i;
  outl(SYNC_ADDR, 1);
  */
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  uint32_t data = inl(CONFIG_ADDR);
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
  };
  cfg->width = data >> 16;
  cfg->height = data & 0x0000ffffu;
  cfg->vmemsz = cfg->width * cfg->height * 4;
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {

  uint32_t width = inl(CONFIG_ADDR) >> 16;
  uint32_t *pixels = ctl->pixels;
  uint32_t y = ctl->y, x = ctl->x;
  uint32_t w = ctl->w, h = ctl->h;

  uint32_t base_addr = FB_ADDR + (width * y + x) * 4;
  uint32_t row_stride = width * 4; // 每行字节数
  if (!ctl->sync && (w == 0 || h == 0)) return;
  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {
      //获得 RGB
      uint32_t pixel = pixels[row * w + col];
      uint32_t R = (pixel >> 16) & 0xff;
      uint32_t G = (pixel >> 8) & 0xff;
      uint32_t B = pixel & 0xff;

      // ARGB 格式
      uint32_t single_pixel = 0xff000000 | (R << 16) | (G << 8) | B;

      // 写入显存
      uint32_t addr = base_addr + row * row_stride + col * 4;
      outl(addr, single_pixel);
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
