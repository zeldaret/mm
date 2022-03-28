/*
 * File: z_en_ms.c
 * Overlay: ovl_En_Ms
 * Description: Bean Seller
 */

#include "z_en_ms.h"
#include "objects/object_ms/object_ms.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnMs*)thisx)

void EnMs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnMs_Wait(EnMs* this, GlobalContext* globalCtx);
void EnMs_Talk(EnMs* this, GlobalContext* globalCtx);
void EnMs_Sell(EnMs* this, GlobalContext* globalCtx);
void EnMs_TalkAfterPurchase(EnMs* this, GlobalContext* globalCtx);

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

static ColliderCylinderInitType1 sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 22, 37, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

void EnMs_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMs* this = THIS;

    Actor_ProcessInitChain(thisx, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_ms_Skel_003DC0, &object_ms_Anim_0005EC, this->jointTable,
                       this->morphTable, 9);
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinderType1(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    Actor_SetScale(&this->actor, 0.015f);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE; // Eating Magic Beans all day will do that to you
    this->actionFunc = EnMs_Wait;
    this->actor.speedXZ = 0.0f;
    this->actor.velocity.y = 0.0f;
    this->actor.gravity = -1.0f;
}

void EnMs_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMs* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnMs_Wait(EnMs* this, GlobalContext* globalCtx) {
    s16 yawDiff = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;

    if (gSaveContext.save.inventory.items[SLOT_MAGIC_BEANS] == ITEM_NONE) {
        this->actor.textId = 0x92E; // "[...] You're the first customer [...]"
    } else {
        this->actor.textId = 0x932; // "[...] So you liked my Magic Beans [...]"
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = EnMs_Talk;
    } else if ((this->actor.xzDistToPlayer < 90.0f) && (ABS_ALT(yawDiff) < 0x2000)) {
        func_800B8614(&this->actor, globalCtx, 90.0f);
    }
}

void EnMs_Talk(EnMs* this, GlobalContext* globalCtx) {
    switch (Message_GetState(&globalCtx->msgCtx)) {
        case 6:
            if (Message_ShouldAdvance(globalCtx) != 0) {
                this->actionFunc = EnMs_Wait;
            }
            break;

        case 5:
            if (Message_ShouldAdvance(globalCtx) != 0) {
                func_801477B4(globalCtx);
                Actor_PickUp(&this->actor, globalCtx, GI_MAGIC_BEANS, this->actor.xzDistToPlayer,
                             this->actor.playerHeightRel);
                this->actionFunc = EnMs_Sell;
            }
            break;

        case 4:
            if (Message_ShouldAdvance(globalCtx) != 0) {
                switch (globalCtx->msgCtx.choiceIndex) {
                    case 0: // yes
                        func_801477B4(globalCtx);
                        if (gSaveContext.save.playerData.rupees < 10) {
                            play_sound(NA_SE_SY_ERROR);
                            func_80151938(globalCtx, 0x935); // "[...] You don't have enough Rupees."
                        } else if (AMMO(ITEM_MAGIC_BEANS) >= 20) {
                            play_sound(NA_SE_SY_ERROR);
                            func_80151938(globalCtx, 0x937); // "[...] You can't carry anymore."
                        } else {
                            func_8019F208();
                            Actor_PickUp(&this->actor, globalCtx, GI_MAGIC_BEANS, 90.0f, 10.0f);
                            func_801159EC(-10);
                            this->actionFunc = EnMs_Sell;
                        }
                        break;

                    case 1: // no
                    default:
                        func_8019F230();
                        func_80151938(globalCtx, 0x934); // "[...] Well, if your mood changes [...]"
                        break;
                }
            }
            break;
        default:
            break;
    }
}

void EnMs_Sell(EnMs* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actor.textId = 0;
        func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.playerHeightRel, 0);
        this->actionFunc = EnMs_TalkAfterPurchase;
    } else {
        Actor_PickUp(&this->actor, globalCtx, GI_MAGIC_BEANS, this->actor.xzDistToPlayer, this->actor.playerHeightRel);
    }
}

void EnMs_TalkAfterPurchase(EnMs* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        func_80151938(globalCtx, 0x936); // "You can plant 'em whenever you want [...]"
        this->actionFunc = EnMs_Talk;
    } else {
        func_800B8500(&this->actor, globalCtx, this->actor.xzDistToPlayer, this->actor.playerHeightRel, -1);
    }
}

void EnMs_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnMs* this = THIS;

    Actor_SetFocus(&this->actor, 20.0f);
    this->actor.targetArrowOffset = 500.0f;
    Actor_SetScale(&this->actor, 0.015f);
    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, globalCtx);
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnMs_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMs* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, NULL, &this->actor);
}
