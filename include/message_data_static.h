#ifndef MESSAGE_DATA_STATIC_H_
#define MESSAGE_DATA_STATIC_H_

#include "PR/ultratypes.h"

typedef struct MessageTableEntry{
    /* 0x0000 */ u16 textId;
    /* 0x0002 */ u8 typePos;
    /* 0x0004 */ const char* segment;
} MessageTableEntry; // size = 0x8;

#endif
