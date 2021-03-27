#include <ultra64.h>
#include <global.h>

s32 osEPiLinkHandle(OSPiHandle* handle) {
    u32 saveMask = __osDisableInt();

    handle->next = __osPiTable;
    __osPiTable = handle;

    __osRestoreInt(saveMask);

    return 0;
}
