#pragma once

#include "kernel/hardware/framebuffer.h"
#include <stddef.h>
#include <stdint.h>

typedef struct {
  uint32_t x;
  uint32_t y;
} point_t;

typedef struct {
  uint32_t width;
  uint32_t height;
} size2d_t;

typedef struct {
  point_t topleft;
  size2d_t size;
} area_t;

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} color_t;

void draw_pixel(framebuffer_info_t *fb, point_t position, color_t color);
void draw_rectangle(framebuffer_info_t *fb, area_t area, color_t color);
void draw_character(framebuffer_info_t *fb, point_t position, color_t color,
                    char c);
void draw_string(framebuffer_info_t *fb, point_t position, color_t color,
                 const char *str);

#define color_red                                                              \
  (color_t) { .red = 0xFF, .blue = 0x00, .green = 0x00 }
#define color_blue                                                             \
  (color_t) { .red = 0x00, .blue = 0xFF, .green = 0x00 }
#define color_green                                                            \
  (color_t) { .red = 0x00, .blue = 0x00, .green = 0xFF }
#define color_cyan                                                             \
  (color_t) { .red = 0x00, .blue = 0xFF, .green = 0xFF }
#define color_magenta                                                          \
  (color_t) { .red = 0xFF, .blue = 0xFF, .green = 0x00 }
#define color_yellow                                                           \
  (color_t) { .red = 0xFF, .blue = 0x00, .green = 0xFF }
#define color_white                                                            \
  (color_t) { .red = 0xFF, .blue = 0xFF, .green = 0xFF }
#define color_black                                                            \
  (color_t) { .red = 0x00, .blue = 0x00, .green = 0x00 }
