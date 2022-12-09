#include "kernel/hardware/mailbox.h"
#include "kernel/hardware/constants.h"
#include <stddef.h>
#include <stdint.h>

#define MAILBOX_BASE PERIPHERAL_BASE + MAILBOX_OFFSET
#define MAIL0_READ (((volatile mail_message_t *)(0x00 + MAILBOX_BASE)))
#define MAIL0_STATUS (((volatile mail_status_t *)(0x18 + MAILBOX_BASE)))
#define MAIL0_WRITE (((volatile mail_message_t *)(0x20 + MAILBOX_BASE)))
#define PROPERTY_CHANNEL 8
#define FRAMEBUFFER_CHANNEL 1

typedef struct {
  uint8_t channel : 4;
  uint32_t data : 28;
} mail_message_t;

typedef struct {
  uint32_t reserved : 30;
  uint8_t empty : 1;
  uint8_t full : 1;
} mail_status_t;

static mail_message_t receive(int channel) {
  mail_status_t status;
  mail_message_t result;

  // Make sure that the message is from the right channel
  do {
    // Make sure there is mail to receive
    do {
      status = *MAIL0_STATUS;
    } while (status.empty);

    // Get the message
    result = *MAIL0_READ;
  } while (result.channel != channel);

  return result;
}

static void send(mail_message_t msg) {
  mail_status_t status;

  // Make sure you can send mail
  do {
    status = *MAIL0_STATUS;
  } while (status.full);

  // Write the message in the mailbox
  *MAIL0_WRITE = msg;
}

void mailbox_request(void *data) {
  // Prepare the message
  mail_message_t mail;
  mail.channel = PROPERTY_CHANNEL;
  mail.data = ((size_t)data) >> 4;

  // Send the message
  send(mail);
  // Receive the answer
  mail = receive(PROPERTY_CHANNEL);
}
