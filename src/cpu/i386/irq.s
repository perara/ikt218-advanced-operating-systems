.intel_syntax noprefix
.extern irq_handler

/*
irq.s
- Contain macro and definitions for the IRQ.

*/


.macro IRQ id, id_remap
    .global irq\id
    irq\id :
        cli
        push 0
        push \id_remap
        jmp irq_common_stub
.endm

IRQ   0,    32
IRQ   1,    33
IRQ   2,    34
IRQ   3,    35
IRQ   4,    36
IRQ   5,    37
IRQ   6,    38
IRQ   7,    39
IRQ   8,    40
IRQ   9,    41
IRQ  10,    42
IRQ  11,    43
IRQ  12,    44
IRQ  13,    45
IRQ  14,    46
IRQ  15,    47


/* ; Common IRQ code. Identical to ISR code except for the 'call' and the 'pop ebx' */
irq_common_stub:
    pusha
    mov ax, ds
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call irq_handler /* irq_handler function (irq.c)
    pop ebx  /* for irq, we pop to the ebx register instead */
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx
    popa
    add esp, 8
    sti
    iret