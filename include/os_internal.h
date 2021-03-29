#ifndef _OS_INTERNAL_H_
#define _OS_INTERNAL_H_

typedef struct  {
    /* 0x00 */ OSMesgQueue* queue;
    /* 0x04 */ OSMesg msg;
} __osHwInt; // size = 0x08

#endif
