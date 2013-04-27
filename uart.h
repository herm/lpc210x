#ifndef UART_H
#define UART_H

#include "utils.h"
#include "lpc2103.h"

#define txd0 0
#define rxd0 1
#define txd1 8
#define rxd1 9

class Serial
{
public:
    Serial(lpc_uart &uart, int baudrate):
        uart_(&uart)
    {
        if (uart_ == &lpc_uart0)
        {
            PINSEL0 = (PINSEL0 & ~(pin_func_mask(txd0)|pin_func_mask(rxd0))) |
                    pin_func(txd0, 1) | pin_func(rxd0, 1);
            FIODIR = (FIODIR & ~pin_mask(rxd0)) | pin_mask(txd0);
        } else if (uart_ == &lpc_uart1)
        {
            PINSEL0 = (PINSEL0 & ~(pin_func_mask(txd1)|pin_func_mask(rxd1))) |
                    pin_func(txd1, 1) | pin_func(rxd1, 1);
            FIODIR = (FIODIR & ~pin_mask(rxd1)) | pin_mask(txd1);
        } /*else abort();*/
        uart_->FDR = 0; //Disable fractional baudrate
        uart_->IER = 0; //No interrupts
        uart_->FCR = FIFO_ENABLE | FIFO_RX_CLEAR | FIFO_TX_CLEAR;
        uart_->TER = TXEN; //Enable transmitter
        if (baudrate) baud(baudrate); else autobaud();
    }

    force_inline void baud(int baudrate)
    {
        uart_->LCR = DLAB;
#warning "Baudrate calculation not implemented!"
        uart_->LCR = UART_8BIT;
    }

    void autobaud()
    {
        uart_->ACR = AUTOBAUD_END_IRQ | AUTOBAUD_TIMEOUT_IRQ;
        uart_->ACR = AUTOBAUD_START;
        while (uart_->ACR);
    }

    void putc(uint8_t c)
    {
        while (!(uart_->LSR & THRE)) ;
        uart_->THR = c;
    }

    void print(const char *str)
    {
        while (*str) { putc(*str++); }
    }

    uint8_t getc()
    {
        while (!(uart_->LSR & RDR)) ;
        return uart_->RBR;
    }

    /** LPC only */
    uint_fast16_t get_raw_baudrate()
    {
        uint_fast16_t result;
        uint8_t tmp = uart_->LCR;
        uart_->LCR = DLAB;
        result = uart_->DLM << 8 | uart_->DLL;
        uart_->LCR = tmp;
        return result;
    }

private:
    lpc_uart *uart_;
};

#endif // UART_H
