#include <ultra64.h>
#include <global.h>

void osCreatePiManager(OSPri pri, OSMesgQueue* cmdQ, OSMesg* cmdBuf, s32 cmdMsgCnt) {
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (!__osPiDevMgr.active) {
        osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
        osCreateMesgQueue(&D_8009E3D0, D_8009E3E8, 1);
        if (!__osPiAccessQueueEnabled) {
            __osPiCreateAccessQueue();
        }
        osSetEventMesg(8, &D_8009E3D0, (OSMesg)0x22222222);
        oldPri = -1;
        myPri = osGetThreadPri(NULL);
        if (myPri < pri) {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }
        savedMask = __osDisableInt();
        __osPiDevMgr.active = 1;
        __osPiDevMgr.thread = &D_8009D220;
        __osPiDevMgr.cmdQueue = cmdQ;
        __osPiDevMgr.evtQueue = &D_8009E3D0;
        __osPiDevMgr.acsQueue = &__osPiAccessQueue;
        __osPiDevMgr.dma = (s32(*)(void))osPiRawStartDma;
        __osPiDevMgr.unk18 = (s32(*)(void))func_800900C0;
        osCreateThread(&D_8009D220, 0, __osDevMgrMain, (void*)&__osPiDevMgr, &piManagerStack[4096], pri);
        osStartThread(&D_8009D220);
        __osRestoreInt(savedMask);
        if (oldPri != -1) {
            osSetThreadPri(NULL, oldPri);
        }
    }
}
