#include "global.h"
#include "PR/os_internal.h"
#include "PR/osint.h"

void __osGetHWIntrRoutine(OSHWIntr idx, OSMesgQueue** outQueue, OSMesg* outMsg) {
    *outQueue = __osHwIntTable[idx].queue;
    *outMsg = __osHwIntTable[idx].msg;
}
