#include "global.h"

UNK_TYPE4 D_80097E40 = 0;

OSPifRam __osContPifRam;
u8 __osContLastPoll;
u8 __osMaxControllers;

OSTimer __osEepromTimer;
OSMesgQueue D_8009CF38;
OSMesg D_8009CF50[1];

s32 osContInit(OSMesgQueue* mq, u8* bitpattern, OSContStatus* data) {
    OSMesg dummy;
    s32 ret = 0;
    OSTime t;
    OSTimer mytimer;
    OSMesgQueue timerMesgQueue;

    if (D_80097E40 != 0) {
        return 0;
    }

    D_80097E40 = 1;

    t = osGetTime();
    if (t < 0x165A0BC) {
        osCreateMesgQueue(&timerMesgQueue, &dummy, 1);
        osSetTimer(&mytimer, 0x165A0BC - t, 0, &timerMesgQueue, &dummy);
        osRecvMesg(&timerMesgQueue, &dummy, OS_MESG_BLOCK);
    }

    __osMaxControllers = 4;

    __osPackRequestData(0);

    ret = __osSiRawStartDma(OS_WRITE, &__osContPifRam);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);

    ret = __osSiRawStartDma(OS_READ, &__osContPifRam);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);

    __osContGetInitData(bitpattern, data);
    __osContLastPoll = 0;
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&D_8009CF38, D_8009CF50, ARRAY_COUNT(D_8009CF50));

    return ret;
}

void __osContGetInitData(u8* pattern, OSContStatus* data) {
    u8* ptr;
    __OSContRequestHeader requestHeader;
    s32 i;
    u8 bits;

    bits = 0;
    ptr = (u8*)__osContPifRam.ramarray;
    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(requestHeader), data++) {
        requestHeader = *(__OSContRequestHeader*)ptr;
        data->errno = (requestHeader.rxsize & 0xc0) >> 4;
        if (data->errno == 0) {
            data->type = requestHeader.typel << 8 | requestHeader.typeh;
            data->status = requestHeader.status;

            bits |= 1 << i;
        }
    }
    *pattern = bits;
}

void __osPackRequestData(u8 poll) {
    u8* ptr;
    __OSContRequestHeader requestHeader;
    s32 i;

    for (i = 0; i < 0xF; i++) {
        __osContPifRam.ramarray[i] = 0;
    }

    __osContPifRam.status = 1;
    ptr = (u8*)__osContPifRam.ramarray;
    requestHeader.align = 255;
    requestHeader.txsize = 1;
    requestHeader.rxsize = 3;
    requestHeader.poll = poll;
    requestHeader.typeh = 255;
    requestHeader.typel = 255;
    requestHeader.status = 255;
    requestHeader.align1 = 255;

    for (i = 0; i < __osMaxControllers; i++) {
        *(__OSContRequestHeader*)ptr = requestHeader;
        ptr += sizeof(requestHeader);
    }
    *ptr = 254;
}
