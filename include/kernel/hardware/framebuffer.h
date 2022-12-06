#pragma once

#include <stddef.h>
#include <stdint.h>

#define COLORDEPTH 24
#define BYTES_PER_PIXEL COLORDEPTH / 8

typedef struct {
  int width;
  int height;
  uint32_t pitch;
  uint8_t *buf;
  size_t buf_size;
} framebuffer_info_t;

void framebuffer_init(void);
framebuffer_info_t *framebuffer_get_info(void);