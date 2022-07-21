#include "global.h"
#include "system_malloc.h"
#include "z64load.h"

void Overlay_LoadGameState(GameStateOverlay* gameState) {
    void* vramStart;

    if (gameState->loadedRamAddr != NULL) {
        return;
    }
    vramStart = gameState->vramStart;
    if (vramStart == NULL) {
        gameState->unk_28 = 0;
        return;
    }
    gameState->loadedRamAddr = Load2_AllocateAndLoad(gameState->vromStart, gameState->vromEnd, (uintptr_t)vramStart,
                                                     (uintptr_t)gameState->vramEnd);
    if (gameState->loadedRamAddr != NULL) {

        gameState->unk_14 =
            (uintptr_t)((gameState->unk_14 != NULL)
                            ? (void*)((uintptr_t)gameState->unk_14 - (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState))
                            : NULL);
        gameState->init =
            (uintptr_t)((gameState->init != NULL)
                            ? (void*)((uintptr_t)gameState->init - (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState))
                            : NULL);
        gameState->destroy =
            (uintptr_t)((gameState->destroy != NULL)
                            ? (void*)((uintptr_t)gameState->destroy - (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState))
                            : NULL);
        gameState->unk_20 =
            (uintptr_t)((gameState->unk_20 != NULL)
                            ? (void*)((uintptr_t)gameState->unk_20 - (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState))
                            : NULL);
        gameState->unk_24 =
            (uintptr_t)((gameState->unk_24 != NULL)
                            ? (void*)((uintptr_t)gameState->unk_24 - (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState))
                            : NULL);

        gameState->unk_28 = 0;
    }
}

void Overlay_FreeGameState(GameStateOverlay* gameState) {
    s32 var_v0;

    if (gameState->loadedRamAddr != NULL) {
        var_v0 = gameState->unk_28 != 0 ? -1 : 0;
        if (var_v0 == 0) {
            gameState->unk_14 =
                (uintptr_t)((gameState->unk_14 != NULL)
                                ? (void*)((uintptr_t)gameState->unk_14 + (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState))
                                : NULL);
            gameState->init =
                (uintptr_t)((gameState->init != NULL)
                                ? (void*)((uintptr_t)gameState->init + (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState))
                                : NULL);
            gameState->destroy = (uintptr_t)(
                (gameState->destroy != NULL)
                    ? (void*)((uintptr_t)gameState->destroy + (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState))
                    : NULL);
            gameState->unk_20 =
                (uintptr_t)((gameState->unk_20 != NULL)
                                ? (void*)((uintptr_t)gameState->unk_20 + (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState))
                                : NULL);
            gameState->unk_24 =
                (uintptr_t)((gameState->unk_24 != NULL)
                                ? (void*)((uintptr_t)gameState->unk_24 + (intptr_t)OVERLAY_RELOCATION_OFFSET(gameState))
                                : NULL);
            SystemArena_Free(gameState->loadedRamAddr);
            gameState->loadedRamAddr = NULL;
        }
    }
}
