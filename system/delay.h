#ifndef _delay_h_
#define _delay_h_
#include "config.h"
#define TUNE_FAC 0.96154

#include <inttypes.h>

#define delay_us(delayval) delay_us_( (uint32_t)( (FOSC*PLL_M) / (1000000/delayval) /4 * TUNE_FAC) ) 
void delay_us_(uint32_t delayval);

#endif
