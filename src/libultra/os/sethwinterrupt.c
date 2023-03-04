#include "global.h"
#include "ultra64/osint.h"

void __osSetHWIntrRoutine(OSHWIntr idx, OSMesgQueue* queue, OSMesg msg) {
    register s32 prevInt = __osDisableInt();

    __osHwIntTable[idx].queue = queue;
    __osHwIntTable[idx].msg = msg;

    __osRestoreInt(prevInt);
}
