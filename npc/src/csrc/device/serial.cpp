#include <utils.h>
#include <device/map.h>


#define CH_OFFSET 0
static uint32_t *serial_base = NULL;

static void serial_putc(char ch) {
  putc(ch, stderr);
}

static void serial_io_handler(uint32_t offset, int len, bool is_write) {
  assert(len == 1);
  switch (offset) {
    /* We bind the serial port with the ho1st stderr in NEMU. */
    case CH_OFFSET:
      if (is_write) serial_putc( (char)(serial_base[0]) );
      else panic("do not support read");
      break;
    default: panic("do not support offset = %d", offset);
  }
}

void init_serial() {
    int total_regs = NEW_IO_SPACE(1);
    serial_base = (uint32_t *)new_space(total_regs);
    add_mmio_map("serial", CONFIG_SERIAL_MMIO, serial_base, total_regs, serial_io_handler);
}
