#ifndef PR_SIINT_H
#define PR_SIINT_H

#include "ultratypes.h"


void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 __osSiDeviceBusy(void);
void __osSiCreateAccessQueue(void);

#endif
