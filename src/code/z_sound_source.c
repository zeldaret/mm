#include "global.h"

void SoundSource_InitAll(GlobalContext* globalCtx) {
    SoundSource* sources = &globalCtx->soundSources[0];
    s32 i;

    // clang-format off
    for (i = 0; i < ARRAY_COUNT(globalCtx->soundSources); i++) { sources[i].countdown = 0; }
    // clang-format on
}

void SoundSource_UpdateAll(GlobalContext* globalCtx) {
    SoundSource* source = &globalCtx->soundSources[0];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(globalCtx->soundSources); i++) {
        if (source->countdown != 0) {
            if (DECR(source->countdown) == 0) {
                Audio_StopSfxByPos(&source->projectedPos);
            } else {
                SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->viewProjectionMtxF, &source->worldPos, &source->projectedPos);
                if (source->playSfxEachFrame) {
                    Audio_PlaySfxAtPos(&source->projectedPos, source->sfxId);
                }
            }
        }

        source++;
    }
}

void SoundSource_Add(GlobalContext* globalCtx, Vec3f* worldPos, u32 duration, u16 sfxId, u32 playSfxEachFrame) {
    s32 countdown;
    SoundSource* source;
    s32 smallestCountdown = 0xFFFF;
    SoundSource* backupSource = NULL;
    s32 i;

    source = &globalCtx->soundSources[0];
    for (i = 0; i < ARRAY_COUNT(globalCtx->soundSources); i++) {
        if (source->countdown == 0) {
            break;
        }

        // Store the sound source with the smallest remaining countdown
        countdown = source->countdown;
        if (countdown < smallestCountdown) {
            smallestCountdown = countdown;
            backupSource = source;
        }
        source++;
    }

    // If no sound source is available, replace the sound source with the smallest remaining countdown
    if (i >= ARRAY_COUNT(globalCtx->soundSources)) {
        source = backupSource;
        Audio_StopSfxByPos(&source->projectedPos);
    }

    source->worldPos = *worldPos;
    source->countdown = duration;
    source->playSfxEachFrame = playSfxEachFrame;
    source->sfxId = sfxId;

    SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->viewProjectionMtxF, &source->worldPos, &source->projectedPos);
    Audio_PlaySfxAtPos(&source->projectedPos, sfxId);
}

void SoundSource_PlaySfxAtFixedWorldPos(GlobalContext* globalCtx, Vec3f* worldPos, u32 duration, u16 sfxId) {
    SoundSource_Add(globalCtx, worldPos, duration, sfxId, false);
}

void SoundSource_PlaySfxEachFrameAtFixedWorldPos(GlobalContext* globalCtx, Vec3f* worldPos, u32 duration, u16 sfxId) {
    SoundSource_Add(globalCtx, worldPos, duration, sfxId, true);
}
