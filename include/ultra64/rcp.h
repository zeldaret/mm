#ifndef _ULTRA64_RCP_H_
#define _ULTRA64_RCP_H_

#define VI_NTSC_CLOCK       48681812        /* Hz = 48.681812 MHz */
#define VI_PAL_CLOCK        49656530        /* Hz = 49.656530 MHz */
#define VI_MPAL_CLOCK       48628316        /* Hz = 48.628316 MHz */

#define DEVICE_TYPE_CART    0   /* ROM cartridge */
#define DEVICE_TYPE_BULK    1   /* ROM bulk */
#define DEVICE_TYPE_64DD    2   /* 64 Disk Drive */
#define DEVICE_TYPE_SRAM    3   /* SRAM */
#define DEVICE_TYPE_INIT    7   /* initial value */

#define IO_READ(addr)       (*(vu32*)PHYS_TO_K1(addr))
#define IO_WRITE(addr,data) (*(vu32*)PHYS_TO_K1(addr)=(u32)(data))

#endif
