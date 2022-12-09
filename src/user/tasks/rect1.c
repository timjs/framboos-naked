#include "kernel/hardware/framebuffer.h"
#include "kernel/hardware/timer.h"
#include "kernel/hardware/uart.h"
#include "kernel/scheduler.h"
#include "shared/graphics.h"
#include <stdbool.h>

void task_rect1() {
  uart_log_begin("Starting rectangle top left");
  framebuffer_info_t *fb = framebuffer_get_info();

  area_t top_left_area = (area_t){
      .topleft = (point_t){.x = 200, .y = 100},
      .size = (size2d_t){.width = 300, .height = 100},
  };

  while (true) {
    draw_rectangle(fb, top_left_area, color_red);
    timer_wait_us(1000 * US_PER_MS);

    draw_rectangle(fb, top_left_area, color_green);
    timer_wait_us(1000 * US_PER_MS);
  }
}
