/*
 * File: z_en_tag_obj.c
 * Overlay: ovl_En_Tag_Obj
 * Description:
 */

#include "z_en_tag_obj.h"

#define FLAGS 0x00000000

#define THIS ((EnTagObj*)thisx)

void EnTagObj_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTagObj_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTagObj_Update(Actor* thisx, GlobalContext* globalCtx);

static ColliderCylinderInit sUnusedColliderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 20, 30, 0, { 0, 0, 0 } },
};

const ActorInit En_Tag_Obj_InitVars = {
    ACTOR_EN_TAG_OBJ,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTagObj),
    (ActorFunc)EnTagObj_Init,
    (ActorFunc)EnTagObj_Destroy,
    (ActorFunc)EnTagObj_Update,
    (ActorFunc)NULL,
};

void EnTagObj_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnTagObj* this = THIS;

    this->hasSpawnedSeahorse = 0;
}

void EnTagObj_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnTagObj_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnTagObj* this = THIS;

    if (!this->hasSpawnedSeahorse) {
        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_OT, this->actor.world.pos.x, this->actor.world.pos.y,
                    this->actor.world.pos.z, 0, 0, 0, 0);
        this->hasSpawnedSeahorse = 1;
    }
}
