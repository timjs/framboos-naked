#include "kernel/hardware/framebuffer.h"
#include "kernel/hardware/timer.h"
#include "kernel/hardware/uart.h"
#include "kernel/scheduler.h"
#include "shared/graphics.h"
#include <stdbool.h>

void task_rect2() {
  uart_log_begin("Starting rectangle top right");
  framebuffer_info_t *fb = framebuffer_get_info();

  area_t top_right_area = (area_t){
      .topleft = (point_t){.x = 800, .y = 100},
      .size = (size2d_t){.width = 300, .height = 100},
  };

  for (uint32_t i = 0; i < 10; i++) {
    draw_rectangle(fb, top_right_area, color_yellow);
    timer_wait_us(500 * US_PER_MS);

    draw_rectangle(fb, top_right_area, color_cyan);
    timer_wait_us(500 * US_PER_MS);
  }

  uart_log_end("Terminating rectangle top right");
}
