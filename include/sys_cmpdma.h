#ifndef SYS_CPMDMA_H
#define SYS_CPMDMA_H

#include "PR/ultratypes.h"
#include "stdint.h"

void CmpDma_LoadFile(uintptr_t segmentVrom, s32 id, void* dst, size_t size);
void CmpDma_LoadAllFiles(uintptr_t segmentVrom, void* dst, size_t size);

#endif
