#pragma once

#include "shared/strfmt.h"
#include <stdbool.h>
#include <stdint.h>

#define kernel_panic(format, ...)                                              \
  print_fmt_via(kernel_panic_implementation,                                   \
                "KERNEL PANIC\n    %s:%u:%s\n    " format, __FILE__, __LINE__, \
                __func__, ##__VA_ARGS__);

void kernel_panic_implementation(const char *message);