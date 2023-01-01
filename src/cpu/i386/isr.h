//
// Created by per on 12/31/22.
//

#ifndef UIAOS_ISR_H
#define UIAOS_ISR_H
#include <stdint.h>
typedef struct registers
{
    uint32_t ds;                  // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;

void init_isr(void(*idt_set_gate)(uint8_t,uint32_t,uint16_t,uint8_t));

// These extern directives let us access the addresses of our ASM ISR handlers.
extern void isr0 ();
extern void isr1 ();
extern void isr2 ();
extern void isr3 ();
extern void isr4 ();
extern void isr5 ();
extern void isr6 ();
extern void isr7 ();
extern void isr8 ();
extern void isr9 ();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

// A few defines to make life a little easier

// Enables registration of callbacks for interrupts or IRQs.
// For IRQs, to ease confusion, use the #defines above as the
// first parameter.
// Note: void* context allow us to pass whatever object into the callback!
typedef void (*isr_t)(registers_t, void* context);
void register_interrupt_handler(uint8_t n, isr_t handler, void* context);

static isr_t interrupt_handlers[256];
static void* interrupt_handlers_contexts[256];

#endif //UIAOS_ISR_H
