#ifndef PR_RCP_H
#define PR_RCP_H

/**
 * PIF Physical memory map (total size = 2 KB)
 *
 *            Size      Description     Mode
 *  1FC007FF    +-------+-----------------+-----+
 *              |  64 B | JoyChannel RAM  | R/W |
 *  1FC007C0    +-------+-----------------+-----+
 *              |1984 B |    Boot ROM     |  *  |  * = Reserved
 *  1FC00000    +-------+-----------------+-----+
 */
#define PIF_ROM_START   0x1FC00000
#define PIF_ROM_END     0x1FC007BF
#define PIF_RAM_START   0x1FC007C0
#define PIF_RAM_END     0x1FC007FF

/*
 * Patterns to interpret VI_CONTROL_REG
 */
#define VI_CTRL_TYPE_16             0x00002 /* [1:0] pixel size: 16 bit */
#define VI_CTRL_TYPE_32             0x00003 /* [1:0] pixel size: 32 bit */
#define VI_CTRL_GAMMA_DITHER_ON     0x00004 /* 2: default = on */
#define VI_CTRL_GAMMA_ON            0x00008 /* 3: default = on */
#define VI_CTRL_DIVOT_ON            0x00010 /* 4: default = on */
#define VI_CTRL_SERRATE_ON          0x00040 /* 6: on if interlaced */
#define VI_CTRL_ANTIALIAS_MASK      0x00300 /* [9:8] anti-alias mode */
#define VI_CTRL_ANTIALIAS_MODE_1    0x00100 /* Bit [9:8] anti-alias mode */
#define VI_CTRL_ANTIALIAS_MODE_2    0x00200 /* Bit [9:8] anti-alias mode */
#define VI_CTRL_ANTIALIAS_MODE_3    0x00300 /* Bit [9:8] anti-alias mode */
#define VI_CTRL_PIXEL_ADV_MASK      0x01000 /* [15:12] pixel advance mode? */
#define VI_CTRL_PIXEL_ADV_1         0x01000 /* Bit [15:12] pixel advance mode? */
#define VI_CTRL_PIXEL_ADV_2         0x02000 /* Bit [15:12] pixel advance mode? */
#define VI_CTRL_PIXEL_ADV_3         0x03000 /* Bit [15:12] pixel advance mode? */
#define VI_CTRL_DITHER_FILTER_ON    0x10000 /* 16: dither-filter mode */


#define VI_NTSC_CLOCK       48681812        /* Hz = 48.681812 MHz */
#define VI_PAL_CLOCK        49656530        /* Hz = 49.656530 MHz */
#define VI_MPAL_CLOCK       48628316        /* Hz = 48.628316 MHz */

/**
 * Audio Interface (AI) Registers
 */
#define AI_BASE_REG     0x04500000

/* AI DRAM address (W): [23:0] starting RDRAM address (8B-aligned) */
#define AI_DRAM_ADDR_REG    (AI_BASE_REG + 0x00)    /* R0: DRAM address */

/* AI length (R/W): [14:0] transfer length (v1.0) - Bottom 3 bits are ignored */
/*                  [17:0] transfer length (v2.0) - Bottom 3 bits are ignored */
#define AI_LEN_REG          (AI_BASE_REG + 0x04)    /* R1: Length */

/* AI control (W): [0] DMA enable - if LSB == 1, DMA is enabled */
#define AI_CONTROL_REG      (AI_BASE_REG + 0x08)    /* R2: DMA Control */

/* Value for control register */
#define AI_CONTROL_DMA_ON   1   /* LSB = 1: DMA enable*/
#define AI_CONTROL_DMA_OFF  0   /* LSB = 1: DMA enable*/

/* 
 * AI status (R): [31]/[0] ai_full (addr & len buffer full), [30] ai_busy 
 *        Note that a 1->0 transition in ai_full will set interrupt
 *           (W): clear audio interrupt 
 */
#define AI_STATUS_REG       (AI_BASE_REG + 0x0C)    /* R3: Status */

/* Value for status register */
#define AI_STATUS_FIFO_FULL (1 << 31)
#define AI_STATUS_DMA_BUSY  (1 << 30)

/* 
 * AI DAC sample period register (W): [13:0] dac rate 
 *   - vid_clock/(dperiod + 1) is the DAC sample rate
 *   - (dperiod + 1) >= 66 * (aclockhp + 1) must be true
 */
#define AI_DACRATE_REG      (AI_BASE_REG + 0x10)    /* R4: DAC rate 14-lsb*/

/* DAC rate = video clock / audio frequency
 *   - DAC rate >= (66 * Bit rate) must be true
 */
#define AI_MAX_DAC_RATE 16384   /* 14-bit+1 */
#define AI_MIN_DAC_RATE 132

/* 
 * AI bit rate (W): [3:0] bit rate (abus clock half period register - aclockhp)
 *   - vid_clock/(2 * (aclockhp + 1)) is the DAC clock rate
 *   - The abus clock stops if aclockhp is zero
 */
#define AI_BITRATE_REG      (AI_BASE_REG + 0x14)    /* R5: Bit rate 4-lsb */

/* Bit rate <= (DAC rate / 66) */
#define AI_MAX_BIT_RATE 16      /* 4-bit+1 */
#define AI_MIN_BIT_RATE 2

#define DEVICE_TYPE_CART    0   /* ROM cartridge */
#define DEVICE_TYPE_BULK    1   /* ROM bulk */
#define DEVICE_TYPE_64DD    2   /* 64 Disk Drive */
#define DEVICE_TYPE_SRAM    3   /* SRAM */
#define DEVICE_TYPE_INIT    7   /* initial value */

/**
 * Signal Processor (SP) Memory
 */
#define SP_DMEM_START   0x04000000
#define SP_DMEM_END     0x04000FFF
#define SP_IMEM_START   0x04001000
#define SP_IMEM_END     0x04001FFF

#define CHNL_ERR_NORESP     0x80    /* Bit 7 (Rx): No response error */
#define CHNL_ERR_OVERRUN    0x40    /* Bit 6 (Rx): Overrun error */
#define CHNL_ERR_FRAME      0x80    /* Bit 7 (Tx): Frame error */
#define CHNL_ERR_COLLISION  0x40    /* Bit 6 (Tx): Collision error */

#define CHNL_ERR_MASK       0xC0    /* Bit 6-7: channel errors */

#define PI_DOM1_ADDR1   0x06000000  /* to 0x07FFFFFF */
#define PI_DOM1_ADDR2   0x10000000  /* to 0x1FBFFFFF */
#define PI_DOM1_ADDR3   0x1FD00000  /* to 0x7FFFFFFF */
#define PI_DOM2_ADDR1   0x05000000  /* to 0x05FFFFFF */
#define PI_DOM2_ADDR2   0x08000000  /* to 0x0FFFFFFF */

#define IO_READ(addr)       (*(vu32*)PHYS_TO_K1(addr))
#define IO_WRITE(addr,data) (*(vu32*)PHYS_TO_K1(addr)=(u32)(data))

#endif
