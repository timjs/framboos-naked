#pragma once

#include <stddef.h>
#include <stdint.h>

static inline void mmio_write(uint32_t reg, uint32_t data) {
  *(volatile uint32_t *)reg = data;
}

static inline uint32_t mmio_read(uint32_t reg) {
  return *(volatile uint32_t *)reg;
}

// Memset/cpy

void *memset(void *dest, int value, size_t n);
void *memcpy(void *dest, void *source, size_t n);

static inline void volatile_memcpy(volatile void *dest, volatile void *source,
                                   size_t n) {
  while (n != 0) {
    n--;
    *(volatile uint8_t *)dest = *(volatile uint8_t *)source;

    dest++;
    source++;
  }
}
