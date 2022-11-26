#include "kernel/hardware/framebuffer.h"
#include "kernel/hardware/interrupt.h"
#include "kernel/hardware/mailbox.h"
#include "kernel/hardware/timer.h"
#include "kernel/hardware/uart.h"
#include "kernel/panic.h"
#include "kernel/scheduler.h"
#include "kernel/task.h"
#include "shared/graphics.h"

#define US_PER_MS 1000

framebuffer_info_t *fb;

void kernel_init() {
  uart_init();

  uart_log_begin("Initializing");

  interrupt_init();

  fb = framebuffer_init();
  uart_log_info("Framebuffer: address=0x%x, width=%u, height=%u, size=%u",
                fb->buf, fb->width, fb->height, fb->buf_size);

  uart_log_end("Initialized kernel");
}

void kernel_main() { kernel_init(); }