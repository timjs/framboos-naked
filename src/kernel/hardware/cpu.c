#include "kernel/hardware/cpu.h"
#include "kernel/hardware/uart.h"

void uart_log_cpu_state(saved_cpu_state_t *state) {
  uart_log_info("r0 = 0x%x", state->r0);
  uart_log_info("r1 = 0x%x", state->r1);
  uart_log_info("r2 = 0x%x", state->r2);
  uart_log_info("r3 = 0x%x", state->r3);
  uart_log_info("r4 = 0x%x", state->r4);
  uart_log_info("r5 = 0x%x", state->r5);
  uart_log_info("r6 = 0x%x", state->r6);
  uart_log_info("r7 = 0x%x", state->r7);
  uart_log_info("r8 = 0x%x", state->r8);
  uart_log_info("r9 = 0x%x", state->r9);
  uart_log_info("r10 = 0x%x", state->r10);
  uart_log_info("r11 = 0x%x", state->r11);
  uart_log_info("r12 = 0x%x", state->r12);
  uart_log_info("cpsr = 0x%x", state->cpsr);
  uart_log_info("sp = 0x%x", state->sp);
  uart_log_info("lr = 0x%x", state->lr);
  uart_log_info("pc = 0x%x", state->pc);
}
