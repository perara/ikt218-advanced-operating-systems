.intel_syntax noprefix

/*
interrupt.s
 -- Contains interrupt service routine wrappers.
  Inspied by  JamesM's kernel development tutorials.
*/


/* This macro creates a stub for an ISR which does NOT pass it's own error code (adds a dummy errcode byte). */
.macro ISR_NOERRCODE id
    .global isr\id
    isr\id :
        cli /* Disable interrupts */
        push 0 /* Dummy Error Code */
        push \id /* Push the interrupt number */
        jmp isr_common_stub /* Jump to the isr handler code */
.endm

/* This macro creates a stub for an ISR which passes it's own error code.*/
.macro ISR_ERRCODE id
    .global isr\id
    isr\id :
        cli /* Disable interrupts */
        push \id /* Push the interrupt number */
        jmp isr_common_stub /* Jump to the isr handler code */
.endm

/*
; Interrupt Exception Meanings:
; 0: Divide By Zero Exception
; 1: Debug Exception
; 2: Non Maskable Interrupt Exception
; 3: Int 3 Exception
; 4: INTO Exception
; 5: Out of Bounds Exception
; 6: Invalid Opcode Exception
; 7: Coprocessor Not Available Exception
; 8: Double Fault Exception (With Error Code!)
; 9: Coprocessor Segment Overrun Exception
; 10: Bad TSS Exception (With Error Code!)
; 11: Segment Not Present Exception (With Error Code!)
; 12: Stack Fault Exception (With Error Code!)
; 13: General Protection Fault Exception (With Error Code!)
; 14: Page Fault Exception (With Error Code!)
; 15: Reserved Exception
; 16: Floating Point Exception
; 17: Alignment Check Exception
; 18: Machine Check Exception
; 19: Reserved
; 20: Reserved
; 21: Reserved
; 22: Reserved
; 23: Reserved
; 24: Reserved
; 25: Reserved
; 26: Reserved
; 27: Reserved
; 28: Reserved
; 29: Reserved
; 30: Reserved
; 31: Reserved
*/

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE   8
ISR_NOERRCODE 9
ISR_ERRCODE   10
ISR_ERRCODE   11
ISR_ERRCODE   12
ISR_ERRCODE   13
ISR_ERRCODE   14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

.extern isr_handler

/* This is our common ISR stub. It saves the processor state, sets
 up for kernel mode segments, calls the C-level fault handler,
 and finally restores the stack frame. */
isr_common_stub:
    pusha                    /* Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax */

    mov ax, ds               /* Lower 16-bits of eax = ds. */
    push eax                 /* save the data segment descriptor */

    mov ax, 0x10  /* load the kernel data segment descriptor */
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    pop eax        /* reload the original data segment descriptor eax? */
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                     /* Pops edi,esi,ebp... */
    add esp, 8     /* Cleans up the pushed error code and pushed ISR number */
    sti
    iret           /* pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP */
