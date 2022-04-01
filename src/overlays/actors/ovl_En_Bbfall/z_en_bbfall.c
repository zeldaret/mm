/*
 * File: z_en_bbfall.c
 * Overlay: ovl_En_Bbfall
 * Description: Red Bubble
 */

#include "z_en_bbfall.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_200)

#define THIS ((EnBbfall*)thisx)

void EnBbfall_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBbfall_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808BF734(EnBbfall* this, GlobalContext* globalCtx);
void func_808BF830(EnBbfall* this, GlobalContext* globalCtx);
void func_808BF8DC(EnBbfall* this, GlobalContext* globalCtx);
void func_808BFA3C(EnBbfall* this, GlobalContext* globalCtx);
void func_808BFB4C(EnBbfall* this, GlobalContext* globalCtx);
void func_808BFE58(EnBbfall* this, GlobalContext* globalCtx);
void func_808C00A0(EnBbfall* this, GlobalContext* globalCtx);
void func_808C0178(EnBbfall* this, GlobalContext* globalCtx);
void func_808BF5E0(EnBbfall* this);
void func_808BF7A0(EnBbfall* this);
void func_808BF894(EnBbfall* this);
void func_808BFA18(EnBbfall* this);

#if 0
const ActorInit En_Bbfall_InitVars = {
    ACTOR_EN_BBFALL,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_BB,
    sizeof(EnBbfall),
    (ActorFunc)EnBbfall_Init,
    (ActorFunc)EnBbfall_Destroy,
    (ActorFunc)EnBbfall_Update,
    (ActorFunc)EnBbfall_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[3] = {
static ColliderJntSphElementInit D_808C0D30[3] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x08 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_NONE, OCELEM_NONE, },
        { 0, { { 0, 0, 0 }, 20 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_808C0D9C = {
    { COLTYPE_HIT3, AT_NONE | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    3, D_808C0D30, // sJntSphElementsInit,
};

// static DamageTable sDamageTable = {
static DamageTable D_808C0DAC = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(1, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

// sColChkInfoInit
static CollisionCheckInfoInit D_808C0DCC = { 2, 20, 40, 50 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808C0DD4[] = {
    ICHAIN_S8(hintId, 36, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 10, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_808C0D30[3];
extern ColliderJntSphInit D_808C0D9C;
extern DamageTable D_808C0DAC;
extern CollisionCheckInfoInit D_808C0DCC;
extern InitChainEntry D_808C0DD4[];

extern SkeletonHeader D_06001A30;
extern AnimationHeader D_06000184;
extern AnimationHeader D_06000444;

void EnBbfall_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBbfall* this = THIS;
    s32 i;

    Actor_ProcessInitChain(&this->actor, D_808C0DD4);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06001A30, &D_06000444, this->jointTable, this->morphTable, 16);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &D_808C0DAC, &D_808C0DCC);
    Collider_InitAndSetJntSph(globalCtx, &this->collider, &this->actor, &D_808C0D9C, this->colliderElements);
    ActorShape_Init(&this->actor.shape, 1500.0f, ActorShadow_DrawCircle, 35.0f);
    this->unk_250 = 0;
    func_808BF5E0(this);
    Actor_SetFocus(&this->actor, 0.0f);
    for (i = 0; i < 3; i++) {
        this->collider.elements[i].dim.worldSphere.radius = this->collider.elements[i].dim.modelSphere.radius;
    }
}

void EnBbfall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBbfall* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF3B8.s")

s32 func_808BF438(EnBbfall* this, GlobalContext* globalCtx) {
    if (!SurfaceType_IsWallDamage(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId)) {
        u32 temp_v0 = func_800C99D4(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);

        if ((temp_v0 == 2) || (temp_v0 == 3) || (temp_v0 == 9)) {
            return 1;
        }
    }

    return 0;
}

void func_808BF4B4(EnBbfall* this) {
    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLE_MOUTH);
    }

    func_800B9010(&this->actor, NA_SE_EN_BUBLEFALL_FIRE - SFX_FLAG);
}

void func_808BF514(EnBbfall* this) {
    if (this->actor.bgCheckFlags & 8) {
        s16 temp_v1 = this->actor.shape.rot.y - this->actor.wallYaw;

        if (ABS_ALT(temp_v1) > 0x4000) {
            this->actor.shape.rot.y = (this->actor.wallYaw * 2) - this->actor.shape.rot.y - 0x8000;
        }

        this->actor.bgCheckFlags &= ~8;
    }
}

void func_808BF578(EnBbfall* this) {
    this->collider.elements->info.toucher.effect = 1;
    this->collider.elements[1].info.toucherFlags |= 1;
    this->collider.elements[2].info.toucherFlags |= 1;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BF5AC.s")

void func_808BF5E0(EnBbfall* this) {
    s32 i;

    Animation_PlayLoop(&this->skelAnime, &D_06000184);
    this->collider.base.atFlags &= ~AT_ON;
    this->collider.base.acFlags &= ~AC_ON;
    this->collider.base.ocFlags1 &= ~OC1_ON;
    this->unk_254 = 0.8f;
    this->unk_258 = 1.0f;
    this->unk_24C = -1;
    this->actor.colChkInfo.health = D_808C0DCC.health;
    this->actor.colorFilterTimer = 0;
    this->unk_24D = 0;
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.velocity.y = 0.0f;
    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.home.pos);
    this->actor.world.pos.y -= 90.0f;
    for (i = 0; i < 6; i++) {
        Math_Vec3f_Copy(&this->unk_268[i], &this->actor.world.pos);
        this->unk_268[i].y -= 47.0f;
    }

    this->actor.bgCheckFlags &= ~1;
    this->actor.flags &= ~ACTOR_FLAG_1;
    this->actionFunc = func_808BF734;
}

void func_808BF734(EnBbfall* this, GlobalContext* globalCtx) {
    if (this->unk_250 != 0) {
        this->unk_250--;
    } else if ((Player_GetMask(globalCtx) != PLAYER_MASK_STONE) && (this->actor.xyzDistToPlayerSq <= SQ(250.0f))) {
        func_808BF7A0(this);
    }
}

void func_808BF7A0(EnBbfall* this) {
    this->actor.gravity = -1.0f;
    this->actor.world.rot.y = this->actor.yawTowardsPlayer;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->collider.base.atFlags |= AT_ON;
    this->collider.base.acFlags |= AC_ON;
    this->collider.base.ocFlags1 |= OC1_ON;
    this->actor.velocity.y = 17.0f;
    func_808BF578(this);
    this->actor.flags |= ACTOR_FLAG_1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BUBLEFALL_APPEAR);
    this->actionFunc = func_808BF830;
}

void func_808BF830(EnBbfall* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.home.pos.y < this->actor.world.pos.y) {
        func_808BF894(this);
    }

    func_808BF4B4(this);
}

void func_808BF894(EnBbfall* this) {
    this->unk_24C = 0xFF;
    this->unk_24D = 1;
    this->actor.bgCheckFlags &= ~1;
    this->actor.speedXZ = 5.0f;
    this->actor.gravity = -1.0f;
    this->actionFunc = func_808BF8DC;
}

void func_808BF8DC(EnBbfall* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->unk_254, 0.8f, 0.1f);
    Math_StepToF(&this->unk_258, 1.0f, 0.1f);
    func_808BF514(this);
    if (this->actor.bgCheckFlags & 1) {
        if (func_808BF438(this, globalCtx)) {
            func_808BFA18(this);
        } else {
            this->actor.velocity.y *= -1.2f;
            this->actor.velocity.y = CLAMP(this->actor.velocity.y, 8.0f, 12.0f);
            this->actor.shape.rot.y += (s16)randPlusMinusPoint5Scaled(73728.0f);
        }

        this->actor.bgCheckFlags &= ~1;
    }

    this->actor.world.rot.y = this->actor.shape.rot.y;
    func_808BF4B4(this);
}

void func_808BFA18(EnBbfall* this) {
    this->unk_24D = 0;
    this->collider.base.acFlags &= ~AC_ON;
    this->actionFunc = func_808BFA3C;
}

void func_808BFA3C(EnBbfall* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.world.pos.y < (this->actor.floorHeight - 90.0f)) {
        this->unk_250 = 0xA;
        func_808BF5E0(this);
    } else {
        func_808BF4B4(this);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFAB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFB4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFE58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808BFF8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C00A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C013C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C0178.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C01E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/EnBbfall_Update.s")

s32 func_808C07D4(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C07D4.s")

void func_808C080C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bbfall/func_808C080C.s")

void EnBbfall_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnBbfall* this = THIS;
    MtxF* currentMatrixState;
    Gfx* gfx;
    s32 phi_s3;
    Vec3f* ptr;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gfx = POLY_OPA_DISP;
    gSPDisplayList(&gfx[0], &sSetupDL[6 * 25]);
    POLY_OPA_DISP = &gfx[1];
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, func_808C07D4, func_808C080C,
                      &this->actor);

    if (this->unk_24C > 0) {
        func_8012C2DC(globalCtx->state.gfxCtx);
        Matrix_RotateY(
            ((Camera_GetCamDirYaw(globalCtx->cameraPtrs[globalCtx->activeCamera]) - this->actor.shape.rot.y) + 0x8000),
            MTXMODE_APPLY);
        Matrix_Scale(this->unk_258, this->unk_254, 1.0f, MTXMODE_APPLY);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
        currentMatrixState = Matrix_GetCurrentState();

        phi_s3 = this->unk_24C;
        ptr = &this->unk_268[0];

        for (i = 0; i < ARRAY_COUNT(this->unk_268); i++, ptr++) {
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 32, 64, 1, 0,
                                        ((globalCtx->gameplayFrames + (i * 10)) * (-20 + i * 2)) & 0x1FF, 32, 128));
            gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 0, phi_s3);
            currentMatrixState->mf[3][0] = ptr->x;
            currentMatrixState->mf[3][1] = ptr->y;
            currentMatrixState->mf[3][2] = ptr->z;
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gGameplayKeepDrawFlameDL);

            phi_s3 -= 35;
            if (phi_s3 < 0) {
                break;
            }

            Matrix_Scale(0.87f, 0.87f, 1.0f, MTXMODE_APPLY);
        }
    }

    Actor_DrawDamageEffects(globalCtx, &this->actor, this->bodyPartsPos, ARRAY_COUNT(this->bodyPartsPos),
                            this->drawDmgEffScale, this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha,
                            this->drawDmgEffType);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
