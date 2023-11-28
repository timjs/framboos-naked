#include "user/tasks/pong.h"
#include "kernel/hardware/atomic.h"
#include "kernel/hardware/framebuffer.h"
#include "kernel/hardware/memory.h"
#include "kernel/hardware/timer.h"
#include "kernel/hardware/uart.h"
#include "kernel/panic.h"
#include "kernel/scheduler.h"
#include "shared/graphics.h"
#include "shared/math.h"
#include "user/spinlock.h"

#define BALL_SIZE 64
#define PADDLE_HEIGHT 160
#define PADDLE_PADDING 16
#define PADDLE_WIDTH 32

typedef struct {
  int ball_x;
  int ball_y;
  int speed_v;
  int speed_h;
  int left_paddle_y;
  int right_paddle_y;
} pong_state_t;

uint8_t buffer[SCREEN_BYTES] = {0xff};

framebuffer_info_t render_surface = (framebuffer_info_t){
    .width = SCREEN_WIDTH,
    .height = SCREEN_HEIGHT,
    .buf = &buffer[0],
    .buf_size = SCREEN_BYTES,
    .pitch = SCREEN_PITCH,
};


static volatile pong_state_t state = (pong_state_t){
    .ball_x = 100,
    .ball_y = 100,
    .speed_v = -9,
    .speed_h = 7,
    .left_paddle_y = 0,
    .right_paddle_y = 200,
};

void state_tick(volatile pong_state_t *state) {
  // A: Update the position of the ball
  state->ball_x += state->speed_h;
  state->ball_y += state->speed_v;

  // B: Update the position of the paddles
  if (state->speed_h < 0) {
    if (state->ball_y + BALL_SIZE / 2 <
        state->left_paddle_y + PADDLE_HEIGHT / 2) {
      state->left_paddle_y -= 2;
    } else {
      state->left_paddle_y += 2;
    }
  } else {
    if (state->ball_y + BALL_SIZE / 2 <
        state->right_paddle_y + PADDLE_HEIGHT / 2) {
      state->right_paddle_y -= 2;
    } else {
      state->right_paddle_y += 2;
    }
  }

  // This is needed for this exercise
  timer_simulate_more_work();

  // C: Make the ball bounce if it touches the left or right edges of the screen
  if (state->ball_x < 0 || state->ball_x + BALL_SIZE >= SCREEN_WIDTH) {
    state->speed_h *= -1;
  }

  // D: Make the ball bounce if it touches the top or bottom edges of the screen
  if (state->ball_y < 0 || state->ball_y + BALL_SIZE >= SCREEN_HEIGHT) {
    state->speed_v *= -1;
  }

  // E: Make the ball bounce if it touches the left paddle
  if (state->ball_x <= PADDLE_PADDING + PADDLE_WIDTH &&
      state->ball_y + BALL_SIZE >= state->left_paddle_y &&
      state->ball_y < state->left_paddle_y + PADDLE_HEIGHT) {
    state->speed_h *= -1;
    state->ball_x = PADDLE_PADDING + PADDLE_WIDTH;
  }

  // F: Make the ball bounce if it touches the right paddle
  if (state->ball_x + BALL_SIZE >=
          SCREEN_WIDTH - PADDLE_PADDING - PADDLE_WIDTH &&
      state->ball_y + BALL_SIZE >= state->right_paddle_y &&
      state->ball_y < state->right_paddle_y + PADDLE_HEIGHT) {
    state->speed_h *= -1;
    state->ball_x = SCREEN_WIDTH - PADDLE_PADDING - PADDLE_WIDTH - BALL_SIZE;
  }

  // G: Make sure all variables are within the screen bounds
  state->left_paddle_y =
      crop(state->left_paddle_y, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
  state->right_paddle_y =
      crop(state->right_paddle_y, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
  state->ball_x = crop(state->ball_x, 0, SCREEN_WIDTH - BALL_SIZE - 1);
  state->ball_y = crop(state->ball_y, 0, SCREEN_HEIGHT - BALL_SIZE - 1);
}

void state_render(framebuffer_info_t *target_fb, volatile pong_state_t *state) {
  // Just to be sure, we'll verify the game state
  int ball_x = state->ball_x;
  int ball_y = state->ball_y;

  // These three ifs will never happen, right? Because we check for this in the
  // logic loop!
  if (ball_x < 0 || ball_y < 0 || ball_x + BALL_SIZE >= target_fb->width ||
      ball_y + BALL_SIZE >= target_fb->height) {
    kernel_panic("Ball is out of bounds: (%d, %d)-(%d, %d)", ball_x, ball_y,
                 ball_x + BALL_SIZE, ball_y + BALL_SIZE);
  }

  if (state->left_paddle_y < 0 ||
      state->left_paddle_y + PADDLE_HEIGHT >= target_fb->height) {
    kernel_panic("Left paddle is out of bounds: y=%d", state->left_paddle_y);
  }

  if (state->right_paddle_y < 0 ||
      state->right_paddle_y + PADDLE_HEIGHT >= target_fb->height) {
    kernel_panic("Left paddle is out of bounds: y=%d", state->right_paddle_y);
  }

}

void task_pong_tick_loop() {
  uart_log_info("Entering pong loop");

  uint64_t next_update_time = timer_get_current_time();
  while (true) {
    next_update_time += FRAME_TIME_US;

  kernel_panic("No implementation of `task_pong_loop`");

    uint64_t current_time = timer_get_current_time();
    if (current_time < next_update_time) {
      timer_wait_us(next_update_time - current_time);
    }
  }
}


void screensaver_start() {
  uart_log_begin("Starting pong screensaver");

  uint8_t task_pong_tick_stack[4096] __attribute__((aligned(8)));
  scheduler_task_add("pong tick loop", task_pong_tick_loop,
                     task_pong_tick_stack + 4096);

  scheduler_start();
}
