#ifndef Z64RUMBLE_H
#define Z64RUMBLE_H

#include "PR/ultratypes.h"
#include "io/controller.h"

typedef enum RumbleManagerState {
    /* 0 */ RUMBLEMANAGER_STATE_WIPE, // Disables the request processing and wipes every request. It can be either set manually or automatically by the system as fail-safe in case the Rumble Pak has been vibrating for 2 minutes
    /* 1 */ RUMBLEMANAGER_STATE_RUNNING, // Normal execution and updating
    /* 2 */ RUMBLEMANAGER_STATE_INITIAL // Indicates initialization and cleanup must be done before processing the rumble requests. All the old requests on are wiped on this state. Then it proceeds to RUMBLEMANAGER_STATE_RUNNING
} RumbleManagerState;

#define RUMBLE_REQUEST_BUFFER_SIZE 0x40

typedef struct RumbleManager {
    /* 0x000 */ u8 rumbleEnabled[MAXCONTROLLERS];
    /* 0x004 */ u8 unk_04[RUMBLE_REQUEST_BUFFER_SIZE];
    /* 0x044 */ u8 timer[RUMBLE_REQUEST_BUFFER_SIZE]; // amount of ticks this request will run before unk_04 starts decreasing
    /* 0x084 */ u8 decreaseStep[RUMBLE_REQUEST_BUFFER_SIZE]; // used to decrease unk_04 by this amount each tick after timer runs out
    /* 0x0C4 */ u8 unk_C4[RUMBLE_REQUEST_BUFFER_SIZE];
    /* 0x104 */ u8 state;
    /* 0x105 */ u8 updateEnabled; // boolean value which controls if the Update function should be run. Contrary to RUMBLEMANAGER_STATE_WIPE, disabling this does not wipe the state of the requests
    /* 0x106 */ u16 rumblingTimer; // amount of "ticks" updates the Rumble Pak has been rumbling without pause. It is restarted after 5 ticks of not rumbling
    /* 0x108 */ u16 unk_108; // small counter/timer used to restart rumblingTimer?
    /* 0x10A */ u8 unk_10A;
    /* 0x10B */ u8 overrideTimer;
    /* 0x10C */ u8 overrideDecreaseStep;
    /* 0x10D */ u8 unk_10D;
} RumbleManager; // size = 0x10E

extern RumbleManager gRumbleMgr;

void Rumble_Override(f32 distSq, u8 arg1, u8 ticksTimer, u8 decreaseStep);
void Rumble_Request(f32 distSq, u8 arg1, u8 ticksTimer, u8 decreaseStep);
void Rumble_Init(void);
void Rumble_Destroy(void);
s32 Rumble_ControllerOneHasRumblePak(void);
void Rumble_StateReset(void);
void Rumble_StateWipeRequests(void);
void Rumble_SetUpdateEnabled(s32 updateEnabled);

void RumbleManager_Update(RumbleManager* rumbleMgr);
void RumbleManager_Init(RumbleManager* rumbleMgr);
void RumbleManager_Destroy(RumbleManager* rumbleMgr);

#endif
