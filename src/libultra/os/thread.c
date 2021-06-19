#include <ultra64.h>
#include <global.h>

OSThread* __osThreadTail = NULL;
UNK_TYPE D_80097E14 = -1;
OSThread* __osRunQueue = (OSThread*)&__osThreadTail;
OSThread* __osActiveQueue = (OSThread*)&__osThreadTail;
OSThread* __osRunningThread = NULL;
OSThread* __osFaultedThread = NULL;

void __osDequeueThread(OSThread** queue, OSThread* t) {
    register OSThread* pred;
    register OSThread* succ;

    pred = (OSThread*)queue; //! This seems questionable, but the function matches...
    succ = pred->next;
    while (succ != NULL) {
        if (succ == t) {
            pred->next = t->next;
            return;
        }
        pred = succ;
        succ = pred->next;
    }
}
