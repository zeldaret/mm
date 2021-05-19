#include <ultra64.h>
#include <global.h>

#define SLOWLY_STATUS_DONE (1 << 0)
#define SLOWLY_STATUS_STARTED (1 << 1)

void Slowly_Main(SlowlyTask* slowly) {
    slowly->status |= SLOWLY_STATUS_STARTED;

    switch (slowly->callbackArgCount) {
        case SLOWLY_CALLBACK_NO_ARGS:
            slowly->callback0();
            break;
        case SLOWLY_CALLBACK_ONE_ARG:
            slowly->callback1(slowly->callbackArg0);
            break;
        case SLOWLY_CALLBACK_TWO_ARGS:
            slowly->callback2(slowly->callbackArg0, slowly->callbackArg1);
            break;
    }

    slowly->status |= SLOWLY_STATUS_DONE;
}

void Slowly_ThreadEntry(SlowlyTask* slowly) {
    Slowly_Main(slowly);
}

void Slowly_Start(SlowlyTask* slowly, void* stack, void (*callback)(), void* callbackArg0, void* callbackArg1) {
    bzero(slowly, sizeof(SlowlyTask));

    slowly->callbackArgCount = SLOWLY_CALLBACK_TWO_ARGS;
    slowly->status = 0;
    slowly->callback0 = callback;
    slowly->callbackArg0 = callbackArg0;
    slowly->callbackArg1 = callbackArg1;

    osCreateThread(&slowly->thread, Z_THREAD_ID_SLOWLY, Slowly_ThreadEntry, slowly, stack, Z_PRIORITY_SLOWLY);
    osStartThread(&slowly->thread);
}

void Slowly_Stop(SlowlyTask* slowly) {
    osDestroyThread(&slowly->thread);
}
