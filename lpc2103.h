// Processor register mappings for Philips LPC2103. Should also work fine
// for LPC2102 and LPC2101.
//
// Copyright (c) 2006, K9spud LLC.
// http://www.k9spud.com/arm/lpc2103/
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// As a special exception, if other files instantiate templates or
// use macros or inline functions from this file, or you compile this
// file and link it with other works to produce a work based on this file,
// this file does not by itself cause the resulting work to be covered
// by the GNU General Public License. However the source code for this
// file must still be made available in accordance with section (3) of
// the GNU General Public License.
//
// This exception does not invalidate any other reasons why a work based
// on this file might be covered by the GNU General Public License.
//
// $Log: lpc2103.h,v $
// Revision 1.1  2006/04/13 06:31:38  edwards
// Initial revision.
//

#ifndef __LPC2103_H__
#define __LPC2103_H__

#define BIT0 (1<<0)
#define BIT1 (1<<1)
#define BIT2 (1<<2)
#define BIT3 (1<<3)
#define BIT4 (1<<4)
#define BIT5 (1<<5)
#define BIT6 (1<<6)
#define BIT7 (1<<7)

#define BIT8 (1<<8)
#define BIT9 (1<<9)
#define BIT10 (1<<10)
#define BIT11 (1<<11)
#define BIT12 (1<<12)
#define BIT13 (1<<13)
#define BIT14 (1<<14)
#define BIT15 (1<<15)

#define BIT16 (1<<16)
#define BIT17 (1<<17)
#define BIT18 (1<<18)
#define BIT19 (1<<19)
#define BIT20 (1<<20)
#define BIT21 (1<<21)
#define BIT22 (1<<22)
#define BIT23 (1<<23)

#define BIT24 (1<<24)
#define BIT25 (1<<25)
#define BIT26 (1<<26)
#define BIT27 (1<<27)
#define BIT28 (1<<28)
#define BIT29 (1<<29)
#define BIT30 (1<<30)
#define BIT31 (1<<31)

/* Vectored Interrupt Controller (VIC) */
#define VICIRQStatus	(*((volatile unsigned long *) 0xFFFFF000))
#define VICFIQStatus	(*((volatile unsigned long *) 0xFFFFF004))
#define VICRawIntr	(*((volatile unsigned long *) 0xFFFFF008))
#define VICIntSelect	(*((volatile unsigned long *) 0xFFFFF00C))
#define VICIntEnable	(*((volatile unsigned long *) 0xFFFFF010))
#define VICIntEnClr	(*((volatile unsigned long *) 0xFFFFF014))
#define VICSoftInt	(*((volatile unsigned long *) 0xFFFFF018))
#define VICSoftIntClr	(*((volatile unsigned long *) 0xFFFFF01C))
#define VICProtection	(*((volatile unsigned long *) 0xFFFFF020))
#define VICVectAddr	(*((volatile unsigned long *) 0xFFFFF030))
#define VICDefVectAddr	(*((volatile unsigned long *) 0xFFFFF034))
#define VICVectAddr0	(*((volatile unsigned long *) 0xFFFFF100))
#define VICVectAddr1	(*((volatile unsigned long *) 0xFFFFF104))
#define VICVectAddr2	(*((volatile unsigned long *) 0xFFFFF108))
#define VICVectAddr3	(*((volatile unsigned long *) 0xFFFFF10C))
#define VICVectAddr4	(*((volatile unsigned long *) 0xFFFFF110))
#define VICVectAddr5	(*((volatile unsigned long *) 0xFFFFF114))
#define VICVectAddr6	(*((volatile unsigned long *) 0xFFFFF118))
#define VICVectAddr7	(*((volatile unsigned long *) 0xFFFFF11C))
#define VICVectAddr8	(*((volatile unsigned long *) 0xFFFFF120))
#define VICVectAddr9	(*((volatile unsigned long *) 0xFFFFF124))
#define VICVectAddr10	(*((volatile unsigned long *) 0xFFFFF128))
#define VICVectAddr11	(*((volatile unsigned long *) 0xFFFFF12C))
#define VICVectAddr12	(*((volatile unsigned long *) 0xFFFFF130))
#define VICVectAddr13	(*((volatile unsigned long *) 0xFFFFF134))
#define VICVectAddr14	(*((volatile unsigned long *) 0xFFFFF138))
#define VICVectAddr15	(*((volatile unsigned long *) 0xFFFFF13C))
#define VICVectCntl0	(*((volatile unsigned long *) 0xFFFFF200))
#define VICVectCntl1	(*((volatile unsigned long *) 0xFFFFF204))
#define VICVectCntl2	(*((volatile unsigned long *) 0xFFFFF208))
#define VICVectCntl3	(*((volatile unsigned long *) 0xFFFFF20C))
#define VICVectCntl4	(*((volatile unsigned long *) 0xFFFFF210))
#define VICVectCntl5	(*((volatile unsigned long *) 0xFFFFF214))
#define VICVectCntl6	(*((volatile unsigned long *) 0xFFFFF218))
#define VICVectCntl7	(*((volatile unsigned long *) 0xFFFFF21C))
#define VICVectCntl8	(*((volatile unsigned long *) 0xFFFFF220))
#define VICVectCntl9	(*((volatile unsigned long *) 0xFFFFF224))
#define VICVectCntl10	(*((volatile unsigned long *) 0xFFFFF228))
#define VICVectCntl11	(*((volatile unsigned long *) 0xFFFFF22C))
#define VICVectCntl12	(*((volatile unsigned long *) 0xFFFFF230))
#define VICVectCntl13	(*((volatile unsigned long *) 0xFFFFF234))
#define VICVectCntl14	(*((volatile unsigned long *) 0xFFFFF238))
#define VICVectCntl15	(*((volatile unsigned long *) 0xFFFFF23C))

/* Pin Function Select */
#define PINSEL0		(*((volatile unsigned long *) 0xE002C000))
#define PINSEL1		(*((volatile unsigned long *) 0xE002C004))

/* Legacy General Purpose Input/Output (GPIO) */
#define IOPIN		(*((volatile unsigned long *) 0xE0028000))
#define IOSET		(*((volatile unsigned long *) 0xE0028004))
#define IODIR		(*((volatile unsigned long *) 0xE0028008))
#define IOCLR		(*((volatile unsigned long *) 0xE002800C))

/* Fast General Purpose Input/Output (GPIO) */
#define FIODIR		(*((volatile unsigned long *) 0x3FFFC000))
#define FIOMASK		(*((volatile unsigned long *) 0x3FFFC010))
#define FIOPIN		(*((volatile unsigned long *) 0x3FFFC014))
#define FIOSET		(*((volatile unsigned long *) 0x3FFFC018))
#define FIOCLR		(*((volatile unsigned long *) 0x3FFFC01C))

/* Universal Asynchronous Receiver/Transmitter 0 (UART0) */
#define U0RBR		(*((volatile unsigned char *) 0xE000C000)) /* rx buffer reg. (R/O when DLAB=0) */
#define U0THR		(*((volatile unsigned char *) 0xE000C000)) /* tx holding reg. (W/O when DLAB=0) */
#define U0DLL		(*((volatile unsigned char *) 0xE000C000)) /* divisor latch LSB (R/W when DLAB=1) */
#define U0DLM		(*((volatile unsigned char *) 0xE000C004)) /* divisor latch MSB (R/W when DLAB=1) */
#define U0IER		(*((volatile unsigned char *) 0xE000C004)) /* interrupt enable reg. (R/W when DLAB=0) */
#define U0IIR		(*((volatile unsigned char *) 0xE000C008)) /* interrupt ID reg. */
#define U0FCR		(*((volatile unsigned char *) 0xE000C008)) /* FIFO control reg. */
#define U0LCR		(*((volatile unsigned char *) 0xE000C00C)) /* line control reg. */
#define U0LSR		(*((volatile unsigned char *) 0xE000C014)) /* line status reg. */
#define U0SCR		(*((volatile unsigned char *) 0xE000C01C)) /* scratch pad reg. */
#define U0ACR		(*((volatile unsigned long *) 0xE000C020)) /* auto-baud control reg. */
#define U0FDR		(*((volatile unsigned char *) 0xE000C028)) /* fractional divider reg. */
#define U0TER		(*((volatile unsigned char *) 0xE000C030)) /* tx enable reg. */

/* Universal Asynchronous Receiver/Transmitter 1 (UART1) */
#define U1RBR		(*((volatile unsigned char *) 0xE0010000)) /* rx buffer reg. (R/O when DLAB=0) */
#define U1THR		(*((volatile unsigned char *) 0xE0010000)) /* tx holding reg. (W/O when DLAB=0) */
#define U1DLL		(*((volatile unsigned char *) 0xE0010000)) /* divisor latch LSB (R/W when DLAB=1) */
#define U1DLM		(*((volatile unsigned char *) 0xE0010004)) /* divisor latch MSB (R/W when DLAB=1) */
#define U1IER		(*((volatile unsigned char *) 0xE0010004)) /* interrupt enable reg. (R/W when DLAB=0) */
#define U1IIR		(*((volatile unsigned char *) 0xE0010008)) /* interrupt ID reg. */
#define U1FCR		(*((volatile unsigned char *) 0xE0010008)) /* FIFO control reg. */
#define U1LCR		(*((volatile unsigned char *) 0xE001000C)) /* line control reg. */
#define U1MCR		(*((volatile unsigned char *) 0xE0010010)) /* modem control reg. */
#define U1LSR		(*((volatile unsigned char *) 0xE0010014)) /* line status reg. */
#define U1MSR		(*((volatile unsigned char *) 0xE0010018)) /* modem status reg. */
#define U1SCR		(*((volatile unsigned char *) 0xE001001C)) /* scratch pad reg. */
#define U1ACR		(*((volatile unsigned long *) 0xE0010020)) /* auto-baud control reg. */
#define U1FDR		(*((volatile unsigned char *) 0xE0010028)) /* fractional divider reg. */
#define U1TER		(*((volatile unsigned char *) 0xE0010030)) /* tx enable reg. */

/* I2C Interface 0 */
#define I2C0CONSET	(*((volatile unsigned char *) 0xE001C000)) /* control set reg. */
#define I2C0STAT	(*((volatile unsigned char *) 0xE001C004)) /* status reg. */
#define I2C0DAT		(*((volatile unsigned char *) 0xE001C008)) /* data reg. */
#define I2C0ADR		(*((volatile unsigned char *) 0xE001C00C)) /* slave address reg. */
#define I2C0SCLH	(*((volatile unsigned short*) 0xE001C010)) /* duty cycle reg. (MSW) */
#define I2C0SCLL	(*((volatile unsigned short*) 0xE001C014)) /* duty cycle reg. (LSW) */
#define I2C0CONCLR	(*((volatile unsigned char *) 0xE001C018)) /* control clear reg. W/O */

/* I2C Interface 1 */
#define I2C1CONSET	(*((volatile unsigned char *) 0xE005C000)) /* control set reg. */
#define I2C1STAT	(*((volatile unsigned char *) 0xE005C004)) /* status reg. */
#define I2C1DAT		(*((volatile unsigned char *) 0xE005C008)) /* data reg. */
#define I2C1ADR		(*((volatile unsigned char *) 0xE005C00C)) /* slave address reg. */
#define I2C1SCLH	(*((volatile unsigned short*) 0xE005C010)) /* duty cycle reg. (MSW) */
#define I2C1SCLL	(*((volatile unsigned short*) 0xE005C014)) /* duty cycle reg. (LSW) */
#define I2C1CONCLR	(*((volatile unsigned char *) 0xE005C018)) /* control clear reg. W/O */

/* Serial Peripheral Interface (SPI) */
#define S0SPCR		(*((volatile unsigned short*) 0xE0020000)) /* control reg. */
#define S0SPSR		(*((volatile unsigned char *) 0xE0020004)) /* status reg. */
#define S0SPDR		(*((volatile unsigned short*) 0xE0020008)) /* data reg. */
#define S0SPCCR		(*((volatile unsigned char *) 0xE002000C)) /* clock counter reg. */
#define S0SPINT		(*((volatile unsigned char *) 0xE002001C)) /* interrupt flag */

/* Synchronous Serial Port (SSP) */

#define SSPCR0		(*((volatile unsigned short*) 0xE0068000)) /* control reg. 0 */
#define SSPCR1		(*((volatile unsigned char *) 0xE0068004)) /* control reg. 1 */
#define SSPDR		(*((volatile unsigned short*) 0xE0068008)) /* data reg. */
#define SSPSR		(*((volatile unsigned char *) 0xE006800C)) /* status reg. */
#define SSPCPSR		(*((volatile unsigned char *) 0xE0068010)) /* clock prescale reg. */
#define SSPIMSC		(*((volatile unsigned char *) 0xE0068014)) /* interrupt mask set and clear reg. */
#define SSPRIS		(*((volatile unsigned char *) 0xE0068018)) /* raw interrupt status reg. */
#define SSPMIS		(*((volatile unsigned char *) 0xE006801C)) /* masked interrupt status reg. */
#define SSPICR		(*((volatile unsigned char *) 0xE0068020)) /* interrupt clear reg. */

/* Memory Accelerator Module (MAM) */
#define MAMCR		(*((volatile unsigned char *) 0xE01FC000)) /* MAM control reg. */
#define MAMTIM		(*((volatile unsigned char *) 0xE01FC004)) /* MAM timing control */

/* External Interrupts */
#define EXTINT		(*((volatile unsigned char *) 0xE01FC140)) /* external interrupt flag reg. */
#define INTWAKE		(*((volatile unsigned short*) 0xE01FC144)) /* interrupt wake-up reg. */
#define EXTMODE		(*((volatile unsigned char *) 0xE01FC148)) /* external interrupt mode reg. */
#define EXTPOLAR	(*((volatile unsigned char *) 0xE01FC14C)) /* external interrupt polarity reg. */

/* Memory Mapping Control */
#define MEMMAP		(*((volatile unsigned char *) 0xE01FC040)) /* memory mapping control */

/* Phase Locked Loop (PLL) */
#define PLLCON		(*((volatile unsigned char *) 0xE01FC080)) /* PLL control reg. (protected by PLLFEED) */
#define PLLCFG		(*((volatile unsigned char *) 0xE01FC084)) /* PLL configuration reg. (protected by PLLFEED) */
#define PLLSTAT		(*((volatile unsigned short*) 0xE01FC088)) /* PLL status reg. */
#define PLLFEED		(*((volatile unsigned char *) 0xE01FC08C)) /* PLL feed reg */

/* Power Control */
#define PCON		(*((volatile unsigned char *) 0xE01FC0C0)) /* power control reg. */
#define PCONP		(*((volatile unsigned long *) 0xE01FC0C4)) /* power control for peripherals */

/* APB Divider */
#define APBDIV		(*((volatile unsigned char *) 0xE01FC100)) /* APB divider control */

/* Reset */
#define RSIR		(*((volatile unsigned char *) 0xE01FC180)) /* reset source identification reg. */

/* Code Security/Debugging */
#define CSPR		(*((volatile unsigned char *) 0xE01FC184)) /* code security protection reg. (R/O) */

/* System Control and Status flags register */
#define SCS		(*((volatile unsigned long *) 0xE01FC1A0))

/* RTC */
#define RTC_CCR      (*((volatile unsigned char *) 0xE0024008)) /* clock control */
#define RTC_CLKEN   BIT0
#define RTC_CTCRST  BIT1
#define RTC_CLKSRC  BIT4
#define RTC_CLKSRC32KHZ  RTC_CLKSRC
#define RTC_PREINT   (*((volatile unsigned short *) 0xE0024080)) /* prescaler (int) */
#define RTC_PREFRAC  (*((volatile unsigned short *) 0xE0024084)) /* prescaler (fraction) */
#define RTC_SEC      (*((volatile unsigned char  *) 0xE0024020))
#define RTC_MIN      (*((volatile unsigned char  *) 0xE0024024))
#define RTC_HOUR     (*((volatile unsigned char  *) 0xE0024028))
#define RTC_DOM      (*((volatile unsigned char  *) 0xE002402C)) /* day of month */
#define RTC_DAY RTC_DOM
#define RTC_DOW      (*((volatile unsigned char  *) 0xE0024030))
#define RTC_DOY      (*((volatile unsigned short *) 0xE0024034))
#define RTC_MONTH    (*((volatile unsigned char  *) 0xE0024038))
#define RTC_YEAR     (*((volatile unsigned short *) 0xE002403C))

/* Timer 0 */
#define T0IR		(*((volatile unsigned char *) 0xE0004000)) /* interrupt reg. */
#define T0TCR		(*((volatile unsigned char *) 0xE0004004)) /* timer control reg. */
#define T0TC		(*((volatile unsigned long *) 0xE0004008)) /* timer counter */
#define T0PR		(*((volatile unsigned long *) 0xE000400C)) /* prescale reg. */
#define T0PC		(*((volatile unsigned long *) 0xE0004010)) /* prescale counter */
#define T0MCR		(*((volatile unsigned short*) 0xE0004014)) /* match control reg. */
#define T0MR0		(*((volatile unsigned long *) 0xE0004018)) /* match reg. 0 */
#define T0MR1		(*((volatile unsigned long *) 0xE000401C)) /* match reg. 1 */
#define T0MR2		(*((volatile unsigned long *) 0xE0004020)) /* match reg. 2 */
#define T0MR3		(*((volatile unsigned long *) 0xE0004024)) /* match reg. 3 */
#define T0CCR		(*((volatile unsigned short*) 0xE0004028)) /* capture control reg. */
#define T0CR0		(*((volatile unsigned long *) 0xE000402C)) /* capture reg. 0 */
#define T0CR1		(*((volatile unsigned long *) 0xE0004030)) /* capture reg. 1 */
#define T0CR2		(*((volatile unsigned long *) 0xE0004034)) /* capture reg. 2 */
#define T0EMR		(*((volatile unsigned short*) 0xE000403C)) /* external match reg. */
#define T0CTCR		(*((volatile unsigned char *) 0xE0004070)) /* count control reg. */
#define T0PWMCON	(*((volatile unsigned long *) 0xE0004074)) /* PWM control reg. */

/* Timer 1 */
#define T1IR		(*((volatile unsigned char *) 0xE0008000)) /* interrupt reg. */
#define T1TCR		(*((volatile unsigned char *) 0xE0008004)) /* timer control reg. */
#define T1TC		(*((volatile unsigned long *) 0xE0008008)) /* timer counter */
#define T1PR		(*((volatile unsigned long *) 0xE000800C)) /* prescale reg. */
#define T1PC		(*((volatile unsigned long *) 0xE0008010)) /* prescale counter */
#define T1MCR		(*((volatile unsigned short*) 0xE0008014)) /* match control reg. */
#define T1MR0		(*((volatile unsigned long *) 0xE0008018)) /* match reg. 0 */
#define T1MR1		(*((volatile unsigned long *) 0xE000801C)) /* match reg. 1 */
#define T1MR2		(*((volatile unsigned long *) 0xE0008020)) /* match reg. 2 */
#define T1MR3		(*((volatile unsigned long *) 0xE0008024)) /* match reg. 3 */
#define T1CCR		(*((volatile unsigned short*) 0xE0008028)) /* capture control reg. */
#define T1CR0		(*((volatile unsigned long *) 0xE000802C)) /* capture reg. 0 */
#define T1CR1		(*((volatile unsigned long *) 0xE0008030)) /* capture reg. 1 */
#define T1CR2		(*((volatile unsigned long *) 0xE0008034)) /* capture reg. 2 */
#define T1EMR		(*((volatile unsigned short*) 0xE000803C)) /* external match reg. */
#define T1CTCR		(*((volatile unsigned char *) 0xE0008070)) /* count control reg. */
#define T1PWMCON	(*((volatile unsigned long *) 0xE0008074)) /* PWM control reg. */

/* Timer 2 */
#define T2IR		(*((volatile unsigned char *) 0xE0070000)) /* interrupt reg. */
#define T2TCR		(*((volatile unsigned char *) 0xE0070004)) /* timer control reg. */
#define T2TC		(*((volatile unsigned short*) 0xE0070008)) /* timer counter */
#define T2PR		(*((volatile unsigned short*) 0xE007000C)) /* prescale reg. */
#define T2PC		(*((volatile unsigned short*) 0xE0070010)) /* prescale counter */
#define T2MCR		(*((volatile unsigned short*) 0xE0070014)) /* match control reg. */
#define T2MR0		(*((volatile unsigned short*) 0xE0070018)) /* match reg. 0 */
#define T2MR1		(*((volatile unsigned short*) 0xE007001C)) /* match reg. 1 */
#define T2MR2		(*((volatile unsigned short*) 0xE0070020)) /* match reg. 2 */
#define T2MR3		(*((volatile unsigned short*) 0xE0070024)) /* match reg. 3 */
#define T2MR0L		(*((volatile unsigned long*) 0xE0070018)) /* match reg. 0 */
#define T2MR1L		(*((volatile unsigned long*) 0xE007001C)) /* match reg. 1 */
#define T2MR2L		(*((volatile unsigned long*) 0xE0070020)) /* match reg. 2 */
#define T2MR3L		(*((volatile unsigned long*) 0xE0070024)) /* match reg. 3 */
#define T2CCR		(*((volatile unsigned short*) 0xE0070028)) /* capture control reg. */
#define T2CR0		(*((volatile unsigned short*) 0xE007002C)) /* capture reg. 0 */
#define T2CR1		(*((volatile unsigned short*) 0xE0070030)) /* capture reg. 1 */
#define T2CR2		(*((volatile unsigned short*) 0xE0070034)) /* capture reg. 2 */
#define T2EMR		(*((volatile unsigned short*) 0xE007003C)) /* external match reg. */
#define T2CTCR		(*((volatile unsigned char *) 0xE0070070)) /* count control reg. */
#define T2PWMCON	(*((volatile unsigned long *) 0xE0070074)) /* PWM control reg. */

/* Timer 3 */
#define T3IR		(*((volatile unsigned char *) 0xE0074000)) /* interrupt reg. */
#define T3TCR		(*((volatile unsigned char *) 0xE0074004)) /* timer control reg. */
#define T3TC		(*((volatile unsigned short*) 0xE0074008)) /* timer counter */
#define T3PR		(*((volatile unsigned short*) 0xE007400C)) /* prescale reg. */
#define T3PC		(*((volatile unsigned short*) 0xE0074010)) /* prescale counter */
#define T3MCR		(*((volatile unsigned short*) 0xE0074014)) /* match control reg. */
#define T3MR0		(*((volatile unsigned short*) 0xE0074018)) /* match reg. 0 */
#define T3MR1		(*((volatile unsigned short*) 0xE007401C)) /* match reg. 1 */
#define T3MR2		(*((volatile unsigned short*) 0xE0074020)) /* match reg. 2 */
#define T3MR3		(*((volatile unsigned short*) 0xE0074024)) /* match reg. 3 */
#define T3MR0L		(*((volatile unsigned long*) 0xE0074018)) /* match reg. 0 */
#define T3MR1L		(*((volatile unsigned long*) 0xE007401C)) /* match reg. 1 */
#define T3MR2L		(*((volatile unsigned long*) 0xE0074020)) /* match reg. 2 */
#define T3MR3L		(*((volatile unsigned long*) 0xE0074024)) /* match reg. 3 */
#define T3CCR		(*((volatile unsigned short*) 0xE0074028)) /* capture control reg. */
#define T3CR0		(*((volatile unsigned short*) 0xE007402C)) /* capture reg. 0 */
#define T3CR1		(*((volatile unsigned short*) 0xE0074030)) /* capture reg. 1 */
#define T3CR2		(*((volatile unsigned short*) 0xE0074034)) /* capture reg. 2 */
#define T3EMR		(*((volatile unsigned short*) 0xE007403C)) /* external match reg. */
#define T3CTCR		(*((volatile unsigned char *) 0xE0074070)) /* count control reg. */
#define T3PWMCON	(*((volatile unsigned long *) 0xE0074074)) /* PWM control reg. */

/* ADC0 */
#define AD0CR       (*((volatile unsigned long *) 0xE0034000)) /* ADC control reg. */
#define AD0GDR      (*((volatile unsigned long *) 0xE0034004)) /* ADC global data reg. */
#define AD0STAT     (*((volatile unsigned long *) 0xE0034030)) /* ADC status reg. */
#define AD0INTEN    (*((volatile unsigned long *) 0xE003400C)) /* ADC irq en reg. */
#define AD0DR0      (*((volatile unsigned long *) 0xE0034010)) /* ADC data reg. 0 */
#define AD0DR1      (*((volatile unsigned long *) 0xE0034014)) /* ADC data reg. 1 */
#define AD0DR2      (*((volatile unsigned long *) 0xE0034018)) /* ADC data reg. 2 */
#define AD0DR3      (*((volatile unsigned long *) 0xE003401C)) /* ADC data reg. 3 */
#define AD0DR4      (*((volatile unsigned long *) 0xE0034020)) /* ADC data reg. 4 */
#define AD0DR5      (*((volatile unsigned long *) 0xE0034024)) /* ADC data reg. 5 */
#define AD0DR6      (*((volatile unsigned long *) 0xE0034028)) /* ADC data reg. 6 */
#define AD0DR7      (*((volatile unsigned long *) 0xE003402C)) /* ADC data reg. 7 */


/* Bit definitions */

/* Timer 01 */
#define Tx_cnt_enable BIT0
#define Tx_reset  BIT1

#define Tx_mode_timer 0
#define Tx_mode_cnt_rising BIT0
#define Tx_mode_cnt_falling BIT1
#define Tx_mode_cnt_both (BIT0|BIT1)

#define MR0int      BIT0
#define MR0reset    BIT1
#define MR0stop     BIT2
#define MR1int      BIT3
#define MR1reset    BIT4
#define MR1stop     BIT5
#define MR2int      BIT6
#define MR2reset    BIT7
#define MR2stop     BIT8
#define MR3int      BIT9
#define MR3reset    BIT10
#define MR3stop     BIT11

#define capre(x)    (BIT0 << ((x)*3))
#define capfe(x)    (BIT1 << ((x)*3))
#define capi(x)     (BIT2 << ((x)*3))
#define cap0re      BIT0
#define cap0fe      BIT1
#define cap0i       BIT2
#define cap1re      BIT3
#define cap1fe      BIT4
#define cap1i       BIT5
#define cap2re      BIT6
#define cap2fe      BIT7
#define cap2i       BIT8
#define cap3re      BIT9
#define cap3fe      BIT10
#define cap3i       BIT11

#define INT_MR0 BIT0
#define INT_MR1 BIT1
#define INT_MR2 BIT2
#define INT_MR3 BIT3
#define INT_CR0 BIT4
#define INT_CR1 BIT5
#define INT_CR2 BIT6
#define INT_CR3 BIT7

/* Interrupt enables */
#define IE_Timer3 27
#define IE_Timer2 26
#define IE_I2C1   19
#define IE_AD0    18
#define IE_EINT2  16
#define IE_EINT1  15
#define IE_EINT0  14
#define IE_RTC    13
#define IE_PLL    12
#define IE_SPI1   11
#define IE_SPI0   10
#define IE_I2C0   9
#define IE_UART1  7
#define IE_UART0  6
#define IE_Timer1 5
#define IE_Timer0 4
#define IE_ARMCORE1 3
#define IE_ARMCORE0 2
#define IE_WDT    0
#define BIT(x) (1<<x)
#define IRQ_EN    BIT5
#define IRQ_DIS   0

//GPIO
#define GPIO0M BIT0

//APBDIV
#define APBDIV1 BIT0
#define APBDIV2 BIT1
#define APBDIV4 0

//PLL
#define PSEL_BIT0 		BIT5
#define PSEL_BIT1 		BIT6

#define PSEL1   0
#define PSEL2   PSEL_BIT0
#define PSEL4   PSEL_BIT1
#define PSEL8   (PSEL_BIT0|PSEL_BIT1)

#define PLLE		BIT0
#define PLLC		BIT1
#define PLOCK		BIT10
#define PLL_FEED1	0xAA
#define PLL_FEED2	0x55

/* SCB */
#define MEMMAP_BOOT_LOADER_MODE   0       // Interrupt vectors are re-mapped to Boot Block.
#define MEMMAP_USER_FLASH_MODE    BIT0  // Interrupt vectors are not re-mapped and reside in Flash.
#define MEMMAP_USER_RAM_MODE      BIT1  // Interrupt vectors are re-mapped to Static RAM.


/* UART */
#define FIFO_ENABLE   		BIT0
#define FIFO_RX_CLEAR       BIT1
#define FIFO_TX_CLEAR       BIT2
#define FIFO_RX_TRIGGER_1   0
#define FIFO_RX_TRIGGER_4   BIT6
#define FIFO_RX_TRIGGER_8   BIT7
#define FIFO_RX_TRIGGER_14  (BIT6|BIT7)

#define UART_5BIT           0
#define UART_6BIT           1
#define UART_7BIT           2
#define UART_8BIT           3
#define STOPBIT             BIT2
#define PARITY              BIT3
#define PARITY_ODD          0
#define PARITY_EVEN         BIT4
#define PARITY_1            BIT5
#define PARITY_0            (BIT4|BIT5)
#define BREAK				BIT6
#define DLAB				BIT7

#define TXEN				BIT7

#define RDR                 BIT0
#define OVERRUN             BIT1
#define PARITY_ERROR        BIT2
#define FRAMING_ERROR       BIT3
#define BREAK_IRQ			BIT4
#define THRE				BIT5
#define TEMT				BIT6
#define RXFE				BIT7

#define IRQ_data_ready        BIT0
#define IRQ_transmitter_ready BIT1
#define IRQ_status_line       BIT2
#define IRQ_autobaud_timeout  BIT8
#define IRQ_autobaud_end      BIT9

#define power_timer0    BIT1
#define power_timer1    BIT2
#define power_uart0     BIT3
#define power_uart1     BIT4
#define power_i2c0      BIT7
#define power_spi       BIT8
#define power_rtc       BIT9
#define power_ssp       BIT10
#define power_adc       BIT12
#define power_i2c1      BIT19
#define power_timer2    BIT28
#define power_timer3    BIT29

#if 1
#define force_inline __attribute__((always_inline))
#define const_func __attribute__((const))
#define pure_func __attribute__((pure))
#define naked_func __attribute__((naked))
#else 
#define force_inline
#define const_func
#define pure_func
#endif

#define SPI0_BitEnable  BIT2
#define SPI0_CPAH       BIT3
#define SPI0_CPOL       BIT4
#define SPI0_Master     BIT5
#define SPI0_LSBF       BIT6
#define SPI0_SPIE       BIT7
#define SPI0_BITS_8     BIT11
#define SPI0_BITS_9     (BIT11|BIT8)
#define SPI0_BITS_10    (BIT11|BIT9)
#define SPI0_BITS_11    (BIT11|BIT9|BIT8)
#define SPI0_BITS_12    (BIT11|BIT10)
#define SPI0_BITS_13    (BIT11|BIT10|BIT8)
#define SPI0_BITS_14    (BIT11|BIT10|BIT9)
#define SPI0_BITS_15    (BIT11|BIT10|BIT9|BIT8)
#define SPI0_BITS_16    0

#define SPIF BIT7
#endif // __LPC2103_H
