//
// Created by Hugo Trippaers on 20/01/2026.
//
#include "log.h"

#ifdef STDIO_USART
int __io_putchar(int ch) {
    while (!LL_USART_IsActiveFlag_TXE(STDIO_USART)) {
    }

    LL_USART_TransmitData8(STDIO_USART, ch);

    return ch;
}
#endif
