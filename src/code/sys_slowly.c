#include "slowly.h"
#include "global.h"

void Slowly_Main(SlowlyMgr* slowly) {
    slowly->status |= SLOWLY_STATUS_STARTED;

    switch (slowly->argCount) {
        case 0:
            slowly->callback.zero();
            break;

        case 1:
            slowly->callback.one(slowly->arg0);
            break;

        case 2:
            slowly->callback.two(slowly->arg0, slowly->arg1);
            break;

        default:
            break;
    }

    slowly->status |= SLOWLY_STATUS_DONE;
}

void Slowly_ThreadEntry(void* arg) {
    SlowlyMgr* slowly = (SlowlyMgr*)arg;

    Slowly_Main(slowly);
}

void Slowly_Init(SlowlyMgr* slowly, void* stack, SlowlyCallbackTwo callback, void* arg0, void* arg1) {
    bzero(slowly, sizeof(SlowlyMgr));

    slowly->argCount = 2;
    slowly->status = 0;
    slowly->callback.two = callback;
    slowly->arg0 = arg0;
    slowly->arg1 = arg1;

    osCreateThread(&slowly->thread, Z_THREAD_ID_SLOWLY, Slowly_ThreadEntry, slowly, stack, Z_PRIORITY_SLOWLY);
    osStartThread(&slowly->thread);
}

void Slowly_Destroy(SlowlyMgr* slowly) {
    osDestroyThread(&slowly->thread);
}
