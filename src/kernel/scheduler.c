#include "kernel/scheduler.h"
#include "kernel/hardware/cpu.h"
#include "kernel/hardware/interrupt.h"
#include "kernel/hardware/memory.h"
#include "kernel/hardware/timer.h"
#include "kernel/hardware/uart.h"
#include "kernel/panic.h"

#define TIME_QUANTUM 5000

/** File global state *********************************************************/

// The array containing the information of all running and terminated tasks.
// The whole piece of memory is initialised with 0.
static task_t tasks[MAX_TASKS] = {0};
// The `current_task_index` represents the index into the `tasks` array.
// The init task will be placed at index 0.
static tid_t current_task_index = 0;
// A counter for the next task identifier.
// The init task will have tid #1.
static tid_t next_tid = 1;

/** Helpers *******************************************************************/

// Returns the next in use task after the current one.
// Wraps around to 0 after reaching the end of the array.
tid_t find_next_active_task() {

  kernel_panic("There are no running tasks");
}

// Returns the index of the lowest free task slot in the `tasks` array.
tid_t find_first_inactive_slot() {

  kernel_panic("There are no free task slots left");
}

// Is called when a task terminates.
void terminate_current_task() {

  while (true) {
  }
}

/** Adding and removing *******************************************************/

// Spawns a new task.
tid_t scheduler_task_add(char *task_name, task_main_f f, void *stack_pointer) {
  tid_t new_index = find_first_inactive_slot();
  tid_t tid = next_tid++;
  tasks[new_index] = (task_t){
      .tid = tid,
      .in_use = true,
      .task_name = task_name,
      .saved_state =
          (saved_cpu_state_t){
              .sp = (size_t)stack_pointer,
              .pc = (size_t)(void *)f,
              .lr = (size_t)(void *)terminate_current_task,
              .cpsr = get_current_program_status() & ~0xf,
          },
  };

  uart_log_info("Scheduled task '%s' with tid #%u at index %u with sp=0x%x",
                task_name, tid, new_index, stack_pointer);

  return new_index;
}

// Removes a task by setting it to unused.
void scheduler_task_remove(tid_t tid) {
  uart_log_info("Could not find and remove task #%u", tid);
}

// Returns the current running task.
task_t *scheduler_current_task() {
}

/** Scheduling ****************************************************************/

// Put the `init` task in the zeroth slot of the `tasks` array.
void scheduler_init() {
  uart_log_begin("Setting up init task");
  tid_t new_index = find_first_inactive_slot();
  tid_t tid = next_tid++;
  tasks[new_index] = (task_t){
      .task_name = "<init task>",
      .tid = tid,
      .saved_state = {0},
      .in_use = true,
  };
}

void scheduler_start() {
  uart_log_begin("Enabling system timer interrupts");
  interrupt_enable(INTERRUPT_SYSTEM_TIMER_1);
  uart_log_begin("Starting system timer for scheduling");
  timer_set_timer1(TIME_QUANTUM);
  while (true) {
  }
}

// Switch the running task, by modifying the CPU state in 'saved_state'.
void scheduler_task_switch(saved_cpu_state_t *last_state) {
}
