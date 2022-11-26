/*
 * Handlers for exceptions referenced in exceptions.s
 */
#include "kernel/hardware/framebuffer.h"
#include "kernel/hardware/interrupt.h"
#include "kernel/hardware/timer.h"
#include "kernel/hardware/uart.h"
#include "kernel/panic.h"
#include "kernel/scheduler.h"
#include "kernel/task.h"

// Interrupt request handler
void irq_handler(saved_cpu_state_t *saved_state) {
  kernel_panic("Received an unknown interrupt");
}

// Software interrupt handler
void swi_handler(saved_cpu_state_t *saved_state) {
  uart_log_info("syscall[%u](0x%x, 0x%x, 0x%x)", saved_state->r0,
                saved_state->r1, saved_state->r2, saved_state->r3);
  switch (saved_state->r0) {
  default:
    uart_log_cpu_state(saved_state);
    kernel_panic("Unknown syscall: 0x%x", saved_state->r0);
  }
}

void __attribute__((interrupt("ABORT"))) reset_handler(void) {
  kernel_panic("RESET HANDLER");
}

void __attribute__((interrupt("ABORT"))) prefetch_abort_handler(void) {
  kernel_panic("PREFETCH ABORT HANDLER");
}

void __attribute__((interrupt("ABORT"))) data_abort_handler(void) {
  kernel_panic("DATA ABORT HANDLER");
}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_handler(void) {
  kernel_panic("UNDEFINED INSTRUCTION HANDLER");
}

void __attribute__((interrupt("FIQ"))) fast_irq_handler(void) {
  kernel_panic("FIQ HANDLER");
}