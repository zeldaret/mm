/*
 * File: z_bg_spout_fire.c
 * Overlay: ovl_Bg_Spout_Fire
 * Description: Proximity-Activated Fire Wall Spawner
 */

#include "z_bg_spout_fire.h"
#include "objects/object_fwall/object_fwall.h"

#define FLAGS 0x00000000

#define THIS ((BgSpoutFire*)thisx)

void BgSpoutFire_Init(Actor* thisx, GlobalContext* globalCtx);
void BgSpoutFire_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgSpoutFire_Update(Actor* thisx, GlobalContext* globalCtx);
void BgSpoutFire_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80A60C24(BgSpoutFire* this, GlobalContext* globalCtx);
void func_80A60C94(BgSpoutFire* this, GlobalContext* globalCtx);
void func_80A60CDC(BgSpoutFire* this, GlobalContext* globalCtx);
void func_80A60D10(BgSpoutFire* this, GlobalContext* globalCtx);
void func_80A60E08(BgSpoutFire* this, GlobalContext* globalCtx);

const ActorInit Bg_Spout_Fire_InitVars = {
    ACTOR_BG_SPOUT_FIRE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FWALL,
    sizeof(BgSpoutFire),
    (ActorFunc)BgSpoutFire_Init,
    (ActorFunc)BgSpoutFire_Destroy,
    (ActorFunc)BgSpoutFire_Update,
    (ActorFunc)NULL,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x20000000, 0x01, 0x04 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NONE,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 30, 83, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 1, 80, 100, MASS_IMMOVABLE };

static TexturePtr D_80A61194[] = {
    object_fwall_Tex_003CA0, object_fwall_Tex_0040A0, object_fwall_Tex_0044A0, object_fwall_Tex_0048A0,
    object_fwall_Tex_004CA0, object_fwall_Tex_0050A0, object_fwall_Tex_0054A0, object_fwall_Tex_0058A0,
};

static s32 texturesDesegmented = 0;

void BgSpoutFire_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 i;
    BgSpoutFire* this = THIS;

    this->actor.scale.z = 0.13499999f;
    this->actor.scale.x = 0.13499999f;
    this->actor.scale.y = 0.01f;
    this->unk_14A = 0;
    Collider_InitAndSetCylinder(globalCtx, &this->unk14C, &this->actor, &sCylinderInit);
    this->unk14C.dim.pos.y = this->actor.world.pos.y;
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &sColChkInfoInit);
    if (!texturesDesegmented) {
        for (i = 0; i < ARRAY_COUNT(D_80A61194); i++) {
            D_80A61194[i] = Lib_SegmentedToVirtual(D_80A61194[i]);
        }
        texturesDesegmented = true;
    }
    this->actionFunc = func_80A60C94;
}

void BgSpoutFire_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgSpoutFire* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->unk14C);
}

s32 func_80A60C24(BgSpoutFire* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp18;

    Actor_OffsetOfPointInActorCoords(&this->actor, &sp18, &player->actor.world.pos);
    if ((fabsf(sp18.x) < 100.0f) && (fabsf(sp18.z) < 120.0f)) {
        return true;
    } else {
        return false;
    }
}

void func_80A60C94(BgSpoutFire* this, GlobalContext* globalCtx) {
    if (func_80A60C24(this, globalCtx)) {
        this->actor.draw = BgSpoutFire_Draw;
        this->unk_148 = 5;
        this->actionFunc = func_80A60CDC;
    }
}

void func_80A60CDC(BgSpoutFire* this, GlobalContext* globalCtx) {
    if (this->unk_148 != 0) {
        this->unk_148--;
    }
    if (this->unk_148 == 0) {
        this->actionFunc = func_80A60D10;
    }
}

void func_80A60D10(BgSpoutFire* this, GlobalContext* globalCtx) {
    if (func_80A60C24(this, globalCtx)) {
        Math_StepToF(&this->actor.scale.y, 0.1f, 0.024999999f);
        return;
    }
    if (Math_StepToF(&this->actor.scale.y, 0.01f, 0.01f)) {
        this->actor.draw = NULL;
        this->actionFunc = func_80A60C94;
        return;
    }
    this->unk_148 = 0;
}

void func_80A60DA0(Actor* thisx, GlobalContext* globalCtx) {
    s16 phi_a3;

    if (Actor_IsFacingPlayer(thisx, 0x4000)) {
        phi_a3 = thisx->shape.rot.y;
    } else {
        phi_a3 = (thisx->shape.rot.y + 0x8000);
    }
    func_800B8D98(globalCtx, thisx, 5.0f, phi_a3, 1.0f);
}

void func_80A60E08(BgSpoutFire* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp30;
    f32 cos;
    f32 sin;

    Actor_OffsetOfPointInActorCoords(&this->actor, &sp30, &player->actor.world.pos);
    sp30.x = CLAMP(sp30.x, -74.25f, 74.25f);
    if (this->unk_148 == 0) {
        if (sp30.z > 0.0f) {
            sp30.z = -25.0f;
            this->unk_148 = -1;
        } else {
            sp30.z = 25.0f;
            this->unk_148 = 1;
        }
    } else {
        sp30.z = this->unk_148 * 25.0f;
    }
    sin = Math_SinS(this->actor.shape.rot.y);
    cos = Math_CosS(this->actor.shape.rot.y);
    this->unk14C.dim.pos.x = (this->actor.world.pos.x + (sp30.x * cos) + (sp30.z * sin));
    this->unk14C.dim.pos.z = (this->actor.world.pos.z - (sp30.x * sin) + (sp30.z * cos));
}

void BgSpoutFire_Update(Actor* thisx, GlobalContext* globalCtx) {
    s16 pad;
    BgSpoutFire* this = THIS;

    this->unk_14A = ((this->unk_14A + 1) % 8);
    if ((this->unk14C.base.atFlags & AT_HIT)) {
        this->unk14C.base.atFlags &= ~AT_HIT;
        func_80A60DA0(&this->actor, globalCtx);
    }
    this->actionFunc(this, globalCtx);
    if (this->actionFunc == func_80A60D10) {
        func_80A60E08(this, globalCtx);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->unk14C.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->unk14C.base);
        func_800B9010(&this->actor, NA_SE_EV_FIRE_PLATE - SFX_FLAG);
    }
}

void BgSpoutFire_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgSpoutFire* this = THIS;
    Gfx* gfx;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gfx = Gfx_CallSetupDL(POLY_XLU_DISP, 0x14);
    POLY_XLU_DISP = gfx;
    gSPSegment(&gfx[0], 0x08, D_80A61194[this->unk_14A]);
    gDPSetPrimColor(&gfx[1], 0, 0x01, 255, 255, 0, 150);
    gDPSetEnvColor(&gfx[2], 255, 0, 0, 255);
    Matrix_Translate(-55.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    gSPMatrix(&gfx[3], Matrix_NewMtx(globalCtx->state.gfxCtx), (0x00 | 0x02) | 0x00);
    gSPDisplayList(&gfx[4], object_fwall_DL_000040);
    POLY_XLU_DISP = &gfx[5];

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
