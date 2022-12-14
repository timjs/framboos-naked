#pragma once

#include "kernel/hardware/cpu.h"
#include <stdbool.h>
#include <stddef.h>

typedef size_t tid_t;

typedef struct {
  saved_cpu_state_t saved_state;
  char *task_name;
  tid_t tid;
  bool in_use;
} task_t;

typedef void (*task_main_f)(void);
typedef void (*task_terminated_f)(void *);
