#pragma once

#include <stddef.h>
#include <stdint.h>

#define COLOR_DEPTH 24
#define BYTES_PER_PIXEL (COLOR_DEPTH / 8)
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_PITCH (SCREEN_WIDTH * BYTES_PER_PIXEL)
#define SCREEN_BYTES (SCREEN_WIDTH * SCREEN_HEIGHT * BYTES_PER_PIXEL)
#define FRAME_TIME_US (66 * 1000) // 66ms is more or less 15Hz

typedef struct {
  int width;
  int height;
  uint32_t pitch;
  uint8_t *buf;
  size_t buf_size;
} framebuffer_info_t;

void framebuffer_init(void);
framebuffer_info_t *framebuffer_get_info(void);
