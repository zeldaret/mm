#ifndef KALEIDO_MANAGER_H
#define KALEIDO_MANAGER_H

#include "ultra64.h"
#include "romfile.h"

struct PlayState;

typedef enum KaleidoMgrOverlayType {
    /* 0 */ KALEIDO_OVL_KALEIDO_SCOPE,
    /* 1 */ KALEIDO_OVL_PLAYER_ACTOR,
    /* 2 */ KALEIDO_OVL_MAX
} KaleidoMgrOverlayType;

typedef struct KaleidoMgrOverlay {
    /* 0x00 */ void* loadedRamAddr;
    /* 0x04 */ RomFile file;
    /* 0x0C */ void* vramStart;
    /* 0x10 */ void* vramEnd;
    /* 0x14 */ uintptr_t offset; // loadedRamAddr - vramStart
    /* 0x18 */ const char* name;
} KaleidoMgrOverlay; // size = 0x1C


// z_kaleido_manager.c

void KaleidoManager_LoadOvl(KaleidoMgrOverlay* ovl);
void KaleidoManager_ClearOvl(KaleidoMgrOverlay* ovl);
void KaleidoManager_Init(struct PlayState* play);
void KaleidoManager_Destroy(void);
void* KaleidoManager_GetRamAddr(void* vram);

extern KaleidoMgrOverlay gKaleidoMgrOverlayTable[KALEIDO_OVL_MAX];
extern KaleidoMgrOverlay* gKaleidoMgrCurOvl;


// z_kaleido_scope_call.c

void KaleidoScopeCall_LoadPlayer(void);
void KaleidoScopeCall_Init(struct PlayState* play);
void KaleidoScopeCall_Destroy(struct PlayState* play);
void KaleidoScopeCall_Update(struct PlayState* play);
void KaleidoScopeCall_Draw(struct PlayState* play);

#endif
