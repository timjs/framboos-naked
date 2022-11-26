/*
 * Atomic operations
 */
#pragma once

#include <stdint.h>

/*
 * Loop <delay> times in a way that the compiler won't optimize away
 */
static inline void delay(int32_t count) {
  __asm__ volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
                   : "=r"(count)
                   : [count] "0"(count)
                   : "cc");
}

/*
 * Atomically swap two variables
 *
 * FIXME: use LDREX and STREX instead of SWP
 */
static inline int32_t atomic_swap(uint32_t *ptr, uint32_t new_value) {
  int32_t old_value;
  __asm__ volatile("swp %[old_value], %[new_value], [%[ptr]]"
                   : [old_value] "=r"(old_value)
                   : [new_value] "r"(new_value), [ptr] "r"(ptr)
                   :);

  return old_value;
}
