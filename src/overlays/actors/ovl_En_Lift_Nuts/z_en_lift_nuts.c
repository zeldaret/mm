/*
 * File: z_en_lift_nuts.c
 * Overlay: ovl_En_Lift_Nuts
 * Description: Deku Scrub Playground - Employee
 */

#include "z_en_lift_nuts.h"
#include "objects/object_dnt/object_dnt.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((EnLiftNuts*)thisx)

void EnLiftNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnLiftNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AE9F70(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEA044(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEA128(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEA1A0(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEAC64(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEACF8(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEAF14(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEAFA0(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB148(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB230(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB294(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB428(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB598(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB698(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB8A4(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB934(EnLiftNuts* this, GlobalContext* globalCtx);
void func_80AEB9E0(EnLiftNuts* this, GlobalContext* globalCtx);

const ActorInit En_Lift_Nuts_InitVars = {
    ACTOR_EN_LIFT_NUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNT,
    sizeof(EnLiftNuts),
    (ActorFunc)EnLiftNuts_Init,
    (ActorFunc)EnLiftNuts_Destroy,
    (ActorFunc)EnLiftNuts_Update,
    (ActorFunc)EnLiftNuts_Draw,
};

AnimationInfo D_80AEBD50[] = {
    { &object_dnt_Anim_005488, 1.0f, 0.0f, 0.0f, 0, -4.0f }, { &object_dnt_Anim_00B0B4, 1.0f, 0.0f, 0.0f, 0, -4.0f },
    { &object_dnt_Anim_004AA0, 1.0f, 0.0f, 0.0f, 2, -4.0f }, { &object_dnt_Anim_0029E8, 1.0f, 0.0f, 0.0f, 2, -4.0f },
    { &object_dnt_Anim_005CA8, 1.0f, 0.0f, 0.0f, 2, -1.0f }, { &object_dnt_Anim_0038CC, 1.0f, 0.0f, 0.0f, 0, -4.0f },
    { &object_dnt_Anim_003CC0, 1.0f, 0.0f, 0.0f, 2, -1.0f }, { &object_dnt_Anim_0012F4, 1.0f, 0.0f, 0.0f, 2, -4.0f },
    { &object_dnt_Anim_004700, 0.0f, 0.0f, 0.0f, 2, -4.0f }, { &object_dnt_Anim_001BC8, 1.0f, 0.0f, 0.0f, 0, -4.0f },
    { &object_dnt_Anim_003438, 1.0f, 0.0f, 0.0f, 2, -2.0f }, { &object_dnt_Anim_001E2C, 1.0f, 0.0f, 0.0f, 0, -4.0f },
    { &object_dnt_Anim_000994, 1.0f, 0.0f, 0.0f, 2, -4.0f }, { &object_dnt_Anim_002268, 1.0f, 0.0f, 0.0f, 2, -1.0f },
    { &object_dnt_Anim_002F08, 1.0f, 0.0f, 0.0f, 0, -4.0f }, { &object_dnt_Anim_00577C, 1.0f, 0.0f, 0.0f, 0, -4.0f },
    { &object_dnt_Anim_004E38, 1.0f, 0.0f, 0.0f, 2, -4.0f }, { &object_dnt_Anim_0029E8, 1.0f, 4.0f, 0.0f, 2, -4.0f },
    { &object_dnt_Anim_0029E8, 1.0f, 8.0f, 0.0f, 2, 0.0f },
};

Gfx* D_80AEBF18[] = {
    object_dnt_DL_008290,
    object_dnt_DL_001350,
    object_dnt_DL_001420,
    NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AEBF28 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 25, 75, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80AEBF54 = { 0, 0, 0, 0, MASS_IMMOVABLE };

UNK_PTR D_80AEBF60 = NULL;
UNK_TYPE D_80AEBF64 = 0x00000000;
UNK_TYPE2 D_80AEBF68 = 0x0000;

void func_80AE9A20(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (D_80AEBF64 == 0) {
        func_800B6584(globalCtx, ACTOR_EN_GAMELUPY, &D_80AEBF60, 2);
        D_80AEBF64 = 1;
    }
    this->ptr_1EC = (s16*)&D_80AEBF60;
}

void func_80AE9A80(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (D_80AEBF68 == 0) {
        func_800B6608(globalCtx, ACTOR_EN_GAMELUPY);
        D_80AEBF68 = 1;
    }
}

s32 D_80AEBF6C = 0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9AC4.s")

/*
s32 func_80AE9AC4(EnLiftNuts* this, s32 arg1) {
    switch (arg1) {
        case 0:
            if (D_80AEBF6C) {
                return 1;
            }
        case 1:
            if (D_80AEBF6C == 0) {
                this->unk_34E = 1;
                D_80AEBF6C = 1;
                return 1;
            }
        case 2:
            if (D_80AEBF6C == 1) {
                this->unk_34E = 0;
                D_80AEBF6C = 0;
                return 1;
            }
        default:
            return 0;
    }
}
*/

UNK_TYPE D_80AEBF70 = 0x00000000;

Color_RGBA8 D_80AEBF74 = { 170, 130, 90, 255 };
Color_RGBA8 D_80AEBF78 = { 100, 60, 20, 255 };

Vec3f D_80AEBF7C = { 0.0f, 0.0f, 0.0f };

UNK_TYPE func_80AE9B4C(s32 arg0, s32 arg1) {
    if (arg0 == 0) {
        if (D_80AEBF70 == (arg1 ^ 0)) {
            return 1;
        }
    } else if (arg0 == 1) {
        D_80AEBF70 = arg1;
        return 1;
    }
    return 0;
}

s32 func_80AE9B8C() {
    s32 ret = 0;

    if (gSaveContext.weekEventReg[14] & 0x10) {
        ret = 1;
    }

    if (gSaveContext.weekEventReg[14] & 0x20) {
        ret++;
    }

    if (gSaveContext.weekEventReg[14] & 0x40) {
        ret++;
    }

    return ret;
}
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/EnLiftNuts_Init.s")

void EnLiftNuts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnLiftNuts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
    func_80AE9A80(this, globalCtx);
}

void func_80AE9F28(EnLiftNuts* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 18);
    this->actionFunc = func_80AE9F70;
    this->unk_354 = 0;
}

void func_80AE9F70(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (this->unk_354 < 40) {
        this->unk_354++;
    } else if (this->actor.xzDistToPlayer < 100.0f) {
        func_80AEA0B4();
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AE9FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA044.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA0B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA7A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEA910.s")

void func_80AEABF0(EnLiftNuts* this) {
    this->unk_354 = 0;

    if (this->actionFunc != func_80AEB698) {
        if (func_80AE9B4C(0, 0)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        }
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 16);
    }
    this->actionFunc = func_80AEAC64;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAC64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEACF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAEAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAF14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEAFA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB114.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB1C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB3E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB428.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Lift_Nuts/func_80AEB684.s")

void func_80AEB698(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        if ((gSaveContext.weekEventReg[0xE] & 0x10) && (gSaveContext.weekEventReg[0xE] & 0x20) &&
            ((gSaveContext.day % 5) == 3)) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 0xD);
            Message_StartTextbox(globalCtx, 0x27F5, &this->actor);
            this->textId = 0x27F5;
        } else if (func_80AE9B8C() > 0) {
            Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 1);
            Message_StartTextbox(globalCtx, 0x27F0, &this->actor);
            this->textId = 0x27F0;
        } else {
            Message_StartTextbox(globalCtx, 0x27F1, &this->actor);
            this->textId = 0x27F1;
        }
        this->actor.flags &= 0xFFFEFFFF;
        func_80AEABF0(this);
        switch (gSaveContext.day % 5) {
            case 1:
                gSaveContext.weekEventReg[0xE] |= 0x10;
                break;
            case 2:
                gSaveContext.weekEventReg[0xE] |= 0x20;
                break;
            case 3:
                gSaveContext.weekEventReg[0xE] |= 0x40;
                break;
            default:
                break;
        }
    } else {
        func_800B85E0(&this->actor, globalCtx, 200.0f, -1);
    }
}

void func_80AEB828(EnLiftNuts* this) {
    if (!func_80AE9B4C(0, 4)) {
        func_80AE9B4C(1, 4);
        this->unk_356 = 1;
    }
    if (this->actionFunc == func_80AE9F70) {
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 0xF);
    }
    this->unk_354 = 0;
    this->actionFunc = func_80AEB8A4;
}

void func_80AEB8A4(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (this->unk_354 == 22) {
        if (this->unk_356 == 1) {
            Message_StartTextbox(globalCtx, 0x27F6, &this->actor);
            this->textId = 0x27F6;
        }
        Actor_ChangeAnimationByInfo(&this->skelAnime, D_80AEBD50, 17);
        this->actionFunc = func_80AEB934;
    }
    this->unk_354++;
}

void func_80AEB934(EnLiftNuts* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, 5.0f)) {
        func_80AEB9E0(this, globalCtx);
    }
}

void func_80AEB974(EnLiftNuts* this) {
    s16 textId = this->textId;

    switch (textId) {
        default:
            this->unk_1E4 = 0;
            break;
        case 0x27EE:
        case 0x27EF:
            this->unk_1E4 = 1;
            break;
        case 0x27F5:
            this->unk_1E4 = 2;
            break;
        case 0x27F4:
            if (this->unk_354 == 0) {
                this->unk_1E4 = 2;
                break;
            }
            this->unk_1E4 = 1;
    }
}

void func_80AEB9E0(EnLiftNuts* this, GlobalContext* globalCtx) {
    Vec3f worldPos;
    Vec3f velocity;
    Vec3f accel;
    Color_RGBA8 sp68;
    Color_RGBA8 sp64;
    s32 i;

    worldPos = this->actor.world.pos;

    sp68 = D_80AEBF74;
    sp64 = D_80AEBF78;

    accel.y = 0.0f;

    for (i = 0; i < 30; i++) {
        velocity.x = Rand_Centered() * 15.0f;
        velocity.y = Rand_ZeroOne() * 2.0f;
        velocity.z = Rand_Centered() * 15.0f;

        accel.x = -0.2f * velocity.x;
        accel.z = -0.2f * velocity.z;

        func_800B0EB0(globalCtx, &worldPos, &velocity, &accel, &sp68, &sp64, 80, 25, 10);
    }
}

void func_80AEBB30(EnLiftNuts* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnLiftNuts_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnLiftNuts* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, globalCtx);
    func_80AEBB30(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, thisx, 0.0f, 0.0f, 0.0f, 4);
    func_80AE9BCC(this, globalCtx);

    if (func_80AE9B4C(0, 2)) {
        thisx->flags &= -2;
    }
}

s32 func_80AEBC18(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnLiftNuts* this = THIS;

    if (limbIndex == 15 || limbIndex == 16 || limbIndex == 21 || limbIndex == 23 || limbIndex == 24 ||
        limbIndex == 21 || limbIndex == 27) {
        *dList = NULL;
    }

    if (limbIndex == 26) {
        *dList = D_80AEBF18[this->unk_1E4];
    }
    return 0;
}

void func_80AEBC90(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == 25) {
        Matrix_MultiplyVector3fByState(&D_80AEBF7C, &thisx->focus.pos);
    }
}

void EnLiftNuts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnLiftNuts* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80AEBC18, func_80AEBC90, thisx);
}
