#ifndef PR_PIINT_H
#define PR_PIINT_H

#include "ultratypes.h"
#include "os_pi.h"
#include "libc/stdint.h"


void __osDevMgrMain(void* arg);
void __osPiCreateAccessQueue(void);
void __osPiRelAccess(void);
void __osPiGetAccess(void);
s32 __osPiRawStartDma(s32 direction, uintptr_t devAddr, void* dramAddr, size_t size);
s32 __osEPiRawWriteIo(OSPiHandle* handle, uintptr_t devAddr, u32 data);
s32 __osEPiRawReadIo(OSPiHandle* handle, uintptr_t devAddr, u32* data);
s32 __osEPiRawStartDma(OSPiHandle* handle, s32 direction, uintptr_t cartAddr, void* dramAddr, size_t size);
OSMesgQueue* osPiGetCmdQueue(void);


#endif
