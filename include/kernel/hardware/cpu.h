#pragma once

#include <stdint.h>

typedef struct {
  uint32_t cpsr;
  uint32_t pc;
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r4;
  uint32_t r5;
  uint32_t r6;
  uint32_t r7;
  uint32_t r8;
  uint32_t r9;
  uint32_t r10;
  uint32_t r11;
  uint32_t r12;
  uint32_t sp;
  uint32_t lr;
} saved_cpu_state_t;

void uart_log_cpu_state(saved_cpu_state_t *state);

inline int get_current_program_status(void) {
  int res;
  __asm__ volatile("mrs %[res], cpsr" : [res] "=r"(res)::);
  return res;
}

inline void set_current_program_status(int cpsr) {
  __asm__ volatile("msr cpsr, %[cpsr]" : [cpsr] "=r"(cpsr)::);
}
