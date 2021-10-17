#include <ultra64.h>
#include <global.h>

UNK_TYPE4 __osPiAccessQueueEnabled = 0;

void __osPiCreateAccessQueue(void) {
    __osPiAccessQueueEnabled = 1;
    osCreateMesgQueue(&__osPiAccessQueue, D_8009E3F0, 1);
    osSendMesg(&__osPiAccessQueue, NULL, 0);
}

void __osPiGetAccess(void) {
    OSMesg dummyMesg;
    if (!__osPiAccessQueueEnabled) {
        __osPiCreateAccessQueue();
    }
    osRecvMesg(&__osPiAccessQueue, &dummyMesg, 1);
}

void __osPiRelAccess(void) {
    osSendMesg(&__osPiAccessQueue, NULL, 0);
}
