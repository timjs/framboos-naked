/*
 * Atomic operations
 */
#pragma once

#include <stdbool.h>
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
 * Compare the value in <ptr> to <expected_value>.
 * If equal, stores <new_value> in <ptr> and returns true.
 * Otherwise, does not modify the value in <ptr> and returns false.
 */
static inline bool atomic_compare_exchange(uint32_t *ptr,
                                           uint32_t expected_value,
                                           uint32_t new_value) {
  return __atomic_compare_exchange_n(ptr, &expected_value, new_value, false,
                                     __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}
