#include <PR/ultratypes.h>
#include <osint.h>

void __osDequeueThread(OSThread** queue, OSThread* t)
{
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
