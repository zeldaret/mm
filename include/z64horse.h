#ifndef Z64_HORSE_H
#define Z64_HORSE_H

#include "ultra64.h"
#include "z64.h"


s32 func_800F3940(PlayState* play);
s32 func_800F39B4(PlayState* play, s32 pathIndex, s32 pointIndex, Vec3s* dst, s16* arg4);
s32 func_800F3A64(s16 sceneId);
void func_800F3B2C(PlayState* play);
void func_800F40A0(PlayState* play, Player* player);
void Horse_RotateToPoint(Actor* actor, Vec3f* pos, s16 turnAmount);
s32 func_800F41E4(PlayState* play, ActorContext* actorCtx);


extern s32 D_801BDA9C;
extern s32 D_801BDAA0;
extern s32 D_801BDAA4;

#endif
