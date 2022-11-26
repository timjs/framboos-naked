#pragma once

#include "kernel/task.h"
#include <stddef.h>
#include <stdint.h>

#define MAX_TASKS 1024

void scheduler_start();
size_t scheduler_task_add(char *task_name, task_main_f f, void *stack_pointer);
void scheduler_task_remove(size_t tid);
void scheduler_task_switch(saved_cpu_state_t *saved_state);
task_t *scheduler_current_task();
