#include "kernel/hardware/timer.h"
#include "kernel/hardware/constants.h"

static volatile timer_registers_t *timer_registers =
    (volatile timer_registers_t *)(PERIPHERAL_BASE + SYSTEM_TIMER_OFFSET);

void timer_clear_irq_pending() { timer_registers->control.timer1_matched = 1; }

void timer_set_timer1(uint32_t usecs) {
  timer_registers->timer1 = timer_registers->counter_low + usecs;
}

void timer_wait_us(uint32_t usecs) {
  uint64_t target = (uint64_t)timer_registers->counter_low +
                    (((uint64_t)timer_registers->counter_high) << 32) + usecs;
  while ((uint64_t)timer_registers->counter_low +
             (((uint64_t)timer_registers->counter_high) << 32) <
         target) {
  }
}
