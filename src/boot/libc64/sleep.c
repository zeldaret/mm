#include "libc64/sleep.h"
#include "macros.h" // for ARRAY_COUNT

void csleep(OSTime time) {
    OSMesgQueue mq;
    OSMesg msg[1];
    OSTimer timer;

    osCreateMesgQueue(&mq, msg, ARRAY_COUNT(msg));
    osSetTimer(&timer, time, 0, &mq, NULL);
    osRecvMesg(&mq, NULL, OS_MESG_BLOCK);
}

void nsleep(u32 nsec) {
    csleep(OS_NSEC_TO_CYCLES(nsec));
}

void usleep(u32 usec) {
    csleep(OS_USEC_TO_CYCLES(usec));
}

void msleep(u32 msec) {
    csleep((msec * OS_CPU_COUNTER) / 1000ULL);
}

void sleep(u32 sec) {
    csleep(sec * OS_CPU_COUNTER);
}
