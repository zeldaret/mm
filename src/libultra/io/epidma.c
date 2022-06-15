#include "global.h"

s32 osEPiStartDma(OSPiHandle* pihandle, OSIoMesg* mb, s32 direction) {
    register s32 result;

    if (!__osPiDevMgr.active) {
        return -1;
    }

    mb->piHandle = pihandle;

    if (direction == 0) {
        mb->hdr.type = 15;
    } else {
        mb->hdr.type = 16;
    }

    if (mb->hdr.pri == 1) {
        result = osJamMesg(osPiGetCmdQueue(), mb, OS_MESG_NOBLOCK);
    } else {
        result = osSendMesg(osPiGetCmdQueue(), mb, OS_MESG_NOBLOCK);
    }
    return result;
}
