#ifndef UART_H
#define UART_H

#include "utils.h"
#include "lpc2103.h"

#define txd1 8
#define rxd1 9

class Serial
{
public:
    Serial(int baudrate)
    {
        PINSEL0 = (PINSEL0 & ~(pin_func_mask(txd1)|pin_func_mask(rxd1))) |
                  pin_func(txd1, 1) | pin_func(rxd1, 1);
        FIODIR = (FIODIR & ~pin_mask(rxd1)) | pin_mask(txd1);
        U1FDR = 0; //Disable fractional baudrate
        U1IER = 0; //No interrupts
        U1FCR = FIFO_ENABLE | FIFO_RX_CLEAR | FIFO_TX_CLEAR;
        U1TER = TXEN; //Enable transmitter
        if (baudrate) baud(baudrate); else autobaud();
    }

    force_inline void baud(int baudrate)
    {
        U1LCR = DLAB;
#warning "Baudrate calculation not implemented!"
        U1LCR = UART_8BIT;
    }

    void autobaud()
    {
        U1ACR = AUTOBAUD_END_IRQ | AUTOBAUD_TIMEOUT_IRQ;
        U1ACR = AUTOBAUD_START;
        while (U1ACR);
    }

    void putc(uint8_t c)
    {
        while (!(U1LSR & THRE)) ;
        U1THR = c;
    }

    void print(const char *str)
    {
        while (*str) { putc(*str++); }
    }

    uint8_t getc()
    {
        while (!(U1LSR & RDR)) ;
        return U1RBR;
    }

};

#endif // UART_H
