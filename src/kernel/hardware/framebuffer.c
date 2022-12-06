#include "kernel/hardware/framebuffer.h"
#include "kernel/hardware/mailbox.h"
#include "kernel/hardware/uart.h"
#include "kernel/panic.h"

framebuffer_info_t fbinfo = (framebuffer_info_t){
    .width = 0,
    .height = 0,
    .buf = NULL,
    .buf_size = 0,
};

void framebuffer_init(void) {
  uart_log_begin("Initialising framebuffer");
  static uint32_t request[] __attribute__((aligned(16))) = {
      // Header
      0x70, // size
      0x0,  // request/response

      // Set physical dimensions
      0x48003,
      0x8,
      0x0,

      // 1280 x 720
      0x500,
      0x2d0,

      // Set virtual dimensions
      0x48004,
      0x8,
      0x0,

      // 1280 x 720
      0x500,
      0x2d0,

      // Set bits per pixel
      0x48005,
      0x4,
      0x0,

      0x18,

      // Set pixel order
      0x48006,
      0x4,
      0x0,

      0x0, // 0 = BGR, 1 = RGB

      // Allocate buffer
      0x40001,
      0x8,
      0x0,

      // Align = 16
      0x10,
      0x0,

      // Null tag
      0x0,
      0x0,
  };

  mailbox_request(&request);

  if (request[1] != RESPONSE_SUCCESS) {
    kernel_panic("Mailbox communication failed: %x", request[1]);
  }

  uart_log_info("Framebuffer initialised at 0x%x", request[23]);

  fbinfo.width = request[5];
  fbinfo.height = request[6];
  fbinfo.pitch = fbinfo.width * BYTES_PER_PIXEL;

  fbinfo.buf = (uint8_t *)((intptr_t)request[23] & 0x3FFFFFFF);
  fbinfo.buf_size = request[24];

  uart_log_info("Framebuffer has size %u, width %u, and height %u",
                fbinfo.buf_size, fbinfo.width, fbinfo.height);

  uint32_t block_size = 32;
  for (size_t i = 0; i < fbinfo.buf_size; i++) {
    if ((i / fbinfo.pitch / block_size +
         ((i % fbinfo.pitch) / 3 / block_size)) %
            2 ==
        0) {
      fbinfo.buf[i] = 0xEE;
    } else {
      fbinfo.buf[i] = 0xCC;
    }
  }

  uart_log_end("Framebuffer initialised");
}

framebuffer_info_t *framebuffer_get_info(void) { return &fbinfo; }
