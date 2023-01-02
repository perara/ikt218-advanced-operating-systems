//
// Created by per on 12/31/22.
//

#ifndef UIAOS_UIASTDLIB_H
#define UIAOS_UIASTDLIB_H

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))


void itoa(int n, char s[]);

#endif //UIAOS_UIASTDLIB_H
