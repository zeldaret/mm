#include "global.h"

s32 PadSetup_Init(OSMesgQueue* messageQueue, u8* outMask, OSContStatus* status) {
    s32 ret;
    s32 i;

    *outMask = 0xFF;
    ret = osContInit(messageQueue, outMask, status);
    if (ret != 0) {
        return ret;
    }
    if (*outMask == 0xFF) {
        if (osContStartQuery(messageQueue) != 0) {
            return 1;
        }
        osRecvMesg(messageQueue, NULL, 1);
        osContGetQuery(status);

        *outMask = 0;

        for (i = 0; i < 4; i++) {
            switch (status[i].errno) {
                case 0:
                    if (status[i].type == CONT_TYPE_NORMAL) {
                        *outMask |= 1 << i;
                    }
                    break;
                default:
                    break;
            }
        }
    }
    return 0;
}
