#ifndef Z64SPEED_METER_H
#define Z64SPEED_METER_H

#include "PR/ultratypes.h"

struct GameState;
struct GraphicsContext;

typedef struct SpeedMeter {
    /* 0x00 */ char unk_00[0x20];
} SpeedMeter; // size = 0x20

void SpeedMeter_Init(SpeedMeter* this);
void SpeedMeter_Destroy(SpeedMeter* this);
void SpeedMeter_DrawTimeEntries(SpeedMeter* this, struct GraphicsContext* gfxCtx);
void SpeedMeter_DrawAllocEntries(SpeedMeter* this, struct GraphicsContext* gfxCtx, struct GameState* gameState);

#endif
