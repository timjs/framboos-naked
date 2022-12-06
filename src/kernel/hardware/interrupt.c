#include "kernel/hardware/interrupt.h"
#include "kernel/hardware/uart.h"
#include "kernel/panic.h"

// NOTE: Even though this is a null pointer, it actually points to valid memory!
static volatile exception_vector_t *active_exception_vector =
    (exception_vector_t *)0;
static volatile interrupt_registers_t *interrupt_registers =
    (interrupt_registers_t *)INTERRUPTS_PENDING;

#define STACK_SIZE (1024 * 256)
static uint8_t irq_stack[STACK_SIZE] = {0};
static uint8_t fiq_stack[STACK_SIZE] = {0};

extern void setup_interrupt_stacks(void *fiq_stack, void *irq_stack);

bool irq_is_pending(interrupt_id_t id) {
  switch (id.group) {
  case SHARED1:
    return (interrupt_registers->irq_gpu_pending1 & (1 << id.index)) > 0;
  case SHARED2:
    return (interrupt_registers->irq_gpu_pending2 & (1 << id.index)) > 0;
  case BASIC:
    // Basic only has interrupts 0..7
    if (id.index >= 8) {
      return false;
    }

    return (interrupt_registers->irq_basic_pending & (1 << id.index)) > 0;
  default:
    kernel_panic("Interrupt id with group=%u is not valid", id.group);
  }
}

void interrupt_enable(interrupt_id_t id) {
  switch (id.group) {
  case SHARED1:
    interrupt_registers->irq_gpu_enable1 |= 1 << id.index;
    break;
  case SHARED2:
    interrupt_registers->irq_gpu_enable2 |= 1 << id.index;
    break;
  case BASIC:
    interrupt_registers->irq_basic_enable |= 1 << id.index;
    break;
  default:
    kernel_panic("Interrupt id with group=%u is not valid", id.group);
  }
}

void interrupt_init() {
  uart_log_begin("Initialising interrupts");

  // Make sure all interrupts are disabled
  interrupt_registers->irq_basic_disable = 0xffffffff;
  interrupt_registers->irq_gpu_disable1 = 0xffffffff;
  interrupt_registers->irq_gpu_disable2 = 0xffffffff;

  // Move the exception vector to address 0x00000000
  *active_exception_vector = exception_vector_data;

  // Enable the IRQ exception
  interrupts_enable();

  uart_log_info("Setting up interrupt stacks at 0x%x and 0x%x",
                &irq_stack[STACK_SIZE], &fiq_stack[STACK_SIZE]);
  setup_interrupt_stacks(&irq_stack[STACK_SIZE], &fiq_stack[STACK_SIZE]);

  uart_log_end("Interrupts initialised");
}