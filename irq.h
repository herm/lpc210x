#ifndef __VIC_H__
#define __VIC_H__
extern "C" {
unsigned enableIRQ(void);
unsigned disableIRQ(void);
unsigned restoreIRQ(unsigned oldCPSR);
}

#define vic_configure(channel, source, handler) \
	do { \
		VICVectAddr##channel = (unsigned long)(handler); \
		VICVectCntl##channel = IRQ_EN | source; \
		VICIntEnable = (1<<source); \
	} while (0)

#endif
