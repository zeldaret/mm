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
                Audio_StopSfxByPos(&source->relativePos);
            } else {
                SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->projectionMatrix, &source->originPos, &source->relativePos);
                if (source->isSfxPlayedEachFrame) {
                    Audio_PlaySfxByPos(&source->relativePos, source->sfxId);
                }
            }
        }

        source++;
    }
}

void SoundSource_Add(GlobalContext* globalCtx, Vec3f* pos, u32 duration, u16 sfxId, u32 isSfxPlayedEachFrame) {
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

        countdown = source->countdown;
        if (countdown < smallestCountdown) {
            smallestCountdown = countdown;
            backupSource = source;
        }
        source++;
    }

    if (i >= ARRAY_COUNT(globalCtx->soundSources)) {
        source = backupSource;
        Audio_StopSfxByPos(&source->relativePos);
    }

    source->originPos = *pos;
    source->countdown = duration;
    source->isSfxPlayedEachFrame = isSfxPlayedEachFrame;
    source->sfxId = sfxId;

    SkinMatrix_Vec3fMtxFMultXYZ(&globalCtx->projectionMatrix, &source->originPos, &source->relativePos);
    Audio_PlaySfxByPos(&source->relativePos, sfxId);
}

void SoundSource_PlaySfxFollowingPos(GlobalContext* globalCtx, Vec3f* pos, u32 duration, u16 sfxId) {
    SoundSource_Add(globalCtx, pos, duration, sfxId, false);
}

void SoundSource_PlaySfxEachFrameFollowingPos(GlobalContext* globalCtx, Vec3f* pos, u32 duration, u16 sfxId) {
    SoundSource_Add(globalCtx, pos, duration, sfxId, true);
}
