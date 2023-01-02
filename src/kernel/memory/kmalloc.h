//
// Created by per on 1/2/23.
//

#ifndef UIAOS_KMALLOC_H
#define UIAOS_KMALLOC_H

#include <stdint.h>

namespace UiAOS::Memory{
    int32_t kmalloc_a(int32_t sz);  // page aligned.
    int32_t kmalloc_p(int32_t sz, int32_t *phys); // returns a physical address.
    int32_t kmalloc_ap(int32_t sz, int32_t *phys); // page aligned and returns a physical address.
    int32_t kmalloc(int32_t sz); // vanilla (normal).
}

#endif //UIAOS_KMALLOC_H
