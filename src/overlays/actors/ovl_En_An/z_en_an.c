/*
 * File: z_en_an.c
 * Overlay: ovl_En_An
 * Description: Anju
 */

#include "z_en_an.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnAn*)thisx)

void EnAn_Init(Actor* thisx, PlayState* play);
void EnAn_Destroy(Actor* thisx, PlayState* play);
void EnAn_Update(Actor* thisx, PlayState* play);

void EnAn_Draw(Actor* this, PlayState* play);

// Action funcs
void func_80B577F0(EnAn* this, PlayState* play);
void func_80B578F8(EnAn* this, PlayState* play);
void func_80B57A44(EnAn* this, PlayState* play);



s32 func_80B53840(EnAn* this, PlayState* play);
s32 func_80B53BA8(EnAn* this, PlayState* play);
void func_80B53ED4(EnAn* this, PlayState* play);
void func_80B53F84(EnAn* this);
s32 func_80B55180(EnAn* this, PlayState* play);
s32 func_80B552E4(EnAn* this, PlayState* play);
void func_80B554E8(EnAn* this);
UNK_RET func_80B55914(EnAn* this, PlayState* play);
void func_80B57B48(EnAn* this, PlayState* play);


extern AnimationInfoS D_80B58BF4[];

#if 0
ActorInit En_An_InitVars = {
    ACTOR_EN_AN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AN1,
    sizeof(EnAn),
    (ActorFunc)EnAn_Init,
    (ActorFunc)EnAn_Destroy,
    (ActorFunc)EnAn_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B58BBC = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 14, 62, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B58BE8 = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_80B58BBC;
extern CollisionCheckInfoInit2 D_80B58BE8;

extern UNK_TYPE D_060111E8;
extern FlexSkeletonHeader D_06012618;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B53840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B539CC.s")

Actor* func_80B53A7C(EnAn* this, PlayState* play, u8 actorCategory, s16 actorId) {
    Actor* foundActor = NULL;

    while (true) {
        foundActor = SubS_FindActor(play, foundActor, actorCategory, actorId);

        if (foundActor == NULL) {
            break;
        }

        if ((this != (EnAn*)foundActor)) {
            if ((foundActor->update != NULL) && !(foundActor->params & 0x8000)) {
                break;
            }
        }

        if (foundActor->next == NULL) {
            foundActor = NULL;
            break;
        }

        foundActor = foundActor->next;
    }

    return foundActor;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B53B3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B53BA8.s")

s32 func_80B53CE8(EnAn* this, PlayState* play, s32 arg2) {
    s8 temp_t1 = this->actor.objBankIndex;
    s8 var_v1 = -1;
    s32 var_t0 = 0;
    s32 var_t2 = 0;

    if ((arg2 >= 0x19) && (this->unk_20B >= 0)) {
        var_v1 = this->unk_20B;
    } else if ((arg2 >= 0x15) && (this->unk_209 >= 0)) {
        var_v1 = this->unk_209;
    } else if ((arg2 >= 0x11) && (this->unk_208 >= 0)) {
        var_v1 = this->unk_208;
    } else if (arg2 < 0x11) {
        var_v1 = temp_t1;
    }

    if (var_v1 < 0) {
        return 0;
    }

    switch (arg2) {
        case 0x1:
        case 0x2:
            if ((this->unk_39C != 1) && (this->unk_39C != 2)) {
                var_t0 = 1;
            }
            break;

        case 0x7:
        case 0x8:
            if ((this->unk_39C != 7) && (this->unk_39C != 8)) {
                var_t0 = 1;
            }
            break;

        case 0x9:
        case 0xA:
            if ((this->unk_39C != 9) && (this->unk_39C != 0xA)) {
                var_t0 = 1;
            }
            break;

        default:
            if (arg2 != this->unk_39C) {
                var_t0 = 1;
            }
            break;
    }

    if ((var_t0 != 0) && (var_v1 >= 0)) {
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.status[var_v1].segment);
        this->unk_39C = arg2;
        var_t2 = SubS_ChangeAnimationByInfoS(&this->unk_144, D_80B58BF4, arg2);
        this->unk_368 = this->unk_144.playSpeed;
        gSegments[0x6] = OS_K0_TO_PHYSICAL(play->objectCtx.status[temp_t1].segment);
    }

    return var_t2;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B53ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B53F84.s")

void func_80B54124(EnAn* this, PlayState* play, u32 arg2);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B54124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B54678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B546F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B54750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B547C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B5492C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B54A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B54BC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B54C5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B54D18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B54DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B55180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B552E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B553AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B554E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B555C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B556F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B557AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B55860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B55914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B55D20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B55D98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B55ECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B55F8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B5600C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B5611C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B561A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56744.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56B00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56BC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56CAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56D28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56E44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B56EB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B5702C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B572D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B573F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B575BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B57674.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B57718.s")

void func_80B577F0(EnAn* this, PlayState* play) {
    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 14.0f);
    SkelAnime_InitFlex(play, &this->unk_144, &D_06012618, NULL, this->unk_264, this->unk_2E2, 0x15);

    this->unk_39C = -1;
    func_80B53CE8(this, play, 1);
    Collider_InitAndSetCylinder(play, &this->unk_190, &this->actor, &D_80B58BBC);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80B58BE8);

    if (this->actor.params & 0x8000) {
        this->unk_3C0 = 1;
    }

    this->actor.draw = EnAn_Draw;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_360 = 0;
    this->unk_200 = 0;

    this->actionFunc = func_80B578F8;
    this->actionFunc(this, play);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B578F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B57A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_An/func_80B57B48.s")

void EnAn_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnAn* this = THIS;
    s32 temp_v1; // sp1C
    s32 temp_v0;

    if (play->sceneId != SCENE_YADOYA) {
        this->actor.params &= (s16)~0x8000;
    }

    temp_v1 = ENAN_GET_8000(&this->actor);
    temp_v0 = gSaveContext.save.saveInfo.weekEventReg[0x33] & 0x40;

    if (((temp_v0 == 0) && (temp_v1 == 1)) || ((temp_v0 != 0) && (temp_v1 == 0))) {
        Actor_Kill(&this->actor);
        return;
    }

    if (temp_v1 == 0) {
        if (func_80B53A7C(this, play, ACTORCAT_NPC, ACTOR_EN_AN) != NULL) {
            Actor_Kill(&this->actor);
            return;
        }
    }

    this->unk_214 = -0x80;
    this->unk_3B8 = 0;
    if (temp_v1 == 0) {
        this->actor.room = -1;
    }

    this->actionFunc = func_80B577F0;
}

void EnAn_Destroy(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    Collider_DestroyCylinder(play, &this->unk_190);
}

void EnAn_Update(Actor* thisx, PlayState* play) {
    EnAn* this = (EnAn* ) thisx;

    if (func_80B53840(this, play) != 0) {
        return;
    }

    if ((this->actionFunc != func_80B577F0) && (func_80B55180(this, play) == 0) && (func_80B552E4(this, play) != 0)) {
        func_80B57B48(this, play);
        func_80B53BA8(this, play);
        func_80B53F84(this);
        return;
    }

    this->actionFunc(this, play);
    if (this->unk_200 != 0) {
        func_80B55914(this, play);
        func_80B53BA8(this, play);
        func_80B53F84(this);
        func_80B554E8(this);
        SubS_Offer(&this->actor, play, this->unk_374, 30.0f, 0, this->unk_360 & 7);

        if (!(this->unk_360 & 0x40)) {
            Actor_MoveWithGravity(&this->actor);
            Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4U);
        }

        func_80B53ED4(this, play);
    }
}

extern Vec3f D_80B58ED4;

void func_80B57EE8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnAn* this = THIS;

    if (limbIndex == 9) {
        Matrix_MultVec3f(&D_80B58ED4, &this->actor.focus.pos);
        Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
        func_80B54124(this, play, 1U);
    } else if (limbIndex == 8) {
        func_80B54124(this, play, 0U);
        func_80B54124(this, play, 4U);
        func_80B54124(this, play, 2U);
        func_80B54124(this, play, 3U);
    } else if (limbIndex == 5) {
        func_80B54124(this, play, 5U);
    }
}

void func_80B57FC4(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnAn* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->unk_360 & 0x200)) {
        if (this->unk_360 & 0x80) {
            overrideRot = true;
        } else {
            overrideRot = false;
        }
        stepRot = true;
    } else {
        overrideRot = false;
        stepRot = false;
    }

    if (limbIndex == 9) {
        SubS_UpdateLimb((s16) (this->unk_37C + 0x4000), (s16) (this->unk_37E + this->actor.shape.rot.y + 0x4000), &this->unk_240, &this->unk_258, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_240.x, this->unk_240.y, this->unk_240.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_258.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_258.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_258.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

extern UNK_PTR D_80B58EEC[];
extern UNK_PTR D_80B58EE0[];

void EnAn_Draw(Actor* thisx, PlayState* play) {
    EnAn* this = THIS;

    if ((this->unk_200 != 0) || (this->unk_3B0 != 0)) {
        OPEN_DISPS(play->state.gfxCtx);

        Gfx_SetupDL25_Opa(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80B58EEC[this->unk_390]));
        gSPSegment(POLY_OPA_DISP++, 0x09, Lib_SegmentedToVirtual(D_80B58EE0[this->unk_392]));

        SkelAnime_DrawTransformFlexOpa(play, this->unk_144.skeleton, this->unk_144.jointTable, this->unk_144.dListCount, NULL, func_80B57EE8, func_80B57FC4, &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
