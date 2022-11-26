#pragma once

#include "kernel/hardware/constants.h"
#include "kernel/hardware/cpu.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define INTERRUPTS_BASE (PERIPHERAL_BASE + INTERRUPTS_OFFSET)
#define INTERRUPTS_PENDING (INTERRUPTS_BASE + 0x200)
#define NUM_INTERRUPT_REQUESTS 96
#define NUM_INTERRUPT_REQUESTS_PER_GROUP 32

inline int interrupts_are_enabled(void) {
  return ((get_current_program_status() >> 7) & 1) == 0;
}

inline void interrupts_enable(void) {
  if (!interrupts_are_enabled()) {
    __asm__ volatile("cpsie i");
  }
}

inline void interrupts_disable(void) {
  if (interrupts_are_enabled()) {
    __asm__ volatile("cpsid i");
  }
}

typedef struct {
  size_t data[16];
} exception_vector_t;

extern exception_vector_t exception_vector_data;

typedef struct {
  uint32_t irq_basic_pending;
  uint32_t irq_gpu_pending1;
  uint32_t irq_gpu_pending2;
  uint32_t fiq_control;
  uint32_t irq_gpu_enable1;
  uint32_t irq_gpu_enable2;
  uint32_t irq_basic_enable;
  uint32_t irq_gpu_disable1;
  uint32_t irq_gpu_disable2;
  uint32_t irq_basic_disable;
} interrupt_registers_t;

typedef enum {
  SHARED1 = 0,
  SHARED2 = 1,
  BASIC = 2,
} interrupt_group_t;

typedef struct {
  interrupt_group_t group;
  uint8_t index;
} interrupt_id_t;

#define INTERRUPT_SYSTEM_TIMER_1                                               \
  ((interrupt_id_t){                                                           \
      .group = SHARED1,                                                        \
      .index = 1,                                                              \
  })
#define INTERRUPT_USB_CONTROLLER_ID                                            \
  ((interrupt_id_t){                                                           \
      .group = SHARED1,                                                        \
      .index = 9,                                                              \
  })
#define INTERRUPT_ARM_TIMER_ID                                                 \
  = ((interrupt_id_t){                                                         \
      .group = BASIC,                                                          \
      .index = 0,                                                              \
  });

void interrupt_init();
bool irq_is_pending(interrupt_id_t id);
void interrupt_enable(interrupt_id_t id);
