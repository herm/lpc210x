#ifndef __CONFIG_H__
#define __CONFIG_H__

/********************** Clock *******************/
#define FOSC		TODO
#define PLL_M		1

/********************** GPIO ********************/
/* SPI */
#define spi_mosi    6 /* blue */
#define spi_miso    5 /* orange */
#define spi_sck     4 /* yellow */

/* Custom */




/**************** Do not change ****************/
#define MCLK		(FOSC*PLL_M)
#define APBDIVIDER	1
#define PCLK		(MCLK/APBDIVIDER)
#define MSEL		(PLL_M-1)
#define PSEL		PSEL2

#define MAM_MODE 	2

#define default_PINSEL0 0
#define default_PINSEL1 0
#define default_PIN     0
#define default_DIR     0
#endif
