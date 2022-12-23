#include "user/spinlock.h"
#include "kernel/hardware/atomic.h"
#include "kernel/panic.h"

spinlock_t spinlock_create() {
  kernel_panic("No implementation of `spinlock_create`");
}

void spinlock_acquire(spinlock_t *lock) {
  kernel_panic("No implementation of `spinlock_acquire`");
}

void spinlock_release(spinlock_t *lock) {
  kernel_panic("No implementation of `spinlock_release`");
}
