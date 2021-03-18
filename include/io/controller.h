#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <PR/ultratypes.h>
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

#define CONT_A      0x8000
#define CONT_B      0x4000
#define CONT_G	    0x2000
#define CONT_START  0x1000
#define CONT_UP     0x0800
#define CONT_DOWN   0x0400
#define CONT_LEFT   0x0200
#define CONT_RIGHT  0x0100
#define CONT_L      0x0020
#define CONT_R      0x0010
#define CONT_E      0x0008
#define CONT_D      0x0004
#define CONT_C      0x0002
#define CONT_F      0x0001

#define A_BUTTON	CONT_A
#define B_BUTTON	CONT_B
#define L_TRIG		CONT_L
#define R_TRIG		CONT_R
#define Z_TRIG		CONT_G
#define START_BUTTON	CONT_START
#define U_JPAD		CONT_UP
#define L_JPAD		CONT_LEFT
#define R_JPAD		CONT_RIGHT
#define D_JPAD		CONT_DOWN
#define U_CBUTTONS	CONT_E
#define L_CBUTTONS	CONT_C
#define R_CBUTTONS	CONT_F
#define D_CBUTTONS	CONT_D

typedef struct {
    /* 0x00 */ u32 ramarray[15];
    /* 0x3C */ u32 pifstatus;
} OSPifRam;


typedef struct {
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u16 button;
    /* 0x6 */ s8 stick_x;
    /* 0x7 */ s8 stick_y;
} __OSContReadFormat;


typedef struct {
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u8 typeh;
    /* 0x5 */ u8 typel;
    /* 0x6 */ u8 status;
    /* 0x7 */ u8 dummy1;
} __OSContRequesFormat;

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
    /* 0x04 */ u16 address;
    /* 0x06 */ u8 data[32];
    /* 0x26 */ u8 datacrc;
} __OSContRamReadFormat;


#endif
