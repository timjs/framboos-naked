.section ".text"

.global exception_vector_data

exception_vector_data:
    ldr pc, reset_handler_abs_addr
    ldr pc, undefined_instruction_handler_abs_addr
    ldr pc, software_interrupt_handler_abs_addr
    ldr pc, prefetch_abort_handler_abs_addr
    ldr pc, data_abort_handler_abs_addr
    nop // reserved
    ldr pc, irq_handler_abs_addr
    ldr pc, fast_irq_handler_abs_addr

reset_handler_abs_addr:                 .word reset_handler
undefined_instruction_handler_abs_addr: .word undefined_instruction_handler
software_interrupt_handler_abs_addr:    .word swi_handler_asm_wrapper
prefetch_abort_handler_abs_addr:        .word prefetch_abort_handler
data_abort_handler_abs_addr:            .word data_abort_handler
irq_handler_abs_addr:                   .word irq_handler_asm_wrapper
fast_irq_handler_abs_addr:              .word fast_irq_handler

irq_handler_asm_wrapper:
    sub     sp, #128
    stm     sp, {r0-lr}^
    mrs     r0, spsr
    sub     lr, #4
    push    {r0,lr}

    mov     r0, sp

    and     r1, sp, #4
    sub     sp, sp, r1

    push    {r1}
    bl      irq_handler
    pop     {r1}
    add     sp, sp, r1

    pop     {r0,lr}
    msr     spsr_cxsf, r0
    ldm     sp, {r0-lr}^
    add     sp, #128
    cpsie i
    nop
    movs    pc, lr

swi_handler_asm_wrapper:
    sub     sp, #128
    stm     sp, {r0-lr}^
    mrs     r0, spsr
    push    {r0,lr}

    mov     r0, sp

    and     r1, sp, #4
    sub     sp, sp, r1

    push    {r1}
    bl      swi_handler
    pop     {r1}
    add     sp, sp, r1

    pop     {r0,lr}
    msr     spsr_cxsf, r0
    ldm     sp, {r0-lr}^
    add     sp, #128
    cpsie i
    nop
    movs    pc, lr

.global setup_interrupt_stacks
setup_interrupt_stacks:
    push    {r0-r12}
    mov     r7, sp
    mrs     r4, cpsr
    # FIQ mode
    mov     r5, #0xD1
    # IRQ mode
    mov     r6, #0xD2

    msr     cpsr_c, r5
    mov     sp, r0
    msr     cpsr_c, r6
    mov     sp, r1
    msr     cpsr_c, r4

    mov     sp, r7

    pop     {r0-r12}
    bx      lr
