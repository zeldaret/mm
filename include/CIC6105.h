#ifndef CIC6105_H
#define CIC6105_H

#include "ultra64.h"

#include "versions.h"

// IPL3 puts values in those addresses as part of the anti-piracy checks
#define CIC_ADDRESS_1 0x002FB1F4
#define CIC_ADDRESS_2 0x002FE1C0


void CIC6105_Noop1(void);
void CIC6105_Noop2(void);
void CIC6105_PrintRomInfo(void);
void CIC6105_AddRomInfoFaultPage(void);
void CIC6105_Destroy(void);
void CIC6105_Init(void);

#if MM_VERSION <= N64_JP_1_1
void func_80081980_unknown(void);
#endif

extern s32 gCICAddr1Val;
extern s32 gCICAddr2Val;

#endif
