/*
 * File: z_bg_fire_wall.c
 * Overlay: ovl_Bg_Fire_Wall
 * Description: Wall of fire spawned by ovl_Bg_Spout_Fire
 */

#include "z_bg_fire_wall.h"

#define FLAGS 0x00000000

#define THIS ((BgFireWall*)thisx)

void BgFireWall_Init(Actor* thisx, PlayState* play);
void BgFireWall_Destroy(Actor* thisx, PlayState* play);
void BgFireWall_Update(Actor* thisx, PlayState* play);

void func_809AC638(BgFireWall* this, PlayState* play);
void func_809AC68C(BgFireWall* this, PlayState* play);
void func_809AC6C0(BgFireWall* this, PlayState* play);
void func_809AC970(BgFireWall* this, PlayState* play);
s32 func_809AC5C0(BgFireWall* this, PlayState* play);
void BgFireWall_Draw(Actor* thisx, PlayState* play);
void func_809AC760(BgFireWall* this, PlayState* play);
void func_809AC7F8(BgFireWall* this, PlayState* play);
#if 0
const ActorInit Bg_Fire_Wall_InitVars = {
    ACTOR_BG_FIRE_WALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FWALL,
    sizeof(BgFireWall),
    (ActorFunc)BgFireWall_Init,
    (ActorFunc)BgFireWall_Destroy,
    (ActorFunc)BgFireWall_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809ACC60 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x20000000, 0x01, 0x04 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_NONE, OCELEM_ON, },
    { 34, 85, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_809ACC8C = { 1, 80, 100, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_809ACC60;
extern CollisionCheckInfoInit D_809ACC8C;
extern TexturePtr D_809ACC94[];
extern UNK_TYPE D_06000040;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/BgFireWall_Init.s")

void BgFireWall_Init(Actor* thisx, PlayState* play) {
    BgFireWall* this = (BgFireWall*)thisx;

    this->unk14C = this->actor.params;
    this->actor.scale.y = 0.005f;
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &D_809ACC60);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &D_809ACC8C);
    this->actor.scale.z = 0.12f;
    this->actor.scale.x = 0.12f;
    this->unk15C = 0.09f;
    this->unk158 = 0.1f;
    this->unk160 = 300.0f;
    this->unk148 = Rand_S16Offset(0, 7);
    this->actor.flags |= 0x10;
    this->collider.dim.pos.y = (s16)(s32)this->actor.world.pos.y;
    this->actionFunc = func_809AC638;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/BgFireWall_Destroy.s")

void BgFireWall_Destroy(Actor* thisx, PlayState* play) {
    BgFireWall* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC5C0.s")

s32 func_809AC5C0(BgFireWall* thisx, PlayState* play) {
    BgFireWall* this = THIS;
    Actor* player = play->actorCtx.actorLists[2].first;
    Vec3f sp1C;

    Actor_OffsetOfPointInActorCoords(&this->actor, &sp1C, &player->world.pos);
    if ((fabsf(sp1C.x) < this->unk160) && (fabsf(sp1C.z) < (this->unk160 + 20.0f))) {
        return true;
    } else {
        return false;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC638.s")

void func_809AC638(BgFireWall* this, PlayState* play) {
    if ((this->unk14C != 0) || (func_809AC5C0(this, play) != 0)) {
        this->actor.draw = BgFireWall_Draw;
        this->unk14A = 5;
        this->actionFunc = func_809AC68C;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC68C.s")

void func_809AC68C(BgFireWall* this, PlayState* play) {

    if (this->unk14A != 0) {
        this->unk14A--;
    }
    if (this->unk14A == 0) {
        this->actionFunc = func_809AC6C0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC6C0.s")
/*
void func_809AC6C0(BgFireWall *this, PlayState *play) {
    if ((this->unk14C != 0) || (func_809AC5C0(this, play) != 0)) {
        this->unk15C = 0.09f;
        Math_StepToF(this + 0x5C, 0.09f + this->unk154, this->unk158);
    }
    else if (Math_StepToF(&this->actor.scale.y, 0.005f, this->unk158) != 0) {
        this->actionFunc = func_809AC638;
    } else {

    this->unk14A = 0;
    }
}
*/
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC760.s")

void func_809AC760(BgFireWall* this, PlayState* play) {
    s16 phi_a3;

    if (Actor_IsFacingPlayer(&this->actor, 0x4000) != 0) {
        phi_a3 = this->actor.shape.rot.y;
    } else {
        phi_a3 = (s16)(this->actor.shape.rot.y + 0x8000);
    }
    func_800B8D98(play, &this->actor, (f32)gGameInfo->data[0x990] + 10.0f, phi_a3, (f32)gGameInfo->data[0x991] + 5.0f);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC7F8.s")
/*
void func_809AC7F8(BgFireWall *this, PlayState *play) {
    Vec3f sp38;
    f32 sp30;
    //f32 temp_fv0;
    f32 temp_fv0_2;
    f32 phi_fv0;

    Actor_OffsetOfPointInActorCoords(&this->actor, &sp38, &play->actorCtx.actorLists[2].first->world.pos);

    phi_fv0 = CLAMP(sp38.y, -80.0f, 80.0f);

    if ((f32) sp38.x < -80.0f) {
        phi_fv0 = -80.0f;
    } else if ((f32) sp38.x > 80.0f) {
        phi_fv0 = 80.0f;
    } else {
        phi_fv0 = (f32) sp38.x;
    }

    sp38.y = phi_fv0;
    //temp_fv0 = this->unk150;
    if (this->unk150 == 0.0f) {
        if (sp38.z > 0.0f) {
            sp38.z = -25.0f;
            this->unk150 = -1.0f;
        } else {
            sp38.z = 25.0f;
            this->unk150 = 1.0f;
        }
    } else {
        sp38.z = this->unk150 * 25.0f;
    }
    sp30 = Math_SinS(this->actor.shape.rot.y);
    temp_fv0_2 = Math_CosS(this->actor.shape.rot.y);
    this->collider.dim.pos.x = (s16) (s32) (this->actor.world.pos.x + ((f32) sp38.y * temp_fv0_2) + (sp38.z * sp30));
    this->collider.dim.pos.z = (s16) (s32) ((this->actor.world.pos.z - ((f32) sp38.y * sp30)) + (sp38.z * temp_fv0_2));
}
*/
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC970.s")

void func_809AC970(BgFireWall* this, PlayState* play) {
    if (Math_StepToF(&this->actor.scale.y, 0.005f, this->unk158)) {
        Actor_MarkForDeath(&this->actor);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/BgFireWall_Update.s")
/*
void BgFireWall_Update(Actor* thisx, PlayState* play) {
    BgFireWall* this = (BgFireWall*)thisx;

    this->actionFunc(this, play);
    if ((this->unk14C == 0) || ((this->unk14C != 0) && (this->actor.xzDistToPlayer < 240.0f))) {
        if (((this->collider.base.atFlags) & 2) != 0) {
            this->collider.base.atFlags = (this->collider.base.atFlags) & 0xFFFD;
            func_809AC760(this, play);
        }
    }
    if ((func_809AC6C0 == this->actionFunc) && ((func_800B9010(&this->actor, 0x2034U), (this->unk14C == 0)) ||
                                                ((this->unk14C != 0) && (this->actor.xzDistToPlayer < 240.0f)))) {
        func_809AC7F8(this, play);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
    this->unk148 = (s16)((s32)(this->unk148 + 1) % 8);
    if (func_809AC970 != this->actionFunc) {
        if ((this->actor.parent != NULL) && (this->actor.parent->update != NULL) && (this->unk150 != 0)) {
            this->actionFunc = func_809AC970;
        }
    }
}
*/
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/BgFireWall_Draw.s")

void BgFireWall_Draw(Actor *thisx, PlayState *play) {
    BgFireWall* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 0x14U);
    gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(D_809ACC94[this->unk148]));
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x01, 255, 255, 0, 150);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 255);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, &D_06000040);

    CLOSE_DISPS(play->state.gfxCtx);
}