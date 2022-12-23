#pragma once

#include <stddef.h>

void malloc_init();
void *malloc(size_t size);
void free(void *ptr);
