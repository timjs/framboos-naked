#include "kernel/hardware/timer.h"
#include "kernel/hardware/constants.h"
#include <stdbool.h>

static volatile timer_registers_t *timer_registers =
    (volatile timer_registers_t *)(PERIPHERAL_BASE + SYSTEM_TIMER_OFFSET);

void timer_clear_irq_pending() { timer_registers->control.timer1_matched = 1; }

void timer_set_timer1(uint32_t usecs) {
  timer_registers->timer1 = timer_registers->counter_low + usecs;
}

uint64_t timer_get_current_time() {
  return (uint64_t)timer_registers->counter_low +
         (((uint64_t)timer_registers->counter_high) << 32);
}

void timer_wait_us(uint32_t usecs) {
  uint64_t target = timer_get_current_time() + usecs;
  while (timer_get_current_time() < target) {
  }
}

void timer_simulate_more_work() {
  uint64_t start = timer_get_current_time();
  uint64_t t = timer_get_current_time();
  while (true) {
    uint64_t next = timer_get_current_time();
    if (next - t >= 4500 || next - start >= 15000) {
      return;
    }

    t = next;
  }
}
