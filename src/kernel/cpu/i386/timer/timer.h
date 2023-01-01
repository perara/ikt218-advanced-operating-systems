//
// Created by per on 1/1/23.
//

#ifndef UIAOS_TIMER_H
#define UIAOS_TIMER_H
#include <stdint.h>

void init_timer(uint32_t freq, isr_t handler, void* context);

#endif //UIAOS_TIMER_H
