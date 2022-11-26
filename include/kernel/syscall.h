#pragma once

#include <stdint.h>

static inline intptr_t _syscall0(uint32_t num) {
  register uint32_t r0 __asm__("r0") = num;
  __asm__ volatile("svc #0" : "+r"(r0) : "r"(r0) : "memory");

  return r0;
}

static inline intptr_t _syscall1(uint32_t num, uint32_t arg0) {
  register uint32_t r0 __asm__("r0") = num;
  register uint32_t r1 __asm__("r1") = arg0;
  __asm__ volatile("svc #0" : "+r"(r0) : "r"(r0), "r"(r1) : "memory");

  return r0;
}

static inline intptr_t _syscall2(uint32_t num, uint32_t arg0, uint32_t arg1) {
  register uint32_t r0 __asm__("r0") = num;
  register uint32_t r1 __asm__("r1") = arg0;
  register uint32_t r2 __asm__("r2") = arg1;
  __asm__ volatile("svc #0" : "+r"(r0) : "r"(r0), "r"(r1), "r"(r2) : "memory");

  return r0;
}
