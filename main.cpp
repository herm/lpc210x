/******************************************************************************/
/*  LPC2101 base project                                                      */
/*  Thanks to Martin Thomas for some code samples                             */
/*  (http://www.siwawi.arubi.uni-kl.de/arm_project                            */
/******************************************************************************/

//extern "C"
//{
#include "../lpc2103.h"
#include "config.h"
#include "vic.h"
#include "system.h"
#include <inttypes.h>
//}

uint16_t global_array[123];
int main(void)
{
	gpio_init();
	system_init();
	enableIRQ();
    for (;;) {
        global_array[0]++;
	}
}
