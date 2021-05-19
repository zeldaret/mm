#include <ultra64.h>
#include <global.h>

int osSetTimer(OSTimer* t, OSTime value, OSTime interval, OSMesgQueue* mq, OSMesg msg) {
    OSTime tim;
    OSTimer* spC;
    u32 sp14;
    u32 sp10;
    u32 saveMask;

    t->next = NULL;
    t->prev = NULL;
    t->interval = interval;
    if (value != 0) {
        t->value = value;
    } else {
        t->value = interval;
    }
    t->mq = mq;
    t->msg = msg;

    saveMask = __osDisableInt();

    if (__osTimerList->next != __osTimerList) {
        if (0) {
            ;
        }
        spC = __osTimerList->next;
        sp14 = osGetCount();
        sp10 = sp14 - __osTimerCounter;
        if (sp10 < spC->value) {
            spC->value -= sp10;
        } else {
            spC->value = 1;
        }
    }

    tim = __osInsertTimer(t);
    __osSetTimerIntr(__osTimerList->next->value);

    __osRestoreInt(saveMask);

    return 0;
}
