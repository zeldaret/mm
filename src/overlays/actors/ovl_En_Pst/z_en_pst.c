/*
 * File: z_en_pst.c
 * Overlay: ovl_En_Pst
 * Description: Postbox
 */

#include "z_en_pst.h"

#define FLAGS (ACTOR_FLAG_1)

#define THIS ((EnPst*)thisx)

void EnPst_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B2BD98(EnPst* this, GlobalContext* globalCtx);
void func_80B2BE54(EnPst* this, GlobalContext* globalCtx);

s32 D_80B2C200[] = { 0x02091F09, 0x23030400, 0x01040002 };
s32 D_80B2C20C[] = { 0x020A030A, 0x07030400, 0x01040002 };
s32 D_80B2C218[] = { 0x020A230A, 0x27030400, 0x01040002 };
s32 D_80B2C224[] = { 0x020A350A, 0x39030400, 0x01040002 };
s32 D_80B2C230[] = { 0x020B190B, 0x1D030400, 0x01040002 };

s32 D_80B2C23C[] = { 0x0E27840C, 0x0E00FF2B, 0x00000031, 0x00392800, 0x0A122C27, 0xA40C2F00, 0x000C1012,
                     0x2C27870C, 0x2F00000C, 0x111B022A, 0x002F001B, 0x4000080F, 0x27882D00, 0x180C100F,
                     0x27892D00, 0x180C1012, 0x2C27850C, 0x2FFFD20E, 0x27860C10 };

s32 D_80B2C288[] = { 0x0E27840C, 0x0E00FF2B, 0x00000031, 0x00392800, 0x0A122C27, 0xA40C2F00, 0x000C1012,
                     0x2C27870C, 0x2F00000C, 0x111B042A, 0x002F001B, 0x8000080F, 0x27882D00, 0x180C100F,
                     0x27892D00, 0x180C1012, 0x2C27850C, 0x2FFFD20E, 0x27860C10 };

s32 D_80B2C2D4[] = { 0x0E27840C, 0x0E00FF2B, 0x00000031, 0x00392800, 0x0A122C27, 0xA40C2F00, 0x000C1012,
                     0x2C27870C, 0x2F00000C, 0x111B082A, 0x002F001C, 0x0100080F, 0x27882D00, 0x180C100F,
                     0x27892D00, 0x180C1012, 0x2C27850C, 0x2FFFD20E, 0x27860C10 };

s32 D_80B2C320[] = { 0x0E27840C, 0x0E00FF2B, 0x00000031, 0x00392800, 0x0A122C27, 0xA40C2F00, 0x000C1012,
                     0x2C27870C, 0x2F00000C, 0x111B102A, 0x002F001C, 0x0200080F, 0x27882D00, 0x180C100F,
                     0x27892D00, 0x180C1012, 0x2C27850C, 0x2FFFD20E, 0x27860C10 };

s32 D_80B2C36C[] = { 0x0E27840C, 0x0E00FF2B, 0x00000031, 0x00392800, 0x0A122C27, 0xA40C2F00, 0x000C1012,
                     0x2C27870C, 0x2F00000C, 0x111B202A, 0x002F001C, 0x0400080F, 0x27882D00, 0x180C100F,
                     0x27892D00, 0x180C1012, 0x2C27850C, 0x2FFFD20E, 0x27860C10 };

s32 D_80B2C3B8[] = { 0x0E27A10C, 0x0F27A20C, 0x12005108, 0x000F0600, 0x0C000013, 0x000C0C11,
                     0x51080700, 0x0C060001, 0x00001300, 0x010C0700, 0x000E27A3, 0x0C161000 };

s32 D_80B2C3E8[] = { 0x2C27870C, 0x111B022A, 0x002F001B, 0x4000080F, 0x27882D00, 0x180C100F, 0x27892D00, 0x180C1000 };

s32 D_80B2C408[] = { 0x2C27870C, 0x111B042A, 0x002F001B, 0x8000080F, 0x27882D00, 0x180C100F, 0x27892D00, 0x180C1000 };

s32 D_80B2C428[] = { 0x2C27870C, 0x111B082A, 0x002F001C, 0x0100080F, 0x27882D00, 0x180C100F, 0x27892D00, 0x180C1000 };

s32 D_80B2C448[] = { 0x2C27870C, 0x111B102A, 0x002F001C, 0x0200080F, 0x27882D00, 0x180C100F, 0x27892D00, 0x180C1000 };

s32 D_80B2C468[] = { 0x2C27870C, 0x111B202A, 0x002F001C, 0x0400080F, 0x27882D00, 0x180C100F, 0x27892D00, 0x180C1000 };

s32 D_80B2C488[] = { 0x2C27A40C, 0x10000000 };

s32 D_80B2C490[] = { 0x2C27850C, 0x10000000 };

const ActorInit En_Pst_InitVars = {
    ACTOR_EN_PST,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_PST,
    sizeof(EnPst),
    (ActorFunc)EnPst_Init,
    (ActorFunc)EnPst_Destroy,
    (ActorFunc)EnPst_Update,
    (ActorFunc)EnPst_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B2C4B8 = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 28, 72, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B2C4E4 = { 1, 0, 0, 0, MASS_IMMOVABLE };

s32 D_80B2C4F0[] = { 0x06000018, 0x3F800000, 0x0000FFFF, 0x02000000 };

s32 D_80B2C500[] = { D_80B2C200, D_80B2C20C, D_80B2C218, D_80B2C224, D_80B2C230, 0x00000000, 0x00000000, 0x00000000 };

extern UNK_TYPE D_06001A80;

void func_80B2B830(EnPst* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 func_80B2B874(EnPst* this) {
    switch (this->actor.params) {
        case 0:
            return gSaveContext.save.weekEventReg[0x1B] & 2;
        case 1:
            return gSaveContext.save.weekEventReg[0x1B] & 4;
        case 2:
            return gSaveContext.save.weekEventReg[0x1B] & 8;
        case 3:
            return gSaveContext.save.weekEventReg[0x1B] & 0x10;
        case 4:
            return gSaveContext.save.weekEventReg[0x1B] & 0x20;
        default:
            return 0;
    }
}

s32 func_80B2B8F4(EnPst* this) {
    switch (this->actor.params) {
        case 0:
            return gSaveContext.save.weekEventReg[0x1B] & 0x40;
        case 1:
            return gSaveContext.save.weekEventReg[0x1B] & 0x80;
        case 2:
            return gSaveContext.save.weekEventReg[0x1C] & 1;
        case 3:
            return gSaveContext.save.weekEventReg[0x1C] & 2;
        case 4:
            return gSaveContext.save.weekEventReg[0x1C] & 4;
        default:
            return 0;
    }
}

s32 func_80B2B974(EnPst* this, GlobalContext* globalCtx) {
    s32 sp18 = 0;
    s32 phi_a3 = 0;

    switch (this->unk20E) {
        case 0:
            switch (Message_GetState(&globalCtx->msgCtx)) {
                case 4:
                case 5:
                    if (Message_ShouldAdvance(globalCtx) != 0) {
                        case 16:
                            sp18 = func_80123810(globalCtx);
                            phi_a3 = 0;
                            if ((sp18 == 0x2D) || (sp18 == 0x33)) {
                                this->unk218 = sp18;
                                this->unk20E++;
                                phi_a3 = 1;
                            } else if (sp18 < 0) {
                                this->unk20E++;
                                phi_a3 = 3;
                            } else if (sp18 != 0) {
                                this->unk20E++;
                                phi_a3 = 2;
                            }
                    }
                    break;
            }
            break;
        case 1:
            if (this->unk218 == 0x2D) {
                phi_a3 = 1;
            }
            break;
    }
    return phi_a3;
}

s32* func_80B2BAA4(EnPst* this, GlobalContext* globalCtx) {
    if (Player_GetMask(globalCtx) == 9) {
        return D_80B2C3B8;
    }

    if (this->unk208 & 0x10) {
        switch (this->actor.params) {
            case 0:
                return D_80B2C3E8;
            case 1:
                return D_80B2C408;
            case 2:
                return D_80B2C428;
            case 3:
                return D_80B2C448;
            case 4:
                return D_80B2C468;
            default:
                return NULL;
        }

    } else if (this->unk208 & 0x20) {
        if (this->unk218 == 0x33) {
            return D_80B2C488;
        }
        return D_80B2C490;
    } else {

        this->unk210 = func_80B2B974;
        switch (this->actor.params) {
            case 0:
                return D_80B2C23C;
            case 1:
                return D_80B2C288;
            case 2:
                return D_80B2C2D4;
            case 3:
                return D_80B2C320;
            case 4:
                return D_80B2C36C;
            default:
                return NULL;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BBFC.s")

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BCF8.s")
s32 func_80B2BCF8(EnPst* this, GlobalContext* globalCtx, s16 unkArg) {
    SubS_UpdateFlags(&this->unk208, 3, 7);
    return 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BD30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BD88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BD98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BE54.s")
// void func_80B2BE54(EnPst* this, GlobalContext* globalCtx) {

//     if (func_8010BF58(&this->actor, globalCtx, this->unk1DC, this->unk210, &this->unk1E0) != 0) {
//         if (func_80B2B874(this) != this->unk21C) {
//             if (gSaveContext.save.day != 1) {
//                 if (gSaveContext.save.day != 2) {
//                     gSaveContext.save.weekEventReg[0x5B] |= 8;
//                 } else if (func_80B2B8F4(this) != 0) {
//                     gSaveContext.save.weekEventReg[0x5B] |= 8;
//                 } else {
//                     gSaveContext.save.weekEventReg[0x5B] |= 4;
//                 }
//             } else {
//                 gSaveContext.save.weekEventReg[0x5B] |= 4;
//             }
//         }
//         SubS_UpdateFlags(&this->unk208, 3U, 7U);
//         this->unk1E0 = 0;
//         this->actionFunc = func_80B2BD98;
//     }
// }

void EnPst_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnPst* this = THIS;
    s32 pad;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 18.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06001A80, NULL, &this->jointTable, &this->morphTable, 3);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &D_80B2C4B8);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &D_80B2C4E4);
    SubS_UpdateFlags(&this->unk208, 3, 7);
    SubS_ChangeAnimationByInfoS(&this->skelAnime, &D_80B2C4F0, 0);
    this->actor.targetMode = 0;
    Actor_SetScale(&this->actor, 0.02f);
    this->actionFunc = func_80B2BD98;
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
}

void EnPst_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPst* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnPst_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnPst* this = THIS;

    func_80B2BBFC(this, globalCtx);
    this->actionFunc(this, globalCtx);
    if (this->unk1D8 != 0) {
        if (Actor_IsFacingPlayer(&this->actor, 0x1FFE)) {
            this->unk214 = 0;
            func_8013C964(&this->actor, globalCtx, 60.0f, 20.0f, 0, this->unk208 & 7);
        }
        Actor_SetFocus(&this->actor, 20.0f);
        func_80B2B830(this, globalCtx);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2C11C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/EnPst_Draw.s")
