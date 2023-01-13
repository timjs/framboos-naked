#include "user/alloc.h"
#include "kernel/hardware/memory.h"
#include "kernel/hardware/uart.h"
#include "kernel/panic.h"

#define assert(cond, msg, ...)                                                 \
  if (!(cond)) {                                                               \
    kernel_panic(msg, ##__VA_ARGS__);                                          \
  }
#define assert_eq(lhs, rhs, msg, ...)                                          \
  if (lhs != rhs) {                                                            \
    kernel_panic(msg, ##__VA_ARGS__);                                          \
  }
#define TEST_BLOCK_SIZE (16 * 1024)

bool overlaps(void *lhs_ptr, size_t lhs_size, void *rhs_ptr, size_t rhs_size) {
  return !((intptr_t)lhs_ptr + (intptr_t)lhs_size <= (intptr_t)rhs_ptr ||
           (intptr_t)lhs_ptr >= (intptr_t)rhs_ptr + (intptr_t)rhs_size);
}

void test_memory_alignment() {
  assert_eq((intptr_t)malloc(11) % 4, 0,
            "malloc must return a pointer aligned to 4 bytes");
  assert_eq((intptr_t)malloc(7) % 4, 0,
            "malloc must return a pointer aligned to 4 bytes");
  assert_eq((intptr_t)malloc(3) % 4, 0,
            "malloc must return a pointer aligned to 4 bytes");
  assert_eq((intptr_t)malloc(128) % 4, 0,
            "malloc must return a pointer aligned to 4 bytes");
  assert_eq((intptr_t)malloc(77) % 4, 0,
            "malloc must return a pointer aligned to 4 bytes");
  assert_eq((intptr_t)malloc(5) % 4, 0,
            "malloc must return a pointer aligned to 4 bytes");
  assert_eq((intptr_t)malloc(0) % 4, 0,
            "malloc must return a pointer aligned to 4 bytes");
  assert_eq((intptr_t)malloc(50) % 4, 0,
            "malloc must return a pointer aligned to 4 bytes");
}

void test_unique_memory() {
  void *a = malloc(16);
  void *b = malloc(24);
  void *c = malloc(8);
  void *d = malloc(4);
  void *e = malloc(0);

  assert(!overlaps(a, 16, b, 24),
         "allocated memory areas must not overlap: malloc returned 0x%x with "
         "size %u and 0x%x with size %u",
         a, 16, b, 24);
  assert(!overlaps(a, 16, c, 8), "allocated memory areas must not overlap");
  assert(!overlaps(a, 16, d, 4), "allocated memory areas must not overlap");

  assert(!overlaps(b, 24, c, 8), "allocated memory areas must not overlap");
  assert(!overlaps(b, 24, d, 4), "allocated memory areas must not overlap");

  assert(!overlaps(c, 8, d, 4), "allocated memory areas must not overlap");

  // If you see a crash here, something is probably wrong with your
  // implementation of void free(..).
  free(d);
  free(e);
  free(a);
  free(c);
  free(b);
}

void test_memory_write() {
  void *a = malloc(16);
  void *b = malloc(21);
  memset(a, 0xCC, 16);
  memset(b, 0xDD, 21);

  // If this crashes, your headers are somehow overlapping your memory areas. Or
  // maybe the size you're calculating is not correct.
  free(a);
  free(b);
}

void test_out_of_memory() {
  assert_eq(NULL, malloc(0x7fffffff),
            "malloc must return NULL if requested size is too big");

  bool returned_null = false;
  uart_log_begin("Filling entire memory...");
  for (int i = 0; i < 0x7fffffff / 1024; i++) {
    if (malloc(TEST_BLOCK_SIZE) == NULL) {
      returned_null = true;
      break;
    }
  }
  uart_log_end("Memory filled");

  assert(returned_null, "malloc must return NULL if it runs out of memory");
}

void test_merging_free() {
  void *allocations[10] = {NULL};

  // First we fill the entire memory with blocks of 1024 bytes.
  uart_log_begin("Filling entire memory...");
  for (int n = 0;; n++) {
    void *area = malloc(TEST_BLOCK_SIZE);
    if (n >= 150 && n < 160) {
      allocations[n - 150] = area;
    }

    if (area == NULL) {
      break;
    }
  }

  uart_log_end("Memory filled");

  // Now we will free some blocks in different orders and check if we can
  // re-allocate the total size again Test #1: Free block N, then N-1
  free(allocations[1]);
  free(allocations[0]);

  assert(malloc(2 * TEST_BLOCK_SIZE) != NULL,
         "freeing block N, then freeing block N-1, then allocating a block "
         "with the size of both blocks fails");

  // This should always fail because we filled the entire memory, then freed 2
  // blocks, then allocated 1 block the size of both blocks again.
  assert_eq(malloc(TEST_BLOCK_SIZE), NULL, "memory appeared out of thin air");

  // Test #2: Free block N, then N+1
  free(allocations[2]);
  free(allocations[3]);
  assert(malloc(2 * TEST_BLOCK_SIZE) != NULL,
         "freeing block N, then freeing block N+1, then allocating a block "
         "with the size of both blocks fails");

  // This should always fail because we filled the entire memory, then freed 2
  // blocks, then allocated 1 block the size of both blocks again.
  assert_eq(malloc(TEST_BLOCK_SIZE), NULL, "memory appeared out of thin air");

  // Test #3: Free block N, then N+2, then N+1
  free(allocations[4]);
  free(allocations[6]);

  // This should always fail because the blocks cannot be merged if they are not
  // next to eachother
  assert_eq(malloc(2 * TEST_BLOCK_SIZE), NULL,
            "memory appeared out of thin air");

  free(allocations[5]);
  assert(malloc(3 * TEST_BLOCK_SIZE) != NULL,
         "freeing block N, then freeing block N+2, then freeing block N+1, "
         "then allocating a block with the size of all 3 blocks fails");

  // Test #4: Free block N, then N-2, then N-1
  free(allocations[9]);
  free(allocations[7]);

  // This should always fail because the blocks cannot be merged if they are not
  // next to eachother
  assert_eq(malloc(2 * TEST_BLOCK_SIZE), NULL,
            "memory appeared out of thin air");

  free(allocations[8]);
  assert(malloc(3 * TEST_BLOCK_SIZE) != NULL,
         "freeing block N, then freeing block N-2, then freeing block N-1, "
         "then allocating a block with the size of all 3 blocks fails");
}

void alloc_test() {
  malloc_init();
  uart_log_begin("Running test_memory_alignment...");
  test_memory_alignment();

  malloc_init();
  uart_log_begin("Running test_unique_memory...");
  test_unique_memory();

  malloc_init();
  uart_log_begin("Running test_memory_write...");
  test_memory_write();

  malloc_init();
  uart_log_begin("Running test_out_of_memory...");
  test_out_of_memory();

  malloc_init();
  uart_log_begin("Running test_merging_free...");
  test_merging_free();
}
