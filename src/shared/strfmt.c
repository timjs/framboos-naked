#include "shared/strfmt.h"
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

#define STRFMT_ADD_CHAR(c)                                                     \
  if (bufptr < bufLen - 1) {                                                   \
    buf[bufptr++] = c;                                                         \
  } else {                                                                     \
    buf[bufLen - 1] = '\0';                                                    \
    return buf;                                                                \
  }
const char *vstrfmt(char *buf, const size_t bufLen, const char *format,
                    va_list argp) {
  bool inSpecifier = false;
  unsigned int bufptr = 0;
  if (buf == NULL || bufLen == 0) {
    return NULL;
  }
  if (format == NULL) {
    buf[0] = '\0';
    return buf;
  }
  while (*format != '\0') {
    if (inSpecifier) {
      if (*format == 'x') {
        const unsigned int num = va_arg(argp, unsigned int);
        unsigned int nibblesCount = 0;
        while ((1U << (4 * nibblesCount)) <= num) {
          nibblesCount++;
          if ((1U << (4 * nibblesCount)) > UINT_MAX >> 4U) {
            nibblesCount++;
            break;
          }
        }
        if (nibblesCount == 0) {
          STRFMT_ADD_CHAR('0');
        } else {
          unsigned int i = 0;
          for (i = 0; i < nibblesCount; i++) {
            STRFMT_ADD_CHAR(
                "0123456789abcdef"[(num >> (4 * (nibblesCount - i - 1))) &
                                   0xfU]);
          }
        }
      } else if (*format == 'u' || *format == 'd') {
        unsigned int num;
        bool sign = false;
        if (*format == 'd') {
          int signed_num = va_arg(argp, int);
          if (signed_num < 0) {
            num = (uint32_t)-signed_num;
            sign = true;
          } else {
            num = (uint32_t)signed_num;
          }
        } else {
          num = va_arg(argp, unsigned int);
        }

        unsigned int digitCount = 0;
        uint64_t big_k = 1;
        while (big_k <= num) {
          digitCount++;
          big_k *= 10;
        }

        // Workaround for big numbers: we didn't implement '__aeabi_uldivmod' so
        // we can't divide here. Instead we just multiply again, but one time
        // less.
        int k = 1;
        for (uint32_t i = 0; digitCount > 0 && i < digitCount - 1; i++) {
          k *= 10;
        }

        if (sign) {
          STRFMT_ADD_CHAR('-');
        }

        if (digitCount == 0) {
          STRFMT_ADD_CHAR('0');
        } else {
          unsigned int i = 0;
          for (i = 0; i < digitCount; i++) {
            STRFMT_ADD_CHAR("0123456789"[(num / k) % 10]);
            k /= 10;
          }
        }
      } else if (*format == 's') {
        char *strptr = va_arg(argp, char *);
        if (strptr != NULL) {
          while (*strptr != '\0') {
            STRFMT_ADD_CHAR(*strptr++);
          }
        }
      } else if (*format == 'c') {
        char c = va_arg(argp, int);
        STRFMT_ADD_CHAR(c);
      } else if (*format == '%') {
        STRFMT_ADD_CHAR('%');
      }
      inSpecifier = false;
    } else if (*format == '%') {
      inSpecifier = true;
    } else {
      STRFMT_ADD_CHAR(*format);
    }
    ++format;
  }
  STRFMT_ADD_CHAR('\0');
  return buf;
}
#undef STRFMT_ADD_CHAR

const char *strfmt(char *buf, const size_t bufLen, const char *format, ...) {
  va_list argp;
  const char *retval = NULL;
  va_start(argp, format);
  retval = vstrfmt(buf, bufLen, format, argp);
  va_end(argp);
  return retval;
}

void print_fmt_via(print_via_f via_function, const char *format, ...) {
  char buffer[1024];

  va_list args;
  va_start(args, format);
  vstrfmt(buffer, 1024, format, args);
  va_end(args);

  via_function(buffer);
}
