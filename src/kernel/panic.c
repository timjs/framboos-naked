#include "kernel/panic.h"
#include "kernel/hardware/interrupt.h"
#include "kernel/hardware/uart.h"

// "Crashes" the kernel by printing an error message and entering an infinite
// loop.
void kernel_panic_implementation(const char *message) {
  interrupts_disable();

  uart_log_error("%s", message);

  while (true) {
  }
}
