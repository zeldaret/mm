#include "PR/os_internal.h"
#include "PR/osint.h"

void __osGetHWIntrRoutine(OSHWIntr interrupt, OSMesgQueue** outQueue, OSMesg* outMsg) {
    *outQueue = __osHwIntTable[interrupt].queue;
    *outMsg = __osHwIntTable[interrupt].msg;
}
