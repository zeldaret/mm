#ifndef OS_INTERNAL_H
#define OS_INTERNAL_H

typedef struct  {
    /* 0x00 */ OSMesgQueue* queue;
    /* 0x04 */ OSMesg msg;
} __osHwInt; // size = 0x08

#endif
