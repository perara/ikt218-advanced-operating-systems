//
// Created by per on 12/31/22.
//

#ifndef UIAOS_HARDWARE_PORT_H
#define UIAOS_HARDWARE_PORT_H
#include "stdint.h"


#pragma once
#ifdef __cplusplus
extern "C"
{
#endif

void outb(uint16_t port, uint8_t value);
uint8_t inb(uint16_t port);
uint16_t inw(uint16_t port);


#ifdef __cplusplus
}
#endif





#endif //UIAOS_HARDWARE_PORT_H
