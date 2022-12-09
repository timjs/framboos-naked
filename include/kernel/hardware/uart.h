#pragma once

#include "shared/strfmt.h"
#include <stdarg.h>

void uart_init();
void uart_putc(unsigned char c);
unsigned char uart_getc();
void uart_puts(const char *str);

#define uart_print(format, ...) print_fmt_via(uart_puts, format, ##__VA_ARGS__);
#define uart_println(format, ...) uart_print(format "\n", ##__VA_ARGS__);

#define uart_log_begin(format, ...)                                            \
  uart_println(">>> " format "...", ##__VA_ARGS__);
#define uart_log_end(format, ...) uart_println("<<< " format, ##__VA_ARGS__);
#define uart_log_info(format, ...) uart_println("::: " format, ##__VA_ARGS__);
#define uart_log_warn(format, ...) uart_println("*** " format, ##__VA_ARGS__);
#define uart_log_error(format, ...) uart_println("!!! " format, ##__VA_ARGS__);
