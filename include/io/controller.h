#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <PR/ultratypes.h>

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
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u16 address;
    /* 0x06 */ u8 data[32];
    /* 0x26 */ u8 datacrc;
} __OSContRamReadFormat;


typedef struct {
    /* 0x00 */ u16 company_code;
    /* 0x02 */ u16 game_code;
    /* 0x04 */ u8 start_page;
    /* 0x05 */ u8 status;
    /* 0x06 */ u16 data_sum;
    /* 0x08 */ unsigned char ext_name[4];
    /* 0x0C */ unsigned char game_name[16];
    /* 0x1C */ s32 reserved;
} __OSDir;


typedef struct {
    /* 0x0 */ u8 inode_page[256];
} __OSInode;

#endif
