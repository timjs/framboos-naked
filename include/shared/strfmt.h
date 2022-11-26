#pragma once

#include <stdarg.h>
#include <stddef.h>

const char *strfmt(char *buf, size_t len, const char *format, ...);

typedef void (*print_via_f)(const char *str);
void print_fmt_via(print_via_f via_function, const char *format, ...);
