/*
 * File: z_en_nimotsu.c
 * Overlay: ovl_En_Nimotsu
 * Description: Bomb Shop Bag Stolen by Sakon
 */

#include "z_en_nimotsu.h"
#include "macros.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnNimotsu*)thisx)

void EnNimotsu_Init(Actor* thisx, PlayState* play);
void EnNimotsu_Destroy(Actor* thisx, PlayState* play);
void EnNimotsu_Update(Actor* thisx, PlayState* play);
void EnNimotsu_Draw(Actor* thisx, PlayState* play);

void EnNimotsu_UpdateCollision(EnNimotsu* this, PlayState* play);

const ActorInit En_Nimotsu_InitVars = {
    ACTOR_EN_NIMOTSU,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnNimotsu),
    (ActorFunc)EnNimotsu_Init,
    (ActorFunc)EnNimotsu_Destroy,
    (ActorFunc)EnNimotsu_Update,
    (ActorFunc)EnNimotsu_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER },
    { ELEMTYPE_UNK4,
      { 0x00000000, 0x00, 0x00 },
      { 0x00000000, 0x00, 0x00 },
      TOUCH_NONE | TOUCH_SFX_NORMAL,
      BUMP_NONE,
      OCELEM_ON },
    { 10, 30, 0, { 0, 0, 0 } },
};

extern UNK_TYPE D_06013380;

void EnNimotsu_UpdateCollision(EnNimotsu* this, PlayState* play) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    Actor_UpdateBgCheckInfo(play, &this->actor, 32.0f, 30.0f, 0.0f, 4U);
}

void EnNimotsu_Init(Actor* thisx, PlayState* play) {
    EnNimotsu* this = THIS;

    Collider_InitCylinder(play, &this->collider);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);

    this->framesUntilSomething = 10; // sh (s16 or u16)
    this->actor.gravity = -0.5f;

    Actor_SetScale(&this->actor, 0.01f);
}

void EnNimotsu_Destroy(Actor* thisx, PlayState* play) {
    EnNimotsu* this = THIS;
    Collider_DestroyCylinder(play, &this->collider);
}

void EnNimotsu_Update(Actor* thisx, PlayState* play) {
    EnNimotsu* this = THIS;
    u32 pad;
    Vec3f sp44;

    Actor_MoveWithGravity(&this->actor);

    if (!(this->unk1D8 & 1) && (this->actor.bgCheckFlags & 1)) {

        if (DECR(this->framesUntilSomething) == 0) {
            this->unk1D8 |= 1;
        }

        if ((play->state.frames % 3U) == 0) {
            sp44.x = this->actor.world.pos.x + randPlusMinusPoint5Scaled(15.0f);
            sp44.y = this->actor.world.pos.y;
            sp44.z = this->actor.world.pos.z + randPlusMinusPoint5Scaled(15.0f);
            Actor_SpawnFloorDustRing(play, &this->actor, &sp44, 20.0f, 0, 2.0f, (s16)0, (s16)0, (u8)0);
        }
    }

    EnNimotsu_UpdateCollision(this, play);
}

void EnNimotsu_Draw(Actor* thisx, PlayState* play) {
    EnNimotsu* this = THIS;
    u32 pad;
    Vec3f sp3C;
    Vec3f sp30;

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, &D_06013380);
    func_8012C2DC(play->state.gfxCtx);

    sp3C.x = this->actor.world.pos.x + 7.0f;
    sp3C.y = this->actor.world.pos.y;
    sp3C.z = this->actor.world.pos.z + 2.0f;

    sp30.x = 0.2f;
    sp30.y = 0.2f;
    sp30.z = 0.2f;

    func_800BC620(&sp3C, &sp30, 0xFFU, play);
    CLOSE_DISPS(play->state.gfxCtx);
}
