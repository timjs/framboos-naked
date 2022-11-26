#include "shared/graphics.h"
#include "kernel/hardware/framebuffer.h"
#include "kernel/hardware/interrupt.h"
#include "kernel/hardware/uart.h"
#include "kernel/panic.h"
#include "shared/bitfont.h"

void draw_pixel(framebuffer_info_t *fb, point_t position, color_t color) {
  fb->buf[position.x * BYTES_PER_PIXEL + position.y * fb->pitch + 2] =
      color.red;
  fb->buf[position.x * BYTES_PER_PIXEL + position.y * fb->pitch + 1] =
      color.green;
  fb->buf[position.x * BYTES_PER_PIXEL + position.y * fb->pitch + 0] =
      color.blue;
}

void draw_rectangle(framebuffer_info_t *fb, area_t area, color_t color) {
  kernel_panic("No implementation of `draw_rectangle");
}

void draw_character(framebuffer_info_t *fb, point_t position, color_t color,
                    char c) {
  const uint8_t *data = font(c);

  for (int y = 0; y < 8; y++) {
    uint8_t line = data[y];
    for (int x = 0; x < 8; x++) {
      if ((line & 1) != 0) {
        draw_pixel(fb, (point_t){.x = position.x + x, .y = position.y + y},
                   color);
      }

      line >>= 1;
    }
  }
}

void draw_string(framebuffer_info_t *fb, point_t position, color_t color,
                 char *str) {
  kernel_panic("No implementation of `draw_string`")
}