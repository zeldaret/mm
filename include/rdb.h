#ifndef _RDB_H_
#define _RDB_H_

typedef struct {
    /* 0 */ unsigned int type : 2;
    /* 0 */ unsigned int length : 2;
    /* 1 */ unsigned char buf[3];
} rdbPacket;

#endif
