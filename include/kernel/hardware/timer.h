#pragma once

#include <stdint.h>

#define US_PER_MS 1000

typedef struct {
  uint8_t timer0_matched : 1;
  uint8_t timer1_matched : 1;
  uint8_t timer2_matched : 1;
  uint8_t timer3_matched : 1;
  uint32_t reserved : 28;
} timer_control_reg_t;

typedef struct {
  timer_control_reg_t control;
  uint32_t counter_low;
  uint32_t counter_high;
  uint32_t timer0;
  uint32_t timer1;
  uint32_t timer2;
  uint32_t timer3;
} timer_registers_t;

void timer_clear_irq_pending();
void timer_set_timer1(uint32_t usecs);
void timer_wait_us(uint32_t usecs);
