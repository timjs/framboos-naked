#pragma once

#include "kernel/task.h"

#define MAX_TASKS 1024

tid_t scheduler_task_add(char *task_name, task_main_f f, void *stack_pointer);
void scheduler_task_remove(tid_t tid);
task_t *scheduler_current_task();

void scheduler_init();
void scheduler_start();
void scheduler_task_switch(saved_cpu_state_t *last_state);
