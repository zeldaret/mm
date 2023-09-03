#ifndef PR_OS_INTERNAL_FLASH_H
#define PR_OS_INTERNAL_FLASH_H

#include "os_flash.h"

#define FLASH_PAGE_SIZE 128

#define FRAM_COMMAND_REGISTER 0x10000 // Located at 0x08010000 on the Cart

/* Does nothing for FRAM_COMMAND_SET_MODE_READ_AND_STATUS, FRAM_MODE_NOP, FRAM_COMMAND_SET_MODE_STATUS_AND_STATUS
   Initializes fram to 0xFF in FRAM_MODE_ERASE
   Writes Contents in FLASHRAM_MODE_WRITE
   After execution, sets FRAM_MODE to FRAM_MODE_NOP */
#define FRAM_COMMAND_EXECUTE 0xD2000000
/* flashram->erase_offset = (command & 0xFFFF) * 128; */
#define FRAM_COMMAND_SET_ERASE_SECTOR_OFFSET 0x4B000000
/* flashram->mode = FLASHRAM_MODE_ERASE;
   flashram->status = 0x1111800800C20000LL; */
#define FRAM_COMMAND_SET_MODE_ERASE_AND_STATUS 0x78000000
/* flashram->erase_offset = (command & 0xFFFF) * 128;
   flashram->status = 0x1111800400C20000LL; */
#define FRAM_COMMAND_SET_ERASE_SECTOR_OFFSET_AND_STATUS 0xA5000000
/* flashram->mode = FLASHRAM_MODE_WRITE; */
#define FRAM_COMMAND_SET_MODE_WRITE 0xB4000000
/* flashram->mode = FLASHRAM_MODE_STATUS;
   flashram->status = 0x1111800100C20000LL; */
#define FRAM_COMMAND_SET_MODE_STATUS_AND_STATUS 0xE1000000
/* flashram->mode = FLASHRAM_MODE_READ;
   flashram->status = 0x11118004F0000000LL; */
#define FRAM_COMMAND_SET_MODE_READ_AND_STATUS 0xF0000000
/* unk */
#define FRAM_COMMAND_UNK_ERASE_OPERATION 0x3C000000

typedef enum FramMode {
    /* 0 */ FRAM_MODE_NOP,
    /* 1 */ FRAM_MODE_ERASE,
    /* 2 */ FRAM_MODE_WRITE,
    /* 3 */ FRAM_MODE_READ,
    /* 4 */ FRAM_MODE_STATUS
} FramMode;

#endif
