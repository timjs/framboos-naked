/*
 * Constants for Raspberry Pi 2 model B
 */
#pragma once

#define MEMORY_SIZE (1024 * 1024 * 128) // 128 MiB
#define PAGE_SIZE 4096                  // 4 KiB
#define PAGE_COUNT (MEMORY_SIZE / PAGE_SIZE)

#define PERIPHERAL_BASE 0x3F000000
#define PERIPHERAL_LENGTH 0x01000000

#define SYSTEM_TIMER_OFFSET 0x3000
#define MAILBOX_OFFSET 0xB880
#define INTERRUPTS_OFFSET 0xB000
#define UART0_OFFSET 0x201000
#define GPIO_OFFSET 0x200000
