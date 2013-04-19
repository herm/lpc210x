#include "config.h"
#include "../lpc2103.h"
#include "system.h"

void system_init(void)
{
#if APBDIVIDER == 1
    APBDIV = APBDIV1;
#else
#error Unkown APB divider
#endif

#if MCLK > 40000000
    MAMTIM = 3;
#elif MCLK > 20000000
    MAMTIM = 2;
#else
    MAMTIM = 1;
#endif
#if MAM_MODE != 0
    MAMCR = MAM_MODE;
#endif

#if PLL_M != 1
    PLLCFG = MSEL | PSEL; //defined in config.h
    PLLCON = PLLE;
    PLLFEED = PLL_FEED1;
    PLLFEED = PLL_FEED2;
    while (!(PLLSTAT & PLOCK)); //wait for lock
    PLLCON = PLLE | PLLC;
    PLLFEED = PLL_FEED1;
    PLLFEED = PLL_FEED2;
#endif

#if defined(RAM_RUN)
    MEMMAP = MEMMAP_USER_RAM_MODE;
#elif defined(ROM_RUN)
    MEMMAP = MEMMAP_USER_FLASH_MODE;
#else
#error RUN_MODE not defined!
#endif
    SCS = GPIO0M; //Fast GPIO
#if default_PINSEL0 != 0
    PINSEL0 = default_PINSEL0;
#endif
#if default_PINSEL1 != 0
    PINSEL1 = default_PINSEL1;
#endif
#if default_DIR != 0
    FIODIR  = default_DIR;
#endif
#if default_PIN != 0
    FIOPIN  = default_PIN;
#endif
}
