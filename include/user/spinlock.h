#pragma once

#include <stdint.h>

typedef struct {
  uint32_t value;
} spinlock_t;

spinlock_t spinlock_create();

void spinlock_acquire(spinlock_t *lock);
void spinlock_release(spinlock_t *lock);
