#include "kernel/hardware/uart.h"
#include "kernel/panic.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// The linker script places this symbol at the very end of the binary.
// All (available) memory starting at this symbol is freely usable by us.
extern uint8_t __kernel_end;

// We're going to build a linked list of memory blocks.
// Each block will have a header that contains the size of the block,
// a pointer to the next block, and a boolean indicating whether the block is
// allocated.
typedef struct alloc_header_t alloc_header_t;
struct alloc_header_t {
};

// Returns the first allocation header in memory.
alloc_header_t *first_alloc_header() { return (alloc_header_t *)&__kernel_end; }

// Shifts a pointer to a memory header to point to the data block after it.
void *header_to_dataptr(alloc_header_t *header) {
  // We'll locate the data right after the header.
  return (void *)(((uint8_t *)header) + sizeof(alloc_header_t));
}

// Shifts a pointer to a data block to the memory header before it.
alloc_header_t *dataptr_to_header(void *data) {
  return (alloc_header_t *)(((uint8_t *)data) - sizeof(alloc_header_t));
}

// Calculates the starting address of the remainder of a memory `hole` when
// allocating `rounded_size` bytes. Checks if `rounded_size` is a multiple of 4
// bytes and returns a new allocation header.
alloc_header_t *start_of_new_hole(alloc_header_t *hole, size_t rounded_size) {
  if (rounded_size % 4 != 0) {
    kernel_panic("Size of allocated memory block is not multiple of 4: %u",
                 rounded_size);
  }
  return (alloc_header_t *)(((uint8_t *)header_to_dataptr(hole)) +
                            rounded_size);
}

// We need to initialise the first block before we use it.
// We'll start with one big, unused, block of 16 MiB of memory.
void malloc_init() {
  kernel_panic("No implementation of `malloc_init`");
}

// Allocates a memory area of at least the requested `size`, and returns a
// pointer to it.
void *malloc(size_t size) {
  // ARM requires aligned memory accesses. Our headers are already a nice round
  // 12 bytes in size. To make sure we always have the headers aligned nicely,
  // we're going to allocate multiples of 4 bytes. If we're requested to
  // allocate something that isn't a multiple of 4, we'll round it up to the
  // nearest multiple.
  size_t rounded_size = (size + 3) / 4 * 4;

  kernel_panic("No implementation of `malloc`");
}

void free(void *data) {
  kernel_panic("No implementation of `free`");
}
