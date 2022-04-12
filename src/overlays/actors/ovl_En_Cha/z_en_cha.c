/*
 * File: z_en_cha.c
 * Overlay: ovl_En_Cha
 * Description: Laundry Pool Bell
 */

#include "z_en_cha.h"
#include "objects/object_cha/object_cha.h"

#define FLAGS 0x00000000

#define THIS ((EnCha*)thisx)

void EnCha_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCha_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCha_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCha_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnCha_Idle(EnCha* this, GlobalContext* globalCtx);

const ActorInit En_Cha_InitVars = {
    ACTOR_EN_CHA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_CHA,
    sizeof(EnCha),
    (ActorFunc)EnCha_Init,
    (ActorFunc)EnCha_Destroy,
    (ActorFunc)EnCha_Update,
    (ActorFunc)EnCha_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_WOOD,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
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
    { 10, 40, 0, { 0, 0, 0 } },
};

void EnCha_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnCha* this = THIS;
    s32 pad;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Collider_UpdateCylinder(&this->actor, &this->collider);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.home.rot.z = 0;
    this->actionFunc = EnCha_Idle;
    this->actor.home.rot.x = this->actor.home.rot.z;
    gSaveContext.save.weekEventReg[60] &= (u8)~4;
}

void EnCha_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnCha* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnCha_Ring(EnCha* this, GlobalContext* globalCtx) {
    EnCha_Idle(this, globalCtx);
    if (this->actor.cutscene == -1) {
        this->actionFunc = EnCha_Idle;
    } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        this->actionFunc = EnCha_Idle;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnCha_Idle(EnCha* this, GlobalContext* globalCtx) {
    if (gSaveContext.save.weekEventReg[60] & 4) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DOOR_BELL);
        gSaveContext.save.weekEventReg[60] &= (u8)~4;
        this->actor.home.rot.z = 0x7D0;
    }
    if (this->collider.base.acFlags & AC_HIT) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_DOOR_BELL);
        this->actor.home.rot.z = 0x7D0;
        if (!(gSaveContext.save.weekEventReg[51] & 4)) {
            gSaveContext.save.weekEventReg[51] |= 4;
            this->actionFunc = EnCha_Ring;
        }
    }
    this->actor.home.rot.x += this->actor.home.rot.z;
    this->actor.home.rot.z -= (s16)(this->actor.home.rot.x * 0.1f);
    this->actor.home.rot.z *= 0.96f;
}

void EnCha_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnCha* this = THIS;

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    this->actionFunc(this, globalCtx);
    if ((this->actor.shape.rot.z > -0x1F40) && (this->actor.shape.rot.z < 0x1F40)) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void EnCha_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnCha* this = THIS;

    Gfx_DrawDListOpa(globalCtx, object_cha_DL_000710);
    Matrix_InsertTranslation(-1094.0f, 4950.0f, 9.0f, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(this->actor.home.rot.x, MTXMODE_APPLY);
    Gfx_DrawDListOpa(globalCtx, object_cha_DL_000958);
}
