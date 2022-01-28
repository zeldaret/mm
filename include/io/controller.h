#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include "PR/ultratypes.h"
#include "PR/pfs.h"

#define SIAccessQueueSize 2
#define BLOCKSIZE 32
#define MAXCONTROLLERS  4
#define PFS_ONE_PAGE 8

#define PFS_PAGE_SIZE (BLOCKSIZE*PFS_ONE_PAGE)

#define CONT_CMD_REQUEST_STATUS 0
#define CONT_CMD_READ_BUTTON 1
#define CONT_CMD_READ_MEMPACK 2
#define CONT_CMD_WRITE_MEMPACK 3
#define CONT_CMD_READ_EEPROM 4
#define CONT_CMD_WRITE_EEPROM 5
#define CONT_CMD_RESET 0xFF

#define CONT_CMD_REQUEST_STATUS_TX 1
#define CONT_CMD_READ_BUTTON_TX 1
#define CONT_CMD_READ_MEMPACK_TX 3
#define CONT_CMD_WRITE_MEMPACK_TX 35
#define CONT_CMD_READ_EEPROM_TX 2
#define CONT_CMD_WRITE_EEPROM_TX 10
#define CONT_CMD_RESET_TX 1

#define CONT_CMD_REQUEST_STATUS_RX 3
#define CONT_CMD_READ_BUTTON_RX 4
#define CONT_CMD_READ_MEMPACK_RX 33
#define CONT_CMD_WRITE_MEMPACK_RX 1
#define CONT_CMD_READ_EEPROM_RX 8
#define CONT_CMD_WRITE_EEPROM_RX 1
#define CONT_CMD_RESET_RX 3

#define CONT_CMD_NOP 0xFF
#define CONT_CMD_END 0xFE // Indicates end of a command
#define CONT_CMD_EXE 1    // Set pif ram status byte to this to do a command

#define CONT_ERR_NO_CONTROLLER      PFS_ERR_NOPACK      /* 1 */
#define CONT_ERR_CONTRFAIL          CONT_OVERRUN_ERROR  /* 4 */
#define CONT_ERR_INVALID            PFS_ERR_INVALID     /* 5 */
#define CONT_ERR_DEVICE             PFS_ERR_DEVICE      /* 11 */
#define CONT_ERR_NOT_READY          12
#define CONT_ERR_VOICE_MEMORY       13
#define CONT_ERR_VOICE_WORD         14
#define CONT_ERR_VOICE_NO_RESPONSE  15


#define DIR_STATUS_EMPTY 0
#define DIR_STATUS_UNKNOWN 1
#define DIR_STATUS_OCCUPIED 2

#define PFS_FORCE 1
#define PFS_DELETE 1

#define PFS_LABEL_AREA 7

#define PFS_ERR_NOPACK 1

/* controller errors */
#define CONT_NO_RESPONSE_ERROR          0x8
#define CONT_OVERRUN_ERROR              0x4

/* Controller type */
#define CONT_ABSOLUTE           0x0001
#define CONT_RELATIVE           0x0002
#define CONT_JOYPORT            0x0004
#define CONT_EEPROM             0x8000
#define CONT_EEP16K             0x4000
#define CONT_TYPE_MASK          0x1F07
#define CONT_TYPE_NORMAL        0x0005
#define CONT_TYPE_MOUSE         0x0002
#define CONT_TYPE_VOICE         0x0100

/* Controller status */
#define CONT_CARD_ON            0x01
#define CONT_CARD_PULL          0x02
#define CONT_ADDR_CRC_ER        0x04
#define CONT_EEPROM_BUSY        0x80

/* Buttons */
#define BTN_CRIGHT      0x0001
#define BTN_CLEFT       0x0002
#define BTN_CDOWN       0x0004
#define BTN_CUP         0x0008
#define BTN_R           0x0010
#define BTN_L           0x0020
#define BTN_DRIGHT      0x0100
#define BTN_DLEFT       0x0200
#define BTN_DDOWN       0x0400
#define BTN_DUP         0x0800
#define BTN_START       0x1000
#define BTN_Z           0x2000
#define BTN_B           0x4000
#define BTN_A           0x8000

typedef struct {
    /* 0x00 */ u32 ramarray[15];
    /* 0x3C */ u32 status;
} OSPifRam; // size = 0x40


typedef struct {
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u16 button;
    /* 0x6 */ s8 stick_x;
    /* 0x7 */ s8 stick_y;
} __OSContReadFormat;


// Original name: __OSContRequesFormat
typedef struct {
    /* 0x00 */ u8 align;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 poll;
    /* 0x04 */ u8 typeh;
    /* 0x05 */ u8 typel;
    /* 0x06 */ u8 status;
    /* 0x07 */ u8 align1;
} __OSContRequestHeader; // size = 0x8

typedef struct {
    /* 0x00 */ u8 txsize;
    /* 0x01 */ u8 rxsize;
    /* 0x02 */ u8 poll;
    /* 0x03 */ u8 typeh;
    /* 0x04 */ u8 typel;
    /* 0x05 */ u8 status;
} __OSContRequestHeaderAligned; // size = 0x6

typedef struct {
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u8 hi;
    /* 0x05 */ u8 lo;
    /* 0x06 */ u8 data[32];
    /* 0x26 */ u8 datacrc;
} __OSContRamReadFormat;

extern OSPifRam __osContPifRam;
// extern UNK_TYPE1 D_8009CF0C;
extern u8 __osContLastPoll;
extern u8 __osMaxControllers;
// extern OSMesgQueue D_8009CF38;
// extern OSMesg D_8009CF50;

typedef struct {
    /* 0x00 */ OSContPad cur;
    /* 0x06 */ OSContPad prev;
    /* 0x0C */ OSContPad press; // X/Y store delta from last frame
    /* 0x12 */ OSContPad rel; // X/Y store adjusted
} Input; // size = 0x18

#endif
