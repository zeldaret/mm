#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <PR/ultratypes.h>

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
    /* 0x00 */ union {
        u16 button;
        struct {
            u16 a   : 1;
            u16 b   : 1;
            u16 z   : 1;
            u16 s   : 1;
            u16 du  : 1;
            u16 dd  : 1;
            u16 dl  : 1;
            u16 dr  : 1;
            u16 illegal_h : 1;
            u16 illegal_l : 1;
            u16 l   : 1;
            u16 r   : 1;
            u16 cu  : 1;
            u16 cd  : 1;
            u16 cl  : 1;
            u16 cr  : 1;
        };
    };
    /* 0x02 */ s8  x;
    /* 0x03 */ s8  y;
} PadInput; // size = 0x4

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
