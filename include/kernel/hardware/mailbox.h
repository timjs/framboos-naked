#pragma once

typedef enum {
  REQUEST = 0x00000000,
  RESPONSE_SUCCESS = 0x80000000,
  RESPONSE_ERROR = 0x80000001
} buffer_req_res_code_t;

void mailbox_request(void *data);