/* 
   Precise Delay Functions for LPC2100
   Martin Thomas, 11/2004
*/

#include "delay.h"

void delay_us_(uint32_t delayval)
{
    asm volatile (
        "L_LOOPUS_%=: 		\n\t" \
            "subs	%0, %0, #1 	\n\t" \
            "bne	L_LOOPUS_%=	\n\t" \
            :  /* no outputs */ : "r" (delayval)
    );
}
