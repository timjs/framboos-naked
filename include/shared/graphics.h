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

void draw_pixel(framebuffer_info_t *fb, point_t point, color_t color);
void draw_rectangle(framebuffer_info_t *fb, area_t area, color_t color);
void draw_character(framebuffer_info_t *fb, point_t pos, color_t col, char c);
void draw_string(framebuffer_info_t *fb, point_t pos, color_t col,
                 const char *str);