/*
 * File: z_en_invisible_ruppe.c
 * Overlay: ovl_En_Invisible_Ruppe
 * Description: Invisible Rupee
 */

#include "z_en_invisible_ruppe.h"

#define FLAGS 0x00000000

#define THIS ((EnInvisibleRuppe*)thisx)

void EnInvisibleRuppe_Init(Actor* thisx, GlobalContext* globalCtx);
void EnInvisibleRuppe_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnInvisibleRuppe_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80C258A0(EnInvisibleRuppe* this, GlobalContext* globalCtx);
void func_80C2590C(EnInvisibleRuppe* this, GlobalContext* globalCtx);
void func_80C259E8(EnInvisibleRuppe* this, GlobalContext* globalCtx);

const ActorInit En_Invisible_Ruppe_InitVars = {
    ACTOR_EN_INVISIBLE_RUPPE,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnInvisibleRuppe),
    (ActorFunc)EnInvisibleRuppe_Init,
    (ActorFunc)EnInvisibleRuppe_Destroy,
    (ActorFunc)EnInvisibleRuppe_Update,
    (ActorFunc)NULL,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_NO_PUSH | OC1_TYPE_PLAYER,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },

    {
        ELEMTYPE_UNK4,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },

    { 10, 30, 0, { 0, 0, 0 } },
};

void func_80C258A0(EnInvisibleRuppe* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 32.0f, 30.0f, 0.0f, 4);
}

void func_80C2590C(EnInvisibleRuppe* this, GlobalContext* globalCtx) {
    if (this->collider.base.ocFlags1 & OC1_HIT) {
        switch (INVISIBLERUPPE_GET_3(this)) {
            case 0:
                play_sound(NA_SE_SY_GET_RUPY);
                Item_DropCollectible(globalCtx, &this->actor.world.pos, 0x8000 | ITEM00_RUPEE_GREEN);
                break;

            case 1:
                play_sound(NA_SE_SY_GET_RUPY);
                Item_DropCollectible(globalCtx, &this->actor.world.pos, 0x8000 | ITEM00_RUPEE_BLUE);
                break;

            case 2:
                play_sound(NA_SE_SY_GET_RUPY);
                Item_DropCollectible(globalCtx, &this->actor.world.pos, 0x8000 | ITEM00_RUPEE_RED);
                break;
        }

        if (this->unk_190 >= 0) {
            Flags_SetSwitch(globalCtx, this->unk_190);
        }

        this->actionFunc = func_80C259E8;
    }
}

void func_80C259E8(EnInvisibleRuppe* this, GlobalContext* globalCtx) {
    Actor_MarkForDeath(&this->actor);
}

void EnInvisibleRuppe_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnInvisibleRuppe* this = THIS;

    this->unk_190 = INVISIBLERUPPE_GET_1FC(this);

    if (this->unk_190 == 0x7F) {
        this->unk_190 = -1;
    }

    if ((this->unk_190 >= 0) && Flags_GetSwitch(globalCtx, this->unk_190)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);

    this->actionFunc = func_80C2590C;
}

void EnInvisibleRuppe_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnInvisibleRuppe* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnInvisibleRuppe_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnInvisibleRuppe* this = THIS;

    this->actionFunc(this, globalCtx);
    func_80C258A0(this, globalCtx);
}
