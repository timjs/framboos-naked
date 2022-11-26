#include "kernel/hardware/memory.h"

void memset(void *dest, uint8_t value, size_t n) {
  while (n != 0) {
    n--;
    *(uint8_t *)dest = value;

    dest++;
  }
}
