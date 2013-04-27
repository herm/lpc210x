#ifndef _delay_h_
#define _delay_h_
#include "config.h"
#define TUNE_FAC 0.96154

#include <stdint.h>

#define delay_ms(delayval) delay_us(delayval*1000)
#define delay_us(delayval) delay_us_( (uint32_t)((MCLK)/ (1000000/(delayval)) /4 * TUNE_FAC) )
void delay_us_(uint32_t delayval);
#define nop() asm volatile("nop")
#endif
