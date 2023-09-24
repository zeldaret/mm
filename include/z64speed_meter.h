#ifndef Z64SPEED_METER_H
#define Z64SPEED_METER_H

#include "PR/ultratypes.h"

struct GameState;
struct GraphicsContext;

typedef struct SpeedMeter {
    /* 0x00 */ char unk_00[0x18];
    /* 0x18 */ s32 x; // Unused
    /* 0x1C */ s32 y;
} SpeedMeter; // size = 0x20

typedef struct {
    /* 0x00 */ s32 maxval;
    /* 0x04 */ s32 val;
    /* 0x08 */ u16 backColor;
    /* 0x0A */ u16 foreColor;
    /* 0x0C */ s32 ulx;
    /* 0x10 */ s32 lrx;
    /* 0x14 */ s32 uly;
    /* 0x18 */ s32 lry;
} SpeedMeterAllocEntry; // size = 0x1C

void SpeedMeter_Init(SpeedMeter* this);
void SpeedMeter_Destroy(SpeedMeter* this);
void SpeedMeter_DrawTimeEntries(SpeedMeter* this, struct GraphicsContext* gfxCtx);
void SpeedMeter_DrawAllocEntries(SpeedMeter* this, struct GraphicsContext* gfxCtx, struct GameState* state);

extern volatile OSTime gRSPAudioTimeTotal;
extern volatile OSTime gRSPGfxTimeTotal;
extern volatile OSTime gRDPTimeTotal;
extern volatile OSTime gGraphUpdatePeriod;
extern volatile OSTime gRSPAudioTimeAcc;
extern volatile OSTime gRSPGfxTimeAcc;
extern volatile OSTime gRSPOtherTimeAcc;
extern volatile OSTime D_801FBB18;
extern volatile OSTime gRDPTimeAcc;

#endif
