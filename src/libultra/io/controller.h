#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

typedef struct {
    /* 0 */ u32 ramarray[15];
    /* 60 */ u32 pifstatus;
} OSPifRam;


typedef struct {
    /* 0 */ u8 dummy;
    /* 1 */ u8 txsize;
    /* 2 */ u8 rxsize;
    /* 3 */ u8 cmd;
    /* 4 */ u16 button;
    /* 6 */ s8 stick_x;
    /* 7 */ s8 stick_y;
} __OSContReadFormat;


typedef struct {
    /* 0 */ u8 dummy;
    /* 1 */ u8 txsize;
    /* 2 */ u8 rxsize;
    /* 3 */ u8 cmd;
    /* 4 */ u8 typeh;
    /* 5 */ u8 typel;
    /* 6 */ u8 status;
    /* 7 */ u8 dummy1;
} __OSContRequesFormat;


typedef struct {
    /* 0 */ u8 dummy;
    /* 1 */ u8 txsize;
    /* 2 */ u8 rxsize;
    /* 3 */ u8 cmd;
    /* 4 */ u16 address;
    /* 6 */ u8 data[32];
    /* 38 */ u8 datacrc;
} __OSContRamReadFormat;


typedef struct {
    /* 0 */ u16 company_code;
    /* 2 */ u16 game_code;
    /* 4 */ u8 start_page;
    /* 5 */ u8 status;
    /* 6 */ u16 data_sum;
    /* 8 */ unsigned char ext_name[4];
    /* 12 */ unsigned char game_name[16];
    /* 28 */ s32 reserved;
} __OSDir;


typedef struct {
    /* 0 */ u8 inode_page[256];
} __OSInode;

#endif
