/*
 * File: z_en_invisible_ruppe.c
 * Overlay: ovl_En_Invisible_Ruppe
 * Description: Invisible Rupee
 */

#include "z_en_invisible_ruppe.h"

#define FLAGS 0x00000000

#define THIS ((EnInvisibleRuppe*)thisx)

void EnInvisibleRuppe_Init(Actor* thisx, PlayState* play);
void EnInvisibleRuppe_Destroy(Actor* thisx, PlayState* play);
void EnInvisibleRuppe_Update(Actor* thisx, PlayState* play);

void func_80C258A0(EnInvisibleRuppe* this, PlayState* play);
void func_80C2590C(EnInvisibleRuppe* this, PlayState* play);
void func_80C259E8(EnInvisibleRuppe* this, PlayState* play);

ActorInit En_Invisible_Ruppe_InitVars = {
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

void func_80C258A0(EnInvisibleRuppe* this, PlayState* play) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(play, &this->actor, 32.0f, 30.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
}

void func_80C2590C(EnInvisibleRuppe* this, PlayState* play) {
    if (this->collider.base.ocFlags1 & OC1_HIT) {
        switch (INVISIBLERUPPE_GET_3(&this->actor)) {
            case 0:
                Audio_PlaySfx(NA_SE_SY_GET_RUPY);
                Item_DropCollectible(play, &this->actor.world.pos, 0x8000 | ITEM00_RUPEE_GREEN);
                break;

            case 1:
                Audio_PlaySfx(NA_SE_SY_GET_RUPY);
                Item_DropCollectible(play, &this->actor.world.pos, 0x8000 | ITEM00_RUPEE_BLUE);
                break;

            case 2:
                Audio_PlaySfx(NA_SE_SY_GET_RUPY);
                Item_DropCollectible(play, &this->actor.world.pos, 0x8000 | ITEM00_RUPEE_RED);
                break;

            default:
                break;
        }

        if (this->switchFlag >= 0) {
            Flags_SetSwitch(play, this->switchFlag);
        }

        this->actionFunc = func_80C259E8;
    }
}

void func_80C259E8(EnInvisibleRuppe* this, PlayState* play) {
    Actor_Kill(&this->actor);
}

void EnInvisibleRuppe_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnInvisibleRuppe* this = THIS;

    this->switchFlag = INVISIBLERUPPE_GET_SWITCH_FLAG(&this->actor);

    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }

    if ((this->switchFlag >= 0) && Flags_GetSwitch(play, this->switchFlag)) {
        Actor_Kill(&this->actor);
        return;
    }

    Collider_InitCylinder(play, &this->collider);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);

    this->actionFunc = func_80C2590C;
}

void EnInvisibleRuppe_Destroy(Actor* thisx, PlayState* play) {
    EnInvisibleRuppe* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnInvisibleRuppe_Update(Actor* thisx, PlayState* play) {
    EnInvisibleRuppe* this = THIS;

    this->actionFunc(this, play);
    func_80C258A0(this, play);
}
