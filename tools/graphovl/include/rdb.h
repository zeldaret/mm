#ifndef _RDB_H_
#define _RDB_H_

typedef struct {
    /* 0x0 */ unsigned int type : 2;
    /* 0x0 */ unsigned int length : 2;
    /* 0x1 */ unsigned char buf[3];
} rdbPacket;

#endif
