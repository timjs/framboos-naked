#include "kernel/hardware/timer.h"
#include "kernel/hardware/uart.h"
#include "kernel/scheduler.h"
#include "shared/graphics.h"
#include "shared/strfmt.h"
#include <stdbool.h>

extern framebuffer_info_t *fb;

void draw_startup_picture() {
  extern unsigned char _binary____src_startup_picture_bin_start[];
  unsigned char *data = &(_binary____src_startup_picture_bin_start[0]);
  framebuffer_info_t *fb = framebuffer_get_info();
  for (int y = 0; y < 400; y++) {
    for (int x = 0; x < 640; x++) {
      uint8_t r = *data++;
      uint8_t g = *data++;
      uint8_t b = *data++;
      draw_rectangle(fb,
                     (area_t){
                         .topleft =
                             (point_t){
                                 .x = x * 2,
                                 .y = y * 2,
                             },
                         .size =
                             (size2d_t){
                                 .width = 2,
                                 .height = 2,
                             },
                     },
                     (color_t){
                         .red = r,
                         .green = g,
                         .blue = b,
                     });
    }
  }
}

void task_startup_picture() {
  uart_log_begin("Starting progress bar animation");
  uart_log_info("Task ID: #%u", scheduler_current_task()->tid);

  framebuffer_info_t *fb = framebuffer_get_info();
  uart_log_info("Obtained framebuffer of size: %ux%u", fb->width, fb->height);

  uart_log_begin("Drawing startup picture");
  draw_startup_picture();

  uart_log_begin("Drawing progress bar");
  color_t background = (color_t){.red = 170, .green = 185, .blue = 196};
  color_t foreground = (color_t){.red = 74, .green = 123, .blue = 183};

  int pos = 0;
  int dir = 1;
  int bar_size = 64;
  while (true) {
    pos += dir * 16;
    if (pos >= fb->width - bar_size) {
      pos = fb->width - bar_size;
      dir = -1;
    } else if (pos <= 0) {
      pos = 0;
      dir = 1;
    }

    draw_rectangle(fb,
                   (area_t){
                       .topleft = (point_t){.x = 0, .y = fb->height - 16},
                       .size = (size2d_t){.height = 16, .width = fb->width},
                   },
                   background);
    draw_rectangle(fb,
                   (area_t){
                       .topleft = (point_t){.x = pos, .y = fb->height - 16},
                       .size = (size2d_t){.height = 16, .width = bar_size},
                   },
                   foreground);

    timer_wait_us(33 * US_PER_MS);
  }
}
