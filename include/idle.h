#ifndef IDLE_H
#define IDLE_H

#include "ultra64.h"

extern OSMesgQueue gPiMgrCmdQueue;
extern OSViMode gViConfigMode;
extern u8 gViConfigModeType;

extern u8 D_80096B20;
extern vu8 gViConfigUseBlack;
extern u8 gViConfigAdditionalScanLines;
extern u32 gViConfigFeatures;
extern f32 gViConfigXScale;
extern f32 gViConfigYScale;

void Idle_ThreadEntry(void* arg);

#endif
