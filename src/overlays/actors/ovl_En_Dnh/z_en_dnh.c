/*
 * File: z_en_dnh.c
 * Overlay: ovl_En_Dnh
 * Description: Koume in boat house
 */

#include "z_en_dnh.h"
#include "objects/object_tro/object_tro.h"
#include "objects/object_mm/object_mm.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnDnh*)thisx)

void EnDnh_Init(Actor* thisx, PlayState* play);
void EnDnh_Destroy(Actor* thisx, PlayState* play);
void EnDnh_Update(Actor* thisx, PlayState* play);
void EnDnh_Draw(Actor* thisx, PlayState* play);

void func_80A50F38(EnDnh* this, PlayState* play);
void func_80A50F9C(EnDnh* this, PlayState* play);

UNK_TYPE D_80A51250[] = { 0x000C0800, 0x080E0862, 0x0C111101, 0x10040005, 0x0E08670C, 0x10001402, 0x007A0019,
                          0x1000300E, 0x08590C25, 0x000D0018, 0x0F08630C, 0x12060043, 0x00001300, 0x430C0700,
                          0x000E088D, 0x0C190007, 0x0F088D0C, 0x19000012, 0x11191009, 0x00001000, 0x1A100016,
                          0x0E085A11, 0x1A100C0F, 0x085B0C0F, 0x085C0C05, 0x00060024, 0x00060E08, 0x5B19FFEE,
                          0x300F085E, 0x0C08000A, 0x00050F08, 0x750C1014, 0xFFF60F08, 0x600C1211, 0x19100900,
                          0x0010310F, 0x085F0C10, 0x00192000, 0x49001A10, 0x003D0E08, 0x68111A10, 0x0C0F0869,
                          0x0C0F086A, 0x0C0F086B, 0x0C0F086C, 0x0C050000, 0x00190000, 0x300E086E, 0x1119201C,
                          0x03201D03, 0x401D0380, 0x1D04010C, 0x12090000, 0x10310E08, 0x6D0C100E, 0x08700C19,
                          0xFFCB0019, 0x2000070E, 0x08710C19, 0xFFBB0E08, 0x720C0F08, 0x730C0500, 0x00001700,
                          0x0008000A, 0x0006320F, 0x08750C10, 0x3014FFF6, 0x001A4000, 0x0919FFA8, 0x310E0874,
                          0x0C100E08, 0x76111920, 0x1C03201D, 0x03401D03, 0x801D0401, 0x0C120900, 0x00100000 };

UNK_TYPE D_80A51384[] = { 0x0E08610C, 0x16100000 };

UNK_TYPE D_80A5138C[] = { 0x1B034000, 0x67001A40, 0x003A1B03, 0x80001A0E, 0x087C0C00, 0x5B20000A, 0x0F087E0C,
                          0x115B2019, 0x004E0F08, 0x7B0C1900, 0x470E087D, 0x0C120600, 0x0C000013, 0x000C0C07,
                          0x00000E08, 0x7E0C111A, 0x4019002C, 0x1B038000, 0x0B0E087A, 0x0C0F087B, 0x0C19001C,
                          0x0E08780C, 0x12060005, 0x00001300, 0x050C0700, 0x000E0879, 0x0C190004, 0x0E08770C,
                          0x1D03201D, 0x03401D03, 0x801D0401, 0x16100000 };

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

static AnimationInfoS sAnimationInfo[] = { &object_tro_Anim_0000A0, 1.0f, 0, -1, ANIMMODE_LOOP, 0 };

UNK_TYPE D_80A5143C[] = { 0x06001140, 0x06001940, 0x06002140, 0x06001940, 0x00000000 };

void* func_80A50D40(Actor* actor, PlayState* play) {
    func_800B7298(play, actor, 7U);
    if (gSaveContext.eventInf[3] & 0x20) {
        play->nextEntrance = 0xC60;
    } else {
        play->nextEntrance = 0x8460;
    }
    gSaveContext.nextCutsceneIndex = 0;
    play->transitionTrigger = 0x14;
    play->transitionType = 3;
    gSaveContext.nextTransitionType = 7;
    gSaveContext.save.saveInfo.weekEventReg[0x5A] &= 0xBF;
    gSaveContext.eventInf[5] &= 0xFE;
    return 1;
}

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

s32 func_80A50E40(EnDnh* this, PlayState* play) {
    if (!(this->unk18C & 7) || (Actor_ProcessTalkRequest(&this->actor, &play->state) == 0)) {
        return 0;
    }
    SubS_UpdateFlags(&this->unk18C, 0U, 7U);
    this->unk190 = func_80A50DF8(this, play);
    this->actionFunc = func_80A50F38;
    return 1;
}

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
}

void func_80A50F38(EnDnh* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, this->unk190, this->unk1A0, &this->unk194) != 0) {
        SubS_UpdateFlags(&this->unk18C, 3U, 7U);
        this->unk194 = 0;
        this->unk198 = 0;
        this->actionFunc = func_80A50F9C;
    }
}

void func_80A50F9C(EnDnh* this, PlayState* play) {
}

void EnDnh_Init(Actor* thisx, PlayState* play) {
    EnDnh* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_Init(play, &this->skelAnime, (SkeletonHeader*)object_mm_Tex_002950, NULL, &this->unk1A4, &this->unk1B0,
                   2);
    SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 0);
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
    this->unk1A0 = func_80A50D40;
    this->unk194 = 0;
    this->actionFunc = func_80A50F9C;
}

void EnDnh_Destroy(Actor* thisx, PlayState* play) {
}

void EnDnh_Update(Actor* thisx, PlayState* play) {
    EnDnh* this = THIS;

    func_80A50E40(this, play);
    this->actionFunc(this, play);
    func_80A50EC0(this);
    SkelAnime_Update(&this->skelAnime);
    func_8013C964(&this->actor, play, 60.0f, 30.0f, 0, this->unk18C & 7);
    Actor_SetFocus(&this->actor, 26.0f);
}

s32 func_80A51168(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 1) {
        Matrix_Translate(0.0f, thisx->shape.yOffset, 0.0f, MTXMODE_APPLY);
    }
    return 0;
}

void EnDnh_Draw(Actor* thisx, PlayState* play) {
    EnDnh* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A5143C[this->unk19E]));
    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, func_80A51168, NULL, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
