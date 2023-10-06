#ifndef _ULTRA64_HARDWARE_H_
#define _ULTRA64_HARDWARE_H_

// TODO: not real libultra header. Refactor to R4300.h

// Segment Wrapper
// Uncached RDRAM
#define KSEG1 0xA0000000 // 0xA0000000 - 0xBFFFFFFF  Physical memory, uncached, unmapped
#define RDRAM_UNCACHED KSEG1

// Cached RDRAM
#define KSEG0 0x80000000 // 0x80000000 - 0x9FFFFFFF  Physical memory, cached, unmapped
#define RDRAM_CACHED KSEG0

// Volatile access wrapper, enforcing uncached memory
#define HW_REG(reg, type) *(volatile type*)((reg) | KSEG1)

#define TMEM_SIZE 0x1000

#define MI_INIT_MODE_REG  0x04300000
#define MI_MODE_REG       MI_INIT_MODE_REG
#define MI_VERSION_REG    0x04300004
#define MI_INTR_REG       0x04300008
#define MI_INTR_MASK_REG  0x0430000C

/* Interrupt pending bits */
#define	CAUSE_IP8  0x00008000  /* External level 8 pending - COMPARE */
#define	CAUSE_IP7  0x00004000  /* External level 7 pending - INT4 */
#define	CAUSE_IP6  0x00002000  /* External level 6 pending - INT3 */
#define	CAUSE_IP5  0x00001000  /* External level 5 pending - INT2 */
#define	CAUSE_IP4  0x00000800  /* External level 4 pending - INT1 */
#define	CAUSE_IP3  0x00000400  /* External level 3 pending - INT0 */
#define	CAUSE_SW2  0x00000200  /* Software level 2 pending */
#define	CAUSE_SW1  0x00000100  /* Software level 1 pending */

#endif
