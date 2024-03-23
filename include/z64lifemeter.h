#ifndef Z64LIFEMETER_H
#define Z64LIFEMETER_H

#include "PR/ultratypes.h"

struct PlayState;

void LifeMeter_Init(struct PlayState* play);
void LifeMeter_UpdateColors(struct PlayState* play);
s32 LifeMeter_SaveInterfaceHealth(struct PlayState* play);
s32 LifeMeter_IncreaseInterfaceHealth(struct PlayState* play);
s32 LifeMeter_DecreaseInterfaceHealth(struct PlayState* play);
void LifeMeter_Draw(struct PlayState* play);
void LifeMeter_UpdateSizeAndBeep(struct PlayState* play);
u32 LifeMeter_IsCritical(void);

#endif
