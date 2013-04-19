#include "config.h"
#include "lpc2103.h"
#include "system.h"

void system_init(void)
{
    APBDIV = APBDIV1;
#ifdef PLL
    PLLCFG = MSEL | PSEL; //defined in config.h
    PLLCON = PLLE;
    PLLFEED = PLL_FEED1;
    PLLFEED = PLL_FEED2;
    while (!(PLLSTAT & PLOCK)); //wait for lock
    PLLCON = PLLE | PLLC;
    PLLFEED = PLL_FEED1;
    PLLFEED = PLL_FEED2;
#endif
#ifdef MAM
    MAMTIM = 3;
    MAMCR = 2;
#endif

#if defined(RAM_RUN)
    MEMMAP = MEMMAP_USER_RAM_MODE;
#elif defined(ROM_RUN)
    MEMMAP = MEMMAP_USER_FLASH_MODE;
#else
#error RUN_MODE not defined!
#endif
}

void gpio_init(void)
{
    SCS = GPIO0M;
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
