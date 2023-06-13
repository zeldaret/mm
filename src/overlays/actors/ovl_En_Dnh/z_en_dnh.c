/*
 * File: z_en_dnh.c
 * Overlay: ovl_En_Dnh
 * Description: Koume in boat house
 */

#include "z_en_dnh.h"
#include "objects/object_tro/object_tro.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnDnh*)thisx)

void EnDnh_Init(Actor* thisx, PlayState* play);
void EnDnh_Destroy(Actor* thisx, PlayState* play);
void EnDnh_Update(Actor* thisx, PlayState* play);
void EnDnh_Draw(Actor* thisx, PlayState* play);

void func_80A50F38(EnDnh* this, PlayState* play);
void func_80A50F9C(EnDnh* this, PlayState* play);

#if 0
ActorInit En_Dnh_InitVars = {
    ACTOR_EN_DNH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRO,
    sizeof(EnDnh),
    (ActorFunc)EnDnh_Init,
    (ActorFunc)EnDnh_Destroy,
    (ActorFunc)EnDnh_Update,
    (ActorFunc)EnDnh_Draw,
};

#endif

extern UNK_TYPE D_06002950;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50D40.s")
void* func_80A50D40(Actor *arg0, PlayState *arg1) {
    func_800B7298(arg1, arg0, 7U);
    if (gSaveContext.eventInf[3] & 0x20) {
        arg1->nextEntrance = 0xC60;
    } else {
        arg1->nextEntrance = 0x8460;
    }
    gSaveContext.nextCutsceneIndex = 0;
    arg1->transitionTrigger = 0x14;
    arg1->transitionType = 3;
    gSaveContext.nextTransitionType = 7;
    gSaveContext.save.saveInfo.weekEventReg[0x5A] &= 0xBF;
    gSaveContext.eventInf[5] &= 0xFE;
    return 1;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50DF8.s")
extern s32 D_80A51250;
extern s32 D_80A51384;
extern s32 D_80A5138C;

void* func_80A50DF8(EnDnh* this, PlayState* play) {
    switch (this->unk198) {
        case 1:
            return &D_80A51384;
        case 2:
            return &D_80A5138C;
        default:
            return &D_80A51250;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50E40.s")
s32 func_80A50E40(EnDnh* this, PlayState* play) {
    if (!(this->unk18C & 7) || (Actor_ProcessTalkRequest(&this->actor, &play->state) == 0)) {
        return 0;
    }
    SubS_UpdateFlags(&this->unk18C, 0U, 7U);
    this->unk190 = func_80A50DF8(this, play);
    this->actionFunc = func_80A50F38;
    return 1;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50EC0.s")
s32 func_80A50EC0(EnDnh* this) {
    s16 var_v1;

    if (this->unk19C == 0) {
        var_v1 = 0;
    } else {
        this->unk19C = this->unk19C - 1;
        var_v1 = this->unk19C;
    }
    if (var_v1 == 0) {
        this->unk19E += 1;
        if (this->unk19E >= 4) {
            this->unk19C = Rand_S16Offset(0x1E, 0x1E);
            this->unk19E = 0;
        }
    }
    return;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50F38.s")
void func_80A50F38(EnDnh* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, (void*)this->unk190, this->unk1A0, &this->unk194) != 0) {
        SubS_UpdateFlags(&this->unk18C, 3U, 7U);
        this->unk194 = 0;
        this->unk198 = 0;
        this->actionFunc = func_80A50F9C;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A50F9C.s")
void func_80A50F9C(EnDnh* this, PlayState* play) {
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Init.s")
extern AnimationInfoS D_80A5142C;

void EnDnh_Init(Actor* thisx, PlayState* play) {
    EnDnh* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_Init(play, &this->unk148, (SkeletonHeader*)&D_06002950, NULL, &this->unk1A4, &this->unk1B0, 2);
    SubS_ChangeAnimationByInfoS(&this->unk148, &D_80A5142C, 0);
    this->actor.shape.yOffset = 1100.0f;
    if (gSaveContext.save.entrance != 0xA810) {
        SubS_UpdateFlags(&this->unk18C, 3U, 7U);
        this->unk198 = 0;
    } else {
        SubS_UpdateFlags(&this->unk18C, 4U, 7U);
        this->unk198 = gSaveContext.eventInf[3] & 0x20 ? 2 : 1;
    }
    if (!(gSaveContext.save.saveInfo.weekEventReg[0xC] & 8)) {
        this->actor.draw = NULL;
    }
    this->unk1A0 = &func_80A50D40;
    this->unk194 = 0;
    this->actionFunc = func_80A50F9C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Destroy.s")
void EnDnh_Destroy(Actor* thisx, PlayState* play) {
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Update.s")
void EnDnh_Update(Actor* thisx, PlayState* play) {
    EnDnh* this = THIS;

    func_80A50E40(this, play);
    this->actionFunc(this, play);
    func_80A50EC0(this);
    SkelAnime_Update(&this->unk148);
    func_8013C964(&this->actor, play, 60.0f, 30.0f, 0, this->unk18C & 7);
    Actor_SetFocus(&this->actor, 26.0f);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/func_80A51168.s")
s32 func_80A51168(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 1) {
        Matrix_Translate(0.0f, thisx->shape.yOffset, 0.0f, MTXMODE_APPLY);
    }
    return 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dnh/EnDnh_Draw.s")
s32 func_80A51168(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx); /* extern */
extern s32 D_80A5143C;

void EnDnh_Draw(Actor* thisx, PlayState* play) {
    EnDnh* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(*(&D_80A5143C + this->unk19E)));
    SkelAnime_DrawOpa(play, this->unk148.skeleton, this->unk148.jointTable, func_80A51168, NULL, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
