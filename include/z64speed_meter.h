#ifndef Z64SPEED_METER_H
#define Z64SPEED_METER_H

#include "PR/ultratypes.h"

typedef struct SpeedMeter {
    /* 0x00 */ char unk_00[0x1C];
} SpeedMeter; // size = 0x20

struct GameState;
struct GraphicsContext;

void SpeedMeter_Init(SpeedMeter* this);
void SpeedMeter_Destroy(SpeedMeter* this);
void SpeedMeter_DrawTimeEntries(SpeedMeter* this, struct GraphicsContext* gfxCtx);
void SpeedMeter_DrawAllocEntries(SpeedMeter* this, struct GraphicsContext* gfxCtx, struct GameState* gameState);

#endif
