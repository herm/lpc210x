#ifndef __CONFIG_H__
#define __CONFIG_H__

//Enable PLL and MAM
#define PLL 
#define MAM

/* osc freq */
#define FOSC		10000000
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
#define DCF77_POWER	BIT22
#define DCF77_DATA	BIT10
#define BUTTON		BIT4
#define DEBUG_OUT	BIT6
#define BEEPER      BIT24


#define pin_func(pin, function) ((function) << (((pin) & 0x0f)*2))
#define default_PINSEL0 (pin_func(0, 2)|pin_func(1, 2)|pin_func(3,2)|pin_func(5,2)|pin_func(6,1)|pin_func(7,2)|pin_func(8,2)|pin_func(9,2)|pin_func(13,2))
#define default_PINSEL1 (pin_func(16,2)|pin_func(19,2)|pin_func(20,2)|pin_func(21,2))
#define default_PIN     0x0
#define default_DIR     DCF77_POWER|DEBUG_OUT|BEEPER

/* SPI DEBUG */
#define SPI_BAUDRATE    57553 /*57600 - 0.08%*/
//174 =

/* Timers */
/*
Timer 0
0 L6
1 L8
2 L9
3 interval

Timer 1
0 interval
1 L7
2 L11
3 L12

Timer 2
0 L1
1 L3
2 L5
3 interval

Timer 3
0 L10
1 L2
2 L4
3 interval
*/
#define LED1 T2MR0L
#define LED2 T3MR1L
#define LED3 T2MR1L
#define LED4 T3MR2L
#define LED5 T2MR2L
#define LED6 T0MR0
#define LED7 T1MR1
#define LED8 T0MR1
#define LED9 T0MR2
#define LED10 T3MR0L
#define LED11 T1MR2
#define LED12 T1MR3
#define PWM_FREQ 200 /*Hz*/
#define dcf77_ms(x) (x/5)
#define MAX_DAYS_SYNC 3

#define BLINK_TIME dcf77_ms(1000)

#define TIMER_PRESCALER 3
#define PWM_FS ((int)(PCLK/TIMER_PRESCALER/PWM_FREQ))
#define PWM_REL(x) ((int)((float)(x)*PWM_FS))
#define PWM_ABS(x) (PWM_FS - (x))

extern void debug_putc(char c);
#endif
