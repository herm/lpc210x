#ifndef __CONFIG_H__
#define __CONFIG_H__

//Enable PLL and MAM
#define PLL
#define MAM

/* osc freq */
#define FOSC		SET_CORRECT_VALUE
#define APBDIVIDER	1

#define PLL_M		1
#define PSEL		PSEL2

#if PLL_M == 1
#undef PLL
#endif

#ifdef PLL
#define MCLK		(FOSC*PLL_M)
#else
#define MCLK		FOSC
#endif

#define PCLK		(MCLK/APBDIVIDER)
#define MSEL		(PLL_M-1)

/*
    MAM(Memory Accelerator Module)
    - choosen: MAM fully enabled = MAM-Mode 2
    - System-Clock cclk=64MHz -> 3 CCLKs are proposed as fetch timing
*/
#define MAM_MODE 	2
#define MAM_FETCH   3

/* GPIO */


#define pin_func(pin, function) ((function) << (((pin) & 0x0f)*2))
#define default_PINSEL0 0
#define default_PINSEL1 0
#define default_PIN     SET_AT_LEAST_ONE_OUTPUT
#define default_DIR     0
#endif
