/*
 * File: z_dm_char04.c
 * Overlay: ovl_Dm_Char04
 * Description: Unused(?) Tatl and Tael actors
 */

#include "z_dm_char04.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar04*)thisx)

void DmChar04_Init(Actor* thisx, PlayState* play);
void DmChar04_Destroy(Actor* thisx, PlayState* play);
void DmChar04_Update(Actor* thisx, PlayState* play);
void DmChar04_Draw(Actor* thisx, PlayState* play);

void func_80AABC40(SkelAnime*, AnimationInfo* str, u16 arg2);
void func_80AABE34(DmChar04* this, PlayState* play);
s32 func_80AABF74(PlayState *play2, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx, Gfx **gfx);

#if 0
const ActorInit Dm_Char04_InitVars = {
    ACTOR_DM_CHAR04,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DmChar04),
    (ActorFunc)DmChar04_Init,
    (ActorFunc)DmChar04_Destroy,
    (ActorFunc)DmChar04_Update,
    (ActorFunc)DmChar04_Draw,
};
s32 D_80AAC460[0xC] = {
    0x0402B2E8,
    0x3F800000,
    0,
    0xBF800000,
    0,
    0,
    0x04029140,
    0x3F800000,
    0,
    0xBF800000,
    0,
    0,
};
unkStruct D_80AAC490[3] = {
    { 0x437A0000, 0x437F0000, 0x43660000, 0x437F0000 },
    { 0x41200000, 0x41200000, 0x42200000, 0x437F0000 },
    { 0x437F0000, 0x436B0000, 0x435C0000, 0x437F0000 },
};
unkStruct D_80AAC4C0[3] = {
    { 0x435C0000, 0x43200000, 0x42A00000, 0x437F0000 },
    { 0x42F00000, 0x437F0000, 0x437F0000, 0x437F0000 },
    { 0x437F0000, 0x436B0000, 0x435C0000, 0x437F0000 },
};
static Vec3f D_80AAC4F0 = { 0.0f, 0.0f, 0.0f };
#endif

extern unkStruct D_80AAC490[];
extern unkStruct D_80AAC4C0[];
extern AnimationHeader D_04029140;
extern SkeletonHeader D_0402AF58;
extern AnimationInfo D_80AAC460[];
extern Vec3f D_80AAC4F0;
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/func_80AABC40.s")

void func_80AABC40(SkelAnime* arg0, AnimationInfo* animation, u16 arg2) {
    f32 phi_fv1;

    animation += arg2;

    if (animation->frameCount < 0.0f) {
        phi_fv1 = Animation_GetLastFrame(animation->animation);
    } else {
        phi_fv1 = animation->frameCount;
    }
    Animation_Change(arg0, animation->animation, animation->playSpeed, animation->startFrame, phi_fv1, animation->mode,
                     animation->morphFrames);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/DmChar04_Init.s")

void DmChar04_Init(Actor* thisx, PlayState* play) {
    DmChar04* this = THIS;
    this->str = D_80AAC490[this->actor.params];
    this->str2 = D_80AAC4C0[this->actor.params];
    this->actor.targetArrowOffset = 3000.0f;
    this->unk260 = 0x63;
    this->unk262 = this->actor.params << 0xB;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 24.0f);
    SkelAnime_Init(play, &this->unk144, &D_0402AF58, &D_04029140, &this->jointTable, &this->morphTable, 7);
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 15.0f);
    func_80AABC40(&this->unk144, &D_80AAC460, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_80AABE34;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/DmChar04_Destroy.s")
void DmChar04_Destroy(Actor* thisx, PlayState* play) {
}
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/func_80AABE34.s")

void func_80AABE34(DmChar04* this, PlayState* play) {
    u16 params = this->actor.params + 0x71;

    if (Cutscene_CheckActorAction(play, params) != 0) {
        s32 actionIndex = Cutscene_GetActorActionIndex(play, params);

        if (play->csCtx.frames == play->csCtx.actorActions[actionIndex]->startFrame) {
            if (this->unk260 != play->csCtx.actorActions[actionIndex]->action) {
                this->unk260 = play->csCtx.actorActions[actionIndex]->action;
                if (play->csCtx.actorActions[actionIndex]->action == 1) {
                    this->unk261 = 0;
                } else {
                    this->unk261 = 0;
                }
                func_80AABC40(&this->unk144, &D_80AAC460[this->unk261], 0);
            }
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, play, actionIndex);
    } else {
        this->unk260 = 0x63;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/DmChar04_Update.s")
void DmChar04_Update(Actor* thisx, PlayState* play) {
    DmChar04* this = THIS;

    SkelAnime_Update(&this->unk144);
    this->actionFunc(this, play);
    this->unk262++;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/func_80AABF74.s")
s32 func_80AABF74(PlayState *play2, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx, Gfx **gfx) {
    PlayState* play = play2;
    f32 sp28;
    Vec3f sp1C;
    DmChar04* this = THIS;
    if (limbIndex == 6) {
        sp28 = ((Math_SinS((this->unk262 << 0xC)) * 0.1f) + 1.0f) * 0.012f * (this->actor.scale.x * 124.99999f);
        Matrix_MultVec3f(&D_80AAC4F0, &sp1C);
        Matrix_Translate( sp1C.x, sp1C.y, sp1C.z, MTXMODE_NEW);
        Matrix_Scale(sp28, sp28, sp28, MTXMODE_APPLY);
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char04/DmChar04_Draw.s")
