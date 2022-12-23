#include "kernel/hardware/memory.h"

void *memset(void *dest, int value, size_t n) {
  uint8_t *ptr = (uint8_t *)dest;
  while (n != 0) {
    n--;
    *ptr = (uint8_t)value;

    ptr++;
  }

  return dest;
}

void *memcpy(void *dest, void *source, size_t n) {
  uint8_t *dest_ptr = (uint8_t *)dest;
  uint8_t *src_ptr = (uint8_t *)source;
  while (n >= 4) {
    n -= 4;
    *(uint32_t *)dest_ptr = *(uint32_t *)src_ptr;

    dest_ptr += 4;
    src_ptr += 4;
  }

  while (n != 0) {
    n--;
    *dest_ptr = *src_ptr;

    dest_ptr++;
    src_ptr++;
  }

  return dest;
}
