#include "rom_header.h"
#include "versions.h"

/* 0x00 */ ENDIAN_IDENTIFIER
/* 0x01 */ PI_DOMAIN_1_CFG(64, 18, 7, 3)
/* 0x04 */ SYSTEM_CLOCK_RATE_SETTING(0xF)
/* 0x08 */ ENTRYPOINT(entrypoint)
/* 0x0C */ LIBULTRA_VERSION(2, 0, K)
/* 0x10 */ CHECKSUM()
/* 0x18 */ PADDING(8)
/* 0x20 */
#if MM_VERSION == MM_N64_JP_1_0 || MM_VERSION == MM_N64_JP_1_1
    ROM_NAME("THE MASK OF MUJURA")
#else
    ROM_NAME("ZELDA MAJORA'S MASK")
#endif
/* 0x34 */ PADDING(7)
/* 0x3B */ MEDIUM(CARTRIDGE)
/* 0x3C */ GAME_ID("ZS")
/* 0x3E */
#if MM_VERSION == MM_N64_JP_1_0 || MM_VERSION == MM_N64_JP_1_1
    REGION(JP)
#else
    REGION(US)
#endif
/* 0x3F */ GAME_REVISION(0)
