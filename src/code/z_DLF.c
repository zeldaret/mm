#include "global.h"
#include "system_malloc.h"
#include "z64load.h"

void Overlay_LoadGameState(GameStateOverlay* gameState) {
    void* temp;
    void* vrStart;

    if (gameState->loadedRamAddr != NULL) {
        return;
    }
    vrStart = gameState->vramStart;
    if (vrStart == NULL) {
        gameState->unk_28 = 0;
    } else {
        gameState->loadedRamAddr = Load2_AllocateAndLoad(gameState->vromStart, gameState->vromEnd, (uintptr_t)vrStart,
                                                         (uintptr_t)gameState->vramEnd);
        if (gameState->loadedRamAddr == NULL) {
            return;
        }

        if (gameState->unk_14 != NULL) {
            temp = (void*)((uintptr_t)gameState->unk_14 - (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState));
        } else {
            temp = NULL;
        }
        gameState->unk_14 = temp;
        if (gameState->init != NULL) {
            temp = (void*)((uintptr_t)gameState->init - (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState));
        } else {
            temp = NULL;
        }
        gameState->init = temp;

        if (gameState->destroy != NULL) {
            temp = (void*)((uintptr_t)gameState->destroy - (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState));
        } else {
            temp = NULL;
        }
        gameState->destroy = temp;

        if (gameState->unk_20 != NULL) {
            temp = (void*)((uintptr_t)gameState->unk_20 - (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState));
        } else {
            temp = NULL;
        }
        gameState->unk_20 = temp;

        if (gameState->unk_24 != NULL) {
            temp = (void*)((uintptr_t)gameState->unk_24 - (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState));
        } else {
            temp = NULL;
        }
        gameState->unk_24 = temp;

        gameState->unk_28 = 0;
    }
}

void Overlay_FreeGameState(GameStateOverlay* gameState) {
    s32 var_v0;
    void* temp;

    if (gameState->loadedRamAddr != NULL) {
        var_v0 = gameState->unk_28 != 0 ? -1 : 0;
        if (var_v0 == 0) {
            if (gameState->unk_14 != NULL) {
                temp = (void*)((uintptr_t)gameState->unk_14 + (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState));
            } else {
                temp = NULL;
            }
            gameState->unk_14 = temp;
            if (gameState->init != NULL) {
                temp = (void*)((uintptr_t)gameState->init + (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState));
            } else {
                temp = NULL;
            }
            gameState->init = temp;

            if (gameState->destroy != NULL) {
                temp = (void*)((uintptr_t)gameState->destroy + (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState));
            } else {
                temp = NULL;
            }
            gameState->destroy = temp;

            if (gameState->unk_20 != NULL) {
                temp = (void*)((uintptr_t)gameState->unk_20 + (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState));
            } else {
                temp = NULL;
            }
            gameState->unk_20 = temp;

            if (gameState->unk_24 != NULL) {
                temp = (void*)((uintptr_t)gameState->unk_24 + (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState));
            } else {
                temp = NULL;
            }
            gameState->unk_24 = temp;
            SystemArena_Free(gameState->loadedRamAddr);
            gameState->loadedRamAddr = NULL;
        }
    }
}
