/*
 * File: z_en_ms.c
 * Overlay: ovl_En_Ms
 * Description: Bean Seller
 */

#include "z_en_ms.h"

#define FLAGS 0x00000009

#define THIS ((EnMs*)thisx)

void EnMs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80952734(EnMs* this, GlobalContext* globalCtx);
void func_809527F8(EnMs* this, GlobalContext* globalCtx);
void func_809529AC(EnMs* this, GlobalContext* globalCtx);
void func_80952A1C(EnMs *this, GlobalContext *globalCtx);

// #if 0
const ActorInit En_Ms_InitVars = {
    ACTOR_EN_MS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MS,
    sizeof(EnMs),
    (ActorFunc)EnMs_Init,
    (ActorFunc)EnMs_Destroy,
    (ActorFunc)EnMs_Update,
    (ActorFunc)EnMs_Draw,
};

// static ColliderCylinderInitType1 sCylinderInit = {
static ColliderCylinderInitType1 D_80952BA0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 22, 37, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80952BCC[] = {
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

// #endif

extern ColliderCylinderInitType1 D_80952BA0;
extern InitChainEntry D_80952BCC[];

extern AnimationHeader D_060005EC;
extern FlexSkeletonHeader D_06003DC0;

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Init.s")
void EnMs_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMs* this = THIS;

    Actor_ProcessInitChain(thisx, D_80952BCC);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06003DC0, &D_060005EC, this->jointTable, this->morphTable, 9);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinderType1(globalCtx, &this->collider, &this->actor, &D_80952BA0);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 35.0f);
    Actor_SetScale(&this->actor, 0.015f);
    this->actor.colChkInfo.mass = 0xFF;
    this->actionFunc = func_80952734;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = -1.0f;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Destroy.s")
void EnMs_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMs* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_80952734.s")
void func_80952734(EnMs* this, GlobalContext* globalCtx) {
    s16 temp_v1 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if (gSaveContext.inventory.items[10] == ITEM_NONE) {
        this->actor.textId = 0x92E;
    } else {
        this->actor.textId = 0x932;
    }

    if (func_800B84D0(&this->actor, globalCtx) != 0) {
        this->actionFunc = func_809527F8;
        return;
    }

    if (this->actor.xzDistToPlayer < 90.0f) {
        if (ABS_ALT(temp_v1) < 0x2000) {
            func_800B8614(&this->actor, globalCtx, 90.0f);
        }
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_809527F8.s")
void func_809529AC(EnMs* this, GlobalContext* globalCtx); // extern

void func_809527F8(EnMs* this, GlobalContext* globalCtx) {
    switch (func_80152498(&globalCtx->msgCtx)) {
        case 6:
            if (func_80147624(globalCtx) != 0) {
                this->actionFunc = func_80952734;
            }
            break;

        case 5:
            if (func_80147624(globalCtx) != 0) {
                func_801477B4(globalCtx);
                func_800B8A1C(&this->actor, globalCtx, 0x35, this->actor.xzDistToPlayer, this->actor.yDistToPlayer);
                this->actionFunc = func_809529AC;
            }
            break;

        case 4:
            if (func_80147624(globalCtx) != 0) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0:
                        func_801477B4(globalCtx);
                        if (gSaveContext.rupees < 10) {
                            play_sound(0x4806U);
                            func_80151938(globalCtx, 0x935U);
                        } else if (AMMO(ITEM_MAGIC_BEAN) >= 20) {
                            play_sound(0x4806U);
                            func_80151938(globalCtx, 0x937U);
                        } else {
                            func_8019F208();
                            func_800B8A1C(&this->actor, globalCtx, 0x35, 90.0f, 10.0f);
                            func_801159EC(-10);
                            this->actionFunc = func_809529AC;
                        }
                        break;

                    case 1:
                    default:
                        func_8019F230();
                        func_80151938(globalCtx, 0x934U);
                        break;
                }
            }
            break;
        default:
            break;
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_809529AC.s")
void func_809529AC(EnMs *this, GlobalContext *globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.textId = 0;
        func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.yDistToPlayer, 0);
        this->actionFunc = func_80952A1C;
    } else {
        func_800B8A1C(&this->actor, globalCtx, 0x35, this->actor.xzDistToPlayer, this->actor.yDistToPlayer);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_80952A1C.s")
void func_80952A1C(EnMs *this, GlobalContext *globalCtx) {
    if (func_800B84D0(&this->actor, globalCtx)) {
        func_80151938(globalCtx, 0x936U);
        this->actionFunc = func_809527F8;
    } else {
        func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.yDistToPlayer, -1);
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Update.s")
void EnMs_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnMs* this = THIS;

    Actor_SetHeight(&this->actor, 20.0f);
    this->actor.targetArrowOffset = 500.0f;
    Actor_SetScale(&this->actor, 0.015f);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->actionFunc(this, globalCtx);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Draw.s")
void EnMs_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMs* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawSV(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl, this->skelAnime.dListCount, NULL,
                     NULL, &this->actor);
}
