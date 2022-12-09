#include "kernel/hardware/framebuffer.h"
#include "kernel/hardware/interrupt.h"
#include "kernel/hardware/mailbox.h"
#include "kernel/hardware/timer.h"
#include "kernel/hardware/uart.h"
#include "kernel/panic.h"
#include "kernel/scheduler.h"
#include "kernel/task.h"
#include "shared/graphics.h"

void kernel_init() {
  uart_init();

  uart_log_begin("Initialising");

  interrupt_init();

  framebuffer_init();
  framebuffer_info_t *fb = framebuffer_get_info();
  uart_log_info("Framebuffer: address=0x%x, width=%u, height=%u, size=%u",
                fb->buf, fb->width, fb->height, fb->buf_size);

  uart_log_end("Initialised kernel");
}

void kernel_main() { kernel_init(); }
