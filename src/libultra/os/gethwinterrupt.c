#include "global.h"
#include "ultra64/os_internal.h"
#include "ultra64/osint.h"

void __osGetHWIntrRoutine(s32 idx, OSMesgQueue** outQueue, OSMesg* outMsg) {
    *outQueue = __osHwIntTable[idx].queue;
    *outMsg = __osHwIntTable[idx].msg;
}
