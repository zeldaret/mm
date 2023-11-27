#ifndef LIBC64_SLEEP_H
#define LIBC64_SLEEP_H

#include "ultra64.h"

void csleep(OSTime time);
void nsleep(u32 nsec);
void usleep(u32 usec);
void msleep(u32 msec);
void sleep(u32 sec);

#endif
