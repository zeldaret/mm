/*
 * File: z_en_dinofos.c
 * Overlay: ovl_En_Dinofos
 * Description: Dinolfos
 */

#include "z_en_dinofos.h"
#include "objects/object_dinofos/object_dinofos.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_400)

#define THIS ((EnDinofos*)thisx)

void EnDinofos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDinofos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDinofos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDinofos_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_8089B834(EnDinofos* this, GlobalContext* globalCtx);
void func_8089D318(EnDinofos* this, GlobalContext* globalCtx);
void func_8089BBB4(EnDinofos* this, GlobalContext* globalCtx);
void func_8089B8B0(EnDinofos* this, GlobalContext* globalCtx);
void func_8089C56C(EnDinofos* this, GlobalContext* globalCtx);
void func_8089C44C(EnDinofos* this, GlobalContext* globalCtx);
void func_8089BB60(EnDinofos* this, GlobalContext* globalCtx);
void func_8089C0DC(EnDinofos* this, GlobalContext* globalCtx);
void func_8089D018(EnDinofos* this, GlobalContext* globalCtx);
void func_8089B288(EnDinofos* this, GlobalContext* globalCtx);
void func_8089BD28(EnDinofos* this, GlobalContext* globalCtx);
void func_8089D1E0(EnDinofos* this, GlobalContext* globalCtx);
void func_8089B98C(EnDinofos* this, GlobalContext* globalCtx);
void func_8089CA74(EnDinofos* this, GlobalContext* globalCtx);
void func_8089B3D4(EnDinofos* this, GlobalContext* globalCtx);
void func_8089CB10(EnDinofos* this, GlobalContext* globalCtx);
void func_8089CBEC(EnDinofos* this, GlobalContext* globalCtx);
void func_8089CF00(EnDinofos* this, GlobalContext* globalCtx);
void func_8089CF70(EnDinofos* this, GlobalContext* globalCtx);
void func_8089B580(EnDinofos* this, GlobalContext* globalCtx);
void func_8089B72C(EnDinofos* this, GlobalContext* globalCtx);
void func_8089C2A8(EnDinofos* this, GlobalContext* globalCtx);
void func_8089C1F8(EnDinofos* this, GlobalContext* globalCtx);
void func_8089C724(EnDinofos* this, GlobalContext* globalCtx);
void func_8089C7B8(EnDinofos* this, GlobalContext* globalCtx);
void func_8089C938(EnDinofos* this, GlobalContext* globalCtx);
void func_8089C4F8(EnDinofos* this);
void func_8089BAC0(EnDinofos* this);
void func_8089C024(EnDinofos* this, s32 arg1);
void func_8089D11C(EnDinofos* this, s16 arg1);
void func_8089B7B0(EnDinofos* this);
void func_8089D2E0(EnDinofos* this);
void func_8089CA14(EnDinofos* this);
void func_8089B320(EnDinofos* this);
void func_8089B4A4(EnDinofos* this);
void func_8089B6E8(EnDinofos* this);
void func_8089CFAC(EnDinofos* this);
void func_8089C398(EnDinofos* this);
void func_8089C164(EnDinofos* this);
void func_8089C244(EnDinofos* this);

const ActorInit En_Dinofos_InitVars = {
    ACTOR_EN_DINOFOS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DINOFOS,
    sizeof(EnDinofos),
    (ActorFunc)EnDinofos_Init,
    (ActorFunc)EnDinofos_Destroy,
    (ActorFunc)EnDinofos_Update,
    (ActorFunc)EnDinofos_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[9] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 1, { { 200, 300, 0 }, 19 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 8, { { 200, 200, 0 }, 17 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 16, { { 600, 200, 0 }, 15 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 15, { { 700, 100, 0 }, 10 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 2, { { 1300, 100, 0 }, 12 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON | BUMP_HOOKABLE,
            OCELEM_ON,
        },
        { 5, { { 1300, 100, 0 }, 12 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x20000000, 0x09, 0x08 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 21, { { 0, -10, 35 }, 20 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x20000000, 0x09, 0x08 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 21, { { 0, -10, 70 }, 28 }, 100 },
    },
    {
        {
            ELEMTYPE_UNK0,
            { 0x20000000, 0x09, 0x08 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 21, { { 0, -5, 110 }, 30 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT0,
        AT_NONE | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    9,
    sJntSphElementsInit,
};

static ColliderQuadInit sQuadInit = {
    {
        COLTYPE_NONE,
        AT_NONE | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x04 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0xF),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(1, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(2, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x5),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0x0),
    /* Spin attack    */ DMG_ENTRY(1, 0x0),
    /* Sword beam     */ DMG_ENTRY(1, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0x0),
};

static CollisionCheckInfoInit sColChkInfoInit = { 4, 40, 100, 80 };

static TexturePtr D_8089E33C[] = {
    object_dinofos_Tex_008E30,
    object_dinofos_Tex_009030,
    object_dinofos_Tex_009230,
    object_dinofos_Tex_009030,
};

static s16 D_8089E34C = -1;
static s32 D_8089E350 = 0;

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 16, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 15, ICHAIN_STOP),
};

void EnDinofos_Init(Actor* thisx, GlobalContext* globalCtx) {
    static s32 D_8089E364 = 0;
    static EffectBlureInit2 D_8089E368 = {
        0, 8, 0, { 255, 255, 255, 255 }, { 255, 255, 255, 64 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, 8,
        0, 2, 0, { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    };
    EnDinofos* this = THIS;
    s32 i;
    ColliderJntSphElementDim* dim;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawFeet, 90.0f);
    Effect_Add(globalCtx, &this->unk_2A0, EFFECT_BLURE2, 0, 0, &D_8089E368);
    Collider_InitAndSetJntSph(globalCtx, &this->colliderJntSph, &this->actor, &sJntSphInit,
                              this->colliderJntSphElement);
    Collider_InitAndSetQuad(globalCtx, &this->colliderQuad, &this->actor, &sQuadInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_dinofos_Skel_009570, &object_dinofos_Anim_002E40,
                       this->jointTable, this->morphTable, 21);

    if (D_8089E364 == 0) {
        for (i = 0; i < ARRAY_COUNT(D_8089E33C); i++) {
            D_8089E33C[i] = Lib_SegmentedToVirtual(D_8089E33C[i]);
        }
        D_8089E364 = 1;
    }

    this->unk_288 = 255;
    for (i = 6; i < ARRAY_COUNT(this->colliderJntSphElement); i++) {
        dim = &this->colliderJntSph.elements[i].dim;
        dim->worldSphere.radius = dim->modelSphere.radius;
    }

    this->unk_28B = 0;
    if (thisx->cutscene == -1) {
        func_8089B7B0(this);
    } else {
        this->actor.flags |= ACTOR_FLAG_100000;
        this->actor.gravity = 0.0f;
        this->actor.velocity.y = 0.0f;
        D_8089E34C = thisx->cutscene;
        func_8089D2E0(this);
    }

    D_8089E350++;
}

void EnDinofos_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDinofos* this = THIS;

    Effect_Destroy(globalCtx, this->unk_2A0);
    Collider_DestroyJntSph(globalCtx, &this->colliderJntSph);
    Collider_DestroyQuad(globalCtx, &this->colliderQuad);
}

void func_8089A900(EnDinofos* this) {
    if (this->unk_289 != 0) {
        this->unk_289++;
        if (this->unk_289 == 4) {
            this->unk_289 = 0;
        }
    } else if (Rand_ZeroOne() < 0.05f) {
        this->unk_289 = 1;
    }
}

s32 func_8089A968(EnDinofos* this) {
    s16 temp_v0 = (this->actor.yawTowardsPlayer - this->unk_28E) - this->actor.shape.rot.y;

    if (ABS_ALT(temp_v0) < 0x3000) {
        return true;
    }
    return false;
}

void func_8089A9B0(EnDinofos* this, GlobalContext* globalCtx) {
    if (func_8089A968(this)) {
        if (this->actor.xzDistToPlayer < 100.0f) {
            if (!Actor_OtherIsTargeted(globalCtx, &this->actor) &&
                (((this->actionFunc != func_8089C56C) && (Rand_ZeroOne() > 0.35f)) ||
                 ((this->actionFunc == func_8089C56C) && (Rand_ZeroOne() > 0.8f)))) {
                func_8089C4F8(this);
            } else {
                func_8089BBB4(this, globalCtx);
            }
        } else if ((this->actor.xzDistToPlayer < 260.0f) && (this->actor.xzDistToPlayer > 180.0f)) {
            if (((this->actionFunc != func_8089C44C) && (Rand_ZeroOne() < 0.1f)) ||
                ((this->actionFunc == func_8089C44C) && (Rand_ZeroOne() < 0.05f))) {
                func_8089C024(this, 0);
            } else {
                func_8089BBB4(this, globalCtx);
            }
        } else if (Rand_ZeroOne() < 0.8f) {
            func_8089B8B0(this, globalCtx);
        } else {
            func_8089BBB4(this, globalCtx);
        }
    } else if (Rand_ZeroOne() < 0.6f) {
        func_8089BAC0(this);
    } else {
        func_8089B7B0(this);
    }
}

void func_8089ABF4(EnDinofos* this, GlobalContext* globalCtx) {
    if (this->subCamId != CAM_ID_MAIN) {
        Camera* subCam = Play_GetCamera(globalCtx, this->subCamId);

        Play_CameraSetAtEye(globalCtx, CAM_ID_MAIN, &subCam->at, &subCam->eye);
        this->subCamId = CAM_ID_MAIN;
        ActorCutscene_Stop(this->actor.cutscene);
        if (this->actor.colChkInfo.health == 0) {
            func_800B724C(globalCtx, &this->actor, 6);
        }
    }
}

void func_8089AC70(EnDinofos* this) {
    this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX;
    this->drawDmgEffScale = 0.55f;
    this->colliderJntSph.base.colType = COLTYPE_HIT3;
    this->drawDmgEffFrozenSteamScale = 0.82500005f;
    this->drawDmgEffAlpha = 1.0f;
    this->unk_290 = 80;
    this->actor.flags &= ~ACTOR_FLAG_400;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 80);
}

void func_8089ACEC(EnDinofos* this, GlobalContext* globalCtx) {
    if (this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
        this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        this->colliderJntSph.base.colType = COLTYPE_HIT0;
        this->drawDmgEffAlpha = 0.0f;
        Actor_SpawnIceEffects(globalCtx, &this->actor, this->limbPos, 12, 2, 0.3f, 0.2f);
        this->actor.flags |= ACTOR_FLAG_400;
    }
}

void func_8089AD70(EnDinofos* this) {
    s32 i;

    if (this->unk_28B != 0) {
        for (i = 0; i < ARRAY_COUNT(this->colliderJntSphElement) - 3; i++) {
            this->colliderJntSph.elements[i].info.bumper.dmgFlags |= 0x400;
        }
        this->unk_28B = 0;
    }
}

s32 func_8089AE00(EnDinofos* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 temp_v1;
    s16 temp_v1_2;
    Actor* temp_v0;
    s32 i;

    temp_v0 = func_800BC270(globalCtx, &this->actor, 80.0f, 0x138B0);
    if (temp_v0 != NULL) {
        temp_v1 = (Actor_YawBetweenActors(&this->actor, temp_v0) - this->actor.shape.rot.y) - this->unk_28E;
        if (ABS_ALT(temp_v1) < 0x3000) {
            func_8089D11C(this, temp_v1 + this->unk_28E);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_WARAU);
            return true;
        }
    }

    temp_v0 = func_800BC444(globalCtx, &this->actor, 80.0f);
    if ((temp_v0 != NULL) && (temp_v0->id == ACTOR_EN_BOM_CHU)) {
        temp_v1_2 = (Actor_YawBetweenActors(&this->actor, temp_v0) - this->actor.shape.rot.y) - this->unk_28E;
        if (ABS_ALT(temp_v1_2) < 0x3000) {
            func_8089C024(this, 1);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_WARAU);
            return true;
        }
    }

    if (globalCtx->actorCtx.unk2 != 0) {
        func_8089C024(this, 1);
        return true;
    }

    if ((this->actor.xzDistToPlayer < 100.0f) && (player->swordState != 0) && this->actor.isTargeted &&
        (Rand_ZeroOne() < 0.5f) && func_8089A968(this) && Player_IsFacingActor(&this->actor, 0x2000, globalCtx)) {
        if (Rand_ZeroOne() < 0.5f) {
            func_8089C024(this, 2);
        } else {
            func_8089C024(this, 3);
        }
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_WARAU);
        return true;
    }

    if ((gSaveContext.save.playerForm == PLAYER_FORM_GORON) && (player->actor.velocity.y < -5.0f) &&
        (player->unk_AE7 == 1) && (this->unk_28B == 0)) {
        this->unk_28B = 1;
        for (i = 0; i < ARRAY_COUNT(this->colliderJntSphElement) - 3; i++) {
            this->colliderJntSph.elements[i].info.bumper.dmgFlags &= ~0x400;
        }
    }

    return false;
}

void func_8089B100(EnDinofos* this, GlobalContext* globalCtx) {
    Camera* subCam = Play_GetCamera(globalCtx, this->subCamId);
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp3C;

    Animation_Change(&this->skelAnime, &object_dinofos_Anim_001CCC, 1.0f,
                     Animation_GetLastFrame(&object_dinofos_Anim_001CCC),
                     Animation_GetLastFrame(&object_dinofos_Anim_001CCC), 2, 0.0f);
    func_800BE33C(&subCam->eye, &subCam->at, &this->unk_29A, true);
    Math_Vec3f_Diff(&this->actor.world.pos, &player->actor.world.pos, &sp3C);
    this->unk_2BC.x = player->actor.world.pos.x + (0.4f * sp3C.x);
    this->unk_2BC.y = player->actor.world.pos.y + 5.0f;
    this->unk_2BC.z = player->actor.world.pos.z + (0.4f * sp3C.z);
    this->unk_2C8.x = this->actor.world.pos.x;
    this->unk_2C8.y = this->actor.focus.pos.y - 400.0f;
    this->unk_2C8.z = this->actor.world.pos.z;
    this->unk_2AC = Math_Vec3f_DistXYZ(&subCam->eye, &this->unk_2BC) * 0.05f;
    this->unk_2A8 = Math_Vec3f_DistXYZ(&subCam->at, &this->unk_2C8) * 0.05f;
    this->unk_290 = 20;
    this->actionFunc = func_8089B288;
}

void func_8089B288(EnDinofos* this, GlobalContext* globalCtx) {
    Camera* subCam = Play_GetCamera(globalCtx, this->subCamId);

    this->unk_290--;
    Math_Vec3f_StepTo(&subCam->eye, &this->unk_2BC, this->unk_2AC);
    Math_Vec3f_StepTo(&subCam->at, &this->unk_2C8, this->unk_2A8);
    Play_CameraSetAtEye(globalCtx, this->subCamId, &subCam->at, &subCam->eye);
    if (this->unk_290 == 0) {
        func_8089B320(this);
    }
}

void func_8089B320(EnDinofos* this) {
    this->actor.gravity = -2.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_CRY);
    this->unk_2BC.x = (Math_SinS(this->actor.shape.rot.y - 0x0E00) * 86.0f) + this->actor.world.pos.x;
    this->unk_2BC.y = this->actor.floorHeight + 6.0f;
    this->unk_2BC.z = (Math_CosS(this->actor.shape.rot.y - 0x0E00) * 86.0f) + this->actor.world.pos.z;
    this->unk_290 = 0;
    this->actionFunc = func_8089B3D4;
}

void func_8089B3D4(EnDinofos* this, GlobalContext* globalCtx) {
    Camera* subCam = Play_GetCamera(globalCtx, this->subCamId);
    Vec3f subCamAt;

    Math_Vec3f_StepTo(&subCam->eye, &this->unk_2BC, 10.0f);
    this->unk_290++;
    if (this->unk_290 == 10) {
        func_801A2E54(NA_BGM_MINI_BOSS);
    }

    subCamAt.x = this->actor.world.pos.x;
    subCamAt.z = this->actor.world.pos.z;
    if (this->actor.focus.pos.y <= subCam->at.y) {
        subCamAt.y = this->actor.focus.pos.y;
    } else {
        subCamAt.y = subCam->at.y;
    }

    Play_CameraSetAtEye(globalCtx, this->subCamId, &subCamAt, &subCam->eye);
    if (this->actor.bgCheckFlags & 1) {
        func_8089B4A4(this);
    }
}

void func_8089B4A4(EnDinofos* this) {
    if (this->unk_290 < 10) {
        func_801A2E54(NA_BGM_MINI_BOSS);
    }
    Animation_PlayOnce(&this->skelAnime, &object_dinofos_Anim_00C974);
    this->unk_2BC.x = (Math_SinS(this->actor.shape.rot.y + 0x200) * 123.0f) + this->actor.world.pos.x;
    this->unk_2BC.y = this->actor.floorHeight + 11.0f;
    this->unk_2BC.z = (Math_CosS(this->actor.shape.rot.y + 0x200) * 123.0f) + this->actor.world.pos.z;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BOMCHU_WALK);
    this->unk_290 = 0;
    this->unk_292 = -1;
    this->actionFunc = func_8089B580;
}

void func_8089B580(EnDinofos* this, GlobalContext* globalCtx) {
    Camera* subCam = Play_GetCamera(globalCtx, this->subCamId);

    this->unk_290++;
    if (this->unk_290 < 8) {
        Play_CameraSetAtEye(globalCtx, this->subCamId, &this->actor.focus.pos, &subCam->eye);
    }

    if (this->skelAnime.curFrame > 35.0f) {
        if ((globalCtx->sceneNum == SCENE_MITURIN) && Animation_OnFrame(&this->skelAnime, 38.0f)) {
            globalCtx->envCtx.lightSettingOverride = 11;
        }

        Math_Vec3f_StepTo(&subCam->eye, &this->unk_2BC, 10.0f);
        Play_CameraSetAtEye(globalCtx, this->subCamId, &this->actor.focus.pos, &subCam->eye);
        if (this->skelAnime.curFrame <= 55.0f) {
            func_800B9010(&this->actor, NA_SE_EN_DODO_J_FIRE - SFX_FLAG);
        }
    }

    if ((globalCtx->sceneNum == SCENE_MITURIN) && Animation_OnFrame(&this->skelAnime, 55.0f)) {
        globalCtx->envCtx.lightSettingOverride = 0xFF;
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        func_8089B6E8(this);
    }
}

void func_8089B6E8(EnDinofos* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &object_dinofos_Anim_009B70, -3.0f);
    this->actionFunc = func_8089B72C;
}

void func_8089B72C(EnDinofos* this, GlobalContext* globalCtx) {
    if (Animation_OnFrame(&this->skelAnime, 2.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_ATTACK);
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        func_8089ABF4(this, globalCtx);
        this->actor.flags &= ~ACTOR_FLAG_100000;
        this->actor.cutscene = -1;
        func_8089B7B0(this);
    }
}

void func_8089B7B0(EnDinofos* this) {
    Animation_MorphToLoop(&this->skelAnime, &object_dinofos_Anim_002E40, -4.0f);
    this->unk_290 = (s32)Rand_ZeroFloat(20.0f) + 40;
    this->unk_292 = 30;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    func_8089AD70(this);
    this->actionFunc = func_8089B834;
}

void func_8089B834(EnDinofos* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->unk_292 != 0) {
        this->unk_292--;
    } else if (func_8089A968(this)) {
        this->unk_290 = 0;
    }

    if (this->unk_290 != 0) {
        this->unk_290--;
    } else {
        func_8089A9B0(this, globalCtx);
    }
}

void func_8089B8B0(EnDinofos* this, GlobalContext* globalCtx) {
    f32 phi_f0;

    if (this->actionFunc != func_8089B98C) {
        Animation_MorphToLoop(&this->skelAnime, &object_dinofos_Anim_000580, -4.0f);
        if (Actor_OtherIsTargeted(globalCtx, &this->actor)) {
            phi_f0 = 170.0f;
        } else {
            phi_f0 = 70.0f;
        }
        if (this->actor.xzDistToPlayer <= phi_f0) {
            this->actor.speedXZ = -3.5f;
        } else {
            this->actor.speedXZ = 3.5f;
        }
    }

    this->unk_292 = (s32)Rand_ZeroFloat(10.0f) + 20;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_8089B98C;
}

void func_8089B98C(EnDinofos* this, GlobalContext* globalCtx) {
    f32 phi_f0;

    SkelAnime_Update(&this->skelAnime);
    if (!func_8089AE00(this, globalCtx)) {
        if (Actor_OtherIsTargeted(globalCtx, &this->actor)) {
            phi_f0 = 170.0f;
        } else {
            phi_f0 = 70.0f;
        }

        Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x100);
        this->actor.world.rot.y = this->actor.shape.rot.y;
        if (this->actor.xzDistToPlayer <= phi_f0) {
            Math_StepToF(&this->actor.speedXZ, -7.0f, 0.5f);
        } else {
            Math_StepToF(&this->actor.speedXZ, 7.0f, 0.5f);
        }

        if (this->actor.xzDistToPlayer < 80.0f) {
            this->unk_292 = 0;
        }

        if (this->unk_292 != 0) {
            this->unk_292--;
        } else {
            func_8089A9B0(this, globalCtx);
        }

        if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 6.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_WALK);
        }
    }
}

void func_8089BAC0(EnDinofos* this) {
    if (this->actionFunc != func_8089BB60) {
        Animation_MorphToLoop(&this->skelAnime, &object_dinofos_Anim_000580, -4.0f);
        this->actor.speedXZ = 0.0f;
    }
    if (BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y) > 0) {
        this->unk_28C = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
    } else {
        this->unk_28C = BINANG_SUB(this->actor.shape.rot.y, 0x4000);
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
    func_8089AD70(this);
    this->actionFunc = func_8089BB60;
}

void func_8089BB60(EnDinofos* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk_28C, 0x400)) {
        func_8089A9B0(this, globalCtx);
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_8089BBB4(EnDinofos* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (this->actionFunc != func_8089BD28) {
        s16 rotY = player->actor.shape.rot.y - this->actor.shape.rot.y;
        if (ABS_ALT(rotY) > 0x7800) {
            if (Rand_ZeroOne() < 0.5f) {
                this->actor.speedXZ = 6.0f;
            } else {
                this->actor.speedXZ = -6.0f;
            }
        } else if (rotY >= 0) {
            this->actor.speedXZ = 6.0f;
        } else {
            this->actor.speedXZ = -6.0f;
        }

        if (this->actionFunc == func_8089D1E0) {
            this->skelAnime.playSpeed = this->actor.speedXZ * 0.166666671634f;
        } else {
            Animation_Change(&this->skelAnime, &object_dinofos_Anim_00D62C, this->actor.speedXZ * 0.166666671634f, 0.0f,
                             0.0f, 0, -4.0f);
        }

        this->actor.world.rot.y = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
        this->unk_2A4 = 0;
        this->unk_292 = (s32)Rand_ZeroFloat(10.0f) + 5;
    }

    this->actionFunc = func_8089BD28;
}

void func_8089BD28(EnDinofos* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 phi_v0;
    f32 sp2C = 0.0f;

    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xBB8);
    if (!func_8089AE00(this, globalCtx)) {
        if (this->actor.bgCheckFlags & 8) {
            if (this->actor.speedXZ >= 0.0f) {
                phi_v0 = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
            } else {
                phi_v0 = BINANG_SUB(this->actor.shape.rot.y, 0x4000);
            }

            phi_v0 = this->actor.wallYaw - phi_v0;
            if (ABS_ALT(phi_v0) > 0x4000) {
                this->actor.speedXZ *= -0.8f;
                if (this->actor.speedXZ < 0.0f) {
                    this->actor.speedXZ -= 0.5f;
                } else {
                    this->actor.speedXZ += 0.5f;
                }
            }
        }

        phi_v0 = BINANG_SUB(player->actor.shape.rot.y, this->actor.shape.rot.y);
        if ((phi_v0 >= 0) && (phi_v0 < 0x7800)) {
            this->actor.speedXZ += 0.125f;
        } else if ((phi_v0 < 0) && (phi_v0 > -0x7800)) {
            this->actor.speedXZ -= 0.125f;
        }

        if (this->actor.speedXZ > 0.0f) {
            this->skelAnime.playSpeed = 1.0f;
        } else {
            this->skelAnime.playSpeed = -1.0f;
        }

        this->actor.world.rot.y = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
        if (Actor_OtherIsTargeted(globalCtx, &this->actor)) {
            sp2C = 100.0f;
        }

        if (this->actor.xzDistToPlayer <= (70.0f + sp2C)) {
            Math_StepToF(&this->unk_2A4, -4.0f, 1.5f);
        } else if ((90.0f + sp2C) < this->actor.xzDistToPlayer) {
            Math_StepToF(&this->unk_2A4, 4.0f, 1.5f);
        } else {
            Math_StepToF(&this->unk_2A4, 0.0f, 5.65f);
        }

        this->actor.world.pos.x += Math_SinS(this->actor.shape.rot.y) * this->unk_2A4;
        this->actor.world.pos.z += Math_CosS(this->actor.shape.rot.y) * this->unk_2A4;
        SkelAnime_Update(&this->skelAnime);
        if (this->unk_292 != 0) {
            this->unk_292--;
        } else {
            func_8089A9B0(this, globalCtx);
        }

        if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 5.0f)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_WALK);
        }
    }
}

void func_8089C024(EnDinofos* this, s32 arg1) {
    if (arg1 == 0) {
        Animation_MorphToPlayOnce(&this->skelAnime, &object_dinofos_Anim_001CCC, 2.0f);
        func_8089AD70(this);
    } else {
        Animation_MorphToPlayOnce(&this->skelAnime, &object_dinofos_Anim_001CCC, -1.0f);
        if ((arg1 == 2) || (arg1 == 3)) {
            this->colliderJntSph.base.acFlags &= ~AC_ON;
            func_8089AD70(this);
        }
    }

    this->actor.speedXZ = 0.0f;
    this->unk_290 = arg1;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_8089C0DC;
}

void func_8089C0DC(EnDinofos* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x1000);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
        if (this->unk_290 == 3) {
            func_8089C244(this);
        } else {
            func_8089C164(this);
        }
    }
}

void func_8089C164(EnDinofos* this) {
    if (this->unk_290 == 2) {
        this->actor.speedXZ = -10.0f;
        this->actor.velocity.y = 9.0f;
        this->colliderJntSph.base.acFlags |= AC_ON;
    } else {
        this->actor.velocity.y = 12.5f;
        if (this->unk_290 == 0) {
            this->actor.speedXZ = 4.5f;
        }
    }

    this->actor.bgCheckFlags &= ~1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_JUMP);
    this->actionFunc = func_8089C1F8;
}

void func_8089C1F8(EnDinofos* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.bgCheckFlags & 1) {
        func_8089C398(this);
    }
}

void func_8089C244(EnDinofos* this) {
    this->actor.bgCheckFlags &= ~1;
    this->actor.speedXZ = 8.0f;
    this->actor.velocity.y = 16.0f;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_JUMP);
    this->unk_290 = 0;
    this->unk_292 = -1;
    this->actionFunc = func_8089C2A8;
}

void func_8089C2A8(EnDinofos* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    this->unk_290++;
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x1800);
    if ((this->actor.velocity.y < 0.0f) && (this->skelAnime.animation == &object_dinofos_Anim_001CCC)) {
        this->colliderQuad.base.atFlags |= AT_ON;
        this->colliderJntSph.base.acFlags |= AC_ON;
        Animation_Change(&this->skelAnime, &object_dinofos_Anim_0025B4, 1.0f, 7.0f, 13.0f, 2, -2.0f);
    }

    if (this->actor.bgCheckFlags & 1) {
        this->colliderQuad.base.atFlags &= ~AT_ON;
        func_8089C398(this);
    }
}

void func_8089C398(EnDinofos* this) {
    if (this->actionFunc != func_8089C2A8) {
        Animation_PlayOnce(&this->skelAnime, &object_dinofos_Anim_000AF0);
    } else {
        this->skelAnime.endFrame = Animation_GetLastFrame(&object_dinofos_Anim_0025B4);
    }

    if (this->actor.speedXZ < 0.0f) {
        this->unk_290 = 1;
    } else {
        this->unk_290 = 0;
    }

    this->actor.speedXZ = 0.0f;
    func_8089AD70(this);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_BOMCHU_WALK);
    this->actionFunc = func_8089C44C;
}

void func_8089C44C(EnDinofos* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        if ((this->unk_290 == 1) && (this->actor.xzDistToPlayer < 280.0f) && func_8089A968(this) &&
            (Rand_ZeroOne() < 0.6f)) {
            func_8089CA14(this);
        } else {
            func_8089A9B0(this, globalCtx);
        }
    }
}

void func_8089C4F8(EnDinofos* this) {
    Animation_PlayOnce(&this->skelAnime, &object_dinofos_Anim_0025B4);
    this->colliderQuad.base.atFlags &= ~AT_BOUNCED;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_CRY);
    this->unk_290 = 0;
    this->unk_292 = -1;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_8089C56C;
}

void func_8089C56C(EnDinofos* this, GlobalContext* globalCtx) {
    this->unk_290++;
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x800);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (SkelAnime_Update(&this->skelAnime)) {
        EffectBlure_AddSpace(Effect_GetByIndex(this->unk_2A0));
        this->colliderQuad.base.atFlags &= ~AT_ON;
        func_8089A9B0(this, globalCtx);
    } else if (Animation_OnFrame(&this->skelAnime, 7.0f)) {
        this->colliderQuad.base.atFlags |= AT_ON;
        func_8089AD70(this);
    } else if (Animation_OnFrame(&this->skelAnime, 13.0f)) {
        this->colliderQuad.base.atFlags &= ~AT_ON;
    } else if (Animation_OnFrame(&this->skelAnime, 11.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_ATTACK);
    } else if (this->skelAnime.curFrame < 7.0f) {
        func_8089AE00(this, globalCtx);
    }
}

void func_8089C690(EnDinofos* this) {
    Animation_Change(&this->skelAnime, &object_dinofos_Anim_0025B4, -1.0f, this->skelAnime.curFrame, 0.0f, 2, 0.0f);
    this->colliderQuad.base.atFlags &= ~(AT_ON | AT_BOUNCED);
    if (this->actionFunc != func_8089C2A8) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
    } else {
        this->actor.speedXZ = 3.0f;
    }
    this->actionFunc = func_8089C724;
}

void func_8089C724(EnDinofos* this, GlobalContext* globalCtx) {
    if (this->actor.bgCheckFlags & 1) {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    }

    if (SkelAnime_Update(&this->skelAnime)) {
        func_8089A9B0(this, globalCtx);
    }
}

void func_8089C784(EnDinofos* this) {
    this->actor.speedXZ = 0.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->actionFunc = func_8089C7B8;
}

void func_8089C7B8(EnDinofos* this, GlobalContext* globalCtx) {
    if (this->unk_290 != 0) {
        this->unk_290--;
    }

    if (this->unk_290 == 0) {
        func_8089ACEC(this, globalCtx);
        if (this->actor.colChkInfo.health == 0) {
            if (this->actor.cutscene == -1) {
                func_8089CFAC(this);
            } else {
                func_8089D2E0(this);
            }
        } else if (func_8089A968(this) && (this->actor.xzDistToPlayer < 100.0f)) {
            func_8089CA14(this);
        } else {
            func_8089A9B0(this, globalCtx);
        }
    }
}

void func_8089C87C(EnDinofos* this, s32 arg1) {
    Animation_PlayOnce(&this->skelAnime, &object_dinofos_Anim_00D21C);
    func_800BE5CC(&this->actor, &this->colliderJntSph, arg1);
    this->actor.shape.rot.y = BINANG_ROT180(this->actor.world.rot.y);
    this->actor.speedXZ = 10.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->unk_28E = 0;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_DAMAGE);
    this->colliderJntSph.base.acFlags &= ~AC_ON;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 18);
    this->actionFunc = func_8089C938;
}

void func_8089C938(EnDinofos* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (SkelAnime_Update(&this->skelAnime) && (this->actor.bgCheckFlags & 1)) {
        if (this->actor.colChkInfo.health == 0) {
            if (this->actor.cutscene == -1) {
                func_8089CFAC(this);
            } else {
                func_8089D2E0(this);
            }
        } else if (this->actor.xzDistToPlayer < 280.0f) {
            func_8089CA14(this);
        } else {
            this->colliderJntSph.base.acFlags |= AC_ON;
            func_8089A9B0(this, globalCtx);
        }
    }
}

void func_8089CA14(EnDinofos* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &object_dinofos_Anim_001040, -5.0f);
    this->colliderJntSph.base.acFlags |= AC_ON;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_8089CA74;
}

void func_8089CA74(EnDinofos* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x800);
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (SkelAnime_Update(&this->skelAnime)) {
        func_8089CB10(this, globalCtx);
    } else if (!func_8089AE00(this, globalCtx) && Animation_OnFrame(&this->skelAnime, 12.0f)) {
        this->actor.speedXZ = 8.0f;
    }
}

void func_8089CB10(EnDinofos* this, GlobalContext* globalCtx) {
    s32 i;
    Sphere16* worldSphere;

    Animation_PlayLoop(&this->skelAnime, &object_dinofos_Anim_0013C0);
    this->unk_290 = 20;
    this->actor.speedXZ = 0.0f;
    this->colliderJntSph.base.atFlags |= AT_ON;
    func_8089AD70(this);

    for (i = 6; i < ARRAY_COUNT(this->colliderJntSphElement); i++) {
        worldSphere = &this->colliderJntSph.elements[i].dim.worldSphere;
        worldSphere->center.x = this->limbPos[10].x;
        worldSphere->center.y = this->limbPos[10].y;
        worldSphere->center.z = this->limbPos[10].z;
    }

    if (globalCtx->sceneNum == SCENE_MITURIN) {
        globalCtx->envCtx.lightSettingOverride = 11;
    }

    this->actionFunc = func_8089CBEC;
}

void func_8089CBEC(EnDinofos* this, GlobalContext* globalCtx) {
    s16 temp_s3 = ((s32)randPlusMinusPoint5Scaled(0x1000) + this->actor.shape.rot.y) + this->unk_28E;
    Vec3f sp88;
    Vec3f sp7C;
    ColliderJntSphElementDim* dim;
    s32 i;
    s32 end;
    f32 temp_f20;
    f32 temp_f22;
    s32 temp_s0;

    SkelAnime_Update(&this->skelAnime);
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x800);
    temp_f20 = Math_SinS(temp_s3);
    temp_f22 = Math_CosS(temp_s3);

    temp_s0 = 10 - this->unk_290;
    temp_s0 = CLAMP_MIN(temp_s0, 0);

    sp88.x = 11.0f * temp_f20;
    sp88.y = randPlusMinusPoint5Scaled(2.0f) + -5.4f;
    sp88.z = 11.0f * temp_f22;
    sp7C.x = 0.9f * temp_f20;
    sp7C.y = randPlusMinusPoint5Scaled(0.6f) + 1.4f;
    sp7C.z = 0.9f * temp_f22;
    func_800B9010(&this->actor, NA_SE_EN_DODO_J_FIRE - SFX_FLAG);
    EffectSsDFire_Spawn(globalCtx, &this->limbPos[10], &sp88, &sp7C, 30, 22, 255 - (temp_s0 * 20), 20, 3, 8);

    for (end = 6, i = 3; i > 0; i--) {
        if (this->unk_290 < (20 + -(i * 2))) {
            end = i + 6;
            break;
        }
    }

    for (i = 6; i < end; i++) {
        dim = &this->colliderJntSph.elements[i].dim;
        temp_s3 = (s32)(cos_rad((this->unk_290 + ((i - 5) << 1)) * (M_PI / 20)) * 0x2C00) + this->actor.shape.rot.y;

        dim->worldSphere.center.x = (s32)this->limbPos[10].x + (s32)(Math_SinS(temp_s3) * dim->modelSphere.center.z);
        dim->worldSphere.center.y = (s32)this->limbPos[10].y + (s32)dim->modelSphere.center.y;
        dim->worldSphere.center.z = (s32)this->limbPos[10].z + (s32)(Math_CosS(temp_s3) * dim->modelSphere.center.z);
    }

    if (this->unk_290 != 0) {
        this->unk_290--;
    } else {
        func_8089CF00(this, globalCtx);
    }
}

void func_8089CF00(EnDinofos* this, GlobalContext* globalCtx) {
    Animation_PlayOnce(&this->skelAnime, &object_dinofos_Anim_0017B8);
    this->colliderJntSph.base.atFlags &= ~AT_ON;
    if (globalCtx->sceneNum == SCENE_MITURIN) {
        globalCtx->envCtx.lightSettingOverride = 255;
    }
    this->actionFunc = func_8089CF70;
}

void func_8089CF70(EnDinofos* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        func_8089A9B0(this, globalCtx);
    }
}

void func_8089CFAC(EnDinofos* this) {
    Animation_PlayOnce(&this->skelAnime, &object_dinofos_Anim_00ABD0);
    this->actor.flags &= ~ACTOR_FLAG_1;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_DEAD);
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_8089D018;
}

void func_8089D018(EnDinofos* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        s32 temp_v0 = this->unk_288 - 10;

        if (this->actor.category == ACTORCAT_ENEMY) {
            func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_PROP);
            func_8089ABF4(this, globalCtx);
        }

        if (temp_v0 <= 0) {
            Actor_MarkForDeath(&this->actor);
            this->unk_288 = 0;
        } else {
            this->unk_288 = temp_v0;
        }

        if (this->drawDmgEffAlpha > 0.0f) {
            this->drawDmgEffAlpha = this->unk_288 * (1.0f / 255.0f);
        }

        this->actor.shape.shadowAlpha = this->unk_288;
    } else if (Animation_OnFrame(&this->skelAnime, 26.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_GERUDOFT_DOWN);
    }
}

void func_8089D11C(EnDinofos* this, s16 arg1) {
    if (arg1 >= 0) {
        this->actor.speedXZ = -15.0f;
    } else {
        this->actor.speedXZ = 15.0f;
    }
    Animation_Change(&this->skelAnime, &object_dinofos_Anim_00D62C, this->actor.speedXZ * (1.0f / 7.5f), 0.0f, 0.0f, 0,
                     -4.0f);
    this->actor.world.rot.y = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
    this->unk_292 = 10;
    this->unk_2A4 = 0.0f;
    func_8089AD70(this);
    this->actionFunc = func_8089D1E0;
}

void func_8089D1E0(EnDinofos* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xBB8);
    Math_StepToF(&this->actor.speedXZ, 0.0f, 2.0f);

    this->skelAnime.playSpeed =
        (1.0f + fabsf(this->actor.speedXZ * (1.0f / 15.0f))) * ((this->actor.speedXZ >= 0.0f) ? 1.0f : -1.0f);
    this->actor.world.rot.y = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
    SkelAnime_Update(&this->skelAnime);
    if (this->unk_292 != 0) {
        this->unk_292--;
    } else {
        func_8089A9B0(this, globalCtx);
    }

    if (Animation_OnFrame(&this->skelAnime, 0.0f) || Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_RIZA_WALK);
    }
}

void func_8089D2E0(EnDinofos* this) {
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    this->actionFunc = func_8089D318;
}

void func_8089D318(EnDinofos* this, GlobalContext* globalCtx) {
    Vec3f subCamEye;

    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        if (this->actor.colChkInfo.health == 0) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
            func_800B724C(globalCtx, &this->actor, 7);
        } else {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        }
        this->subCamId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        if (this->actor.colChkInfo.health == 0) {
            subCamEye.x = (Math_SinS(this->actor.shape.rot.y) * 150.0f) + this->actor.focus.pos.x;
            subCamEye.y = this->actor.focus.pos.y;
            subCamEye.z = (Math_CosS(this->actor.shape.rot.y) * 150.0f) + this->actor.focus.pos.z;
            Play_CameraSetAtEye(globalCtx, this->subCamId, &this->actor.focus.pos, &subCamEye);
            func_8089CFAC(this);
        } else {
            func_8089B100(this, globalCtx);
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_8089D42C(EnDinofos* this, GlobalContext* globalCtx) {
    s16 temp_v0_2;

    if ((this->actionFunc == func_8089B834) && (this->unk_290 != 0)) {
        Math_ScaledStepToS(&this->unk_28E, Math_SinS(this->unk_290 * 1400) * 0x2C00, 0x300);
    } else if (this->actionFunc == func_8089CA74) {
        Math_ScaledStepToS(&this->unk_28E, cos_rad(M_PI) * 0x2C00, 0x233);
    } else if (this->actionFunc == func_8089CBEC) {
        this->unk_28E = cos_rad(this->unk_290 * (M_PI / 20)) * 0x2C00;
    } else if (!Play_InCsMode(globalCtx)) {
        temp_v0_2 = this->unk_28E + this->actor.shape.rot.y;
        temp_v0_2 = BINANG_SUB(this->actor.yawTowardsPlayer, temp_v0_2);
        temp_v0_2 = CLAMP(temp_v0_2, -0x300, 0x300);
        this->unk_28E += temp_v0_2;
        this->unk_28E = CLAMP(this->unk_28E, -0x2C00, 0x2C00);
    }
}

s32 func_8089D60C(EnDinofos* this, GlobalContext* globalCtx) {
    s32 i;

    if (this->colliderJntSph.base.acFlags & AC_HIT) {
        this->colliderJntSph.base.acFlags &= ~AC_HIT;
        Actor_SetDropFlagJntSph(&this->actor, &this->colliderJntSph);

        for (i = 0; i < ARRAY_COUNT(this->colliderJntSphElement); i++) {
            if (this->colliderJntSph.elements[i].info.bumperFlags & BUMP_HIT) {
                break;
            }
        }

        if (i == ARRAY_COUNT(this->colliderJntSphElement)) {
            return false;
        }

        if ((this->drawDmgEffType == ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) &&
            (this->colliderJntSph.elements[i].info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
            return false;
        }

        if (this->actor.colChkInfo.damageEffect == 0xF) {
            return false;
        }

        if (!Actor_ApplyDamage(&this->actor)) {
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            D_8089E350--;
            if (D_8089E350 == 0) {
                if (D_8089E34C != -1) {
                    this->actor.cutscene = D_8089E34C;
                }
            }

            if (this->actor.cutscene != -1) {
                func_801A2ED8();
            }
        }

        func_8089ACEC(this, globalCtx);
        func_8089AD70(this);
        if (globalCtx->sceneNum == SCENE_MITURIN) {
            globalCtx->envCtx.lightSettingOverride = 255;
        }

        this->colliderQuad.base.atFlags &= ~(AT_ON | AT_BOUNCED);
        this->colliderJntSph.base.atFlags &= ~AT_ON;
        if (this->actor.colChkInfo.damageEffect == 3) {
            func_8089AC70(this);
            if (this->actor.colChkInfo.health == 0) {
                this->unk_290 = 3;
                this->colliderJntSph.base.acFlags &= ~AC_ON;
            }
            func_8089C784(this);
            return true;
        }

        if (this->actor.colChkInfo.damageEffect == 1) {
            this->unk_290 = 40;
            Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
            func_8089C784(this);
            return true;
        }

        if (this->actor.colChkInfo.damageEffect == 5) {
            this->unk_290 = 40;
            Actor_SetColorFilter(&this->actor, 0, 255, 0, 40);
            this->drawDmgEffScale = 0.55f;
            this->drawDmgEffAlpha = 2.0f;
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_ELECTRIC_SPARKS_MEDIUM;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
            func_8089C784(this);
            return true;
        }

        if (this->actor.colChkInfo.damageEffect == 2) {
            this->drawDmgEffAlpha = 4.0f;
            this->drawDmgEffScale = 0.55f;
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_FIRE;
        } else if (this->actor.colChkInfo.damageEffect == 4) {
            this->drawDmgEffAlpha = 4.0f;
            this->drawDmgEffScale = 0.55f;
            this->drawDmgEffType = ACTOR_DRAW_DMGEFF_LIGHT_ORBS;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG,
                        this->colliderJntSph.elements[i].info.bumper.hitPos.x,
                        this->colliderJntSph.elements[i].info.bumper.hitPos.y,
                        this->colliderJntSph.elements[i].info.bumper.hitPos.z, 0, 0, 0, CLEAR_TAG_LARGE_LIGHT_RAYS);
        }
        func_8089C87C(this, i);
        return true;
    }

    return false;
}

void EnDinofos_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnDinofos* this = THIS;
    s32 pad;
    Vec3f sp30;

    if (this->actionFunc != func_8089C7B8) {
        func_8089A900(this);
    }

    if (!func_8089D60C(this, globalCtx) && (this->colliderQuad.base.atFlags & AT_BOUNCED)) {
        func_8089C690(this);
    }

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 25.0f, 30.0f, 60.0f, 0x5D);
    if (this->actionFunc != func_8089C7B8) {
        if ((this->actor.depthInWater > 0.0f) && (this->actor.depthInWater < 10.0f)) {
            if (!((globalCtx->gameplayFrames % 4) & 1)) {
                Math_Vec3f_Copy(&sp30, &this->limbPos[1 + (globalCtx->gameplayFrames % 4)]);
                sp30.y = this->actor.world.pos.y + this->actor.depthInWater;
                EffectSsGRipple_Spawn(globalCtx, &sp30, 100, 320, 0);
            }
        }
        if (this->actionFunc != func_8089D018) {
            func_8089D42C(this, globalCtx);
        }
    }

    if ((this->actionFunc == func_8089D018) || (this->actionFunc == func_8089C938)) {
        Math_ScaledStepToS(&this->unk_28E, 0, 2000);
    }

    Math_Vec3f_Copy(&this->actor.focus.pos, &this->limbPos[4]);
    this->actor.focus.rot.y = this->actor.shape.rot.y + this->unk_28E;
    if (this->colliderJntSph.base.acFlags & AC_ON) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
    if (this->colliderJntSph.base.atFlags & AT_ON) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
    }

    if (this->colliderQuad.base.atFlags & AT_ON) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderQuad.base);
    }

    if (this->drawDmgEffAlpha > 0.0f) {
        if (this->drawDmgEffType != ACTOR_DRAW_DMGEFF_FROZEN_NO_SFX) {
            Math_StepToF(&this->drawDmgEffAlpha, 0.0f, 0.05f);
            this->drawDmgEffScale = (this->drawDmgEffAlpha + 1.0f) * (11.0f / 40.0f);
            this->drawDmgEffScale = CLAMP_MAX(this->drawDmgEffScale, 0.55f);
        } else if (!Math_StepToF(&this->drawDmgEffFrozenSteamScale, 0.55f, 0.01375f)) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }
}

s32 func_8089DC4C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                  Gfx** gfx) {
    EnDinofos* this = THIS;

    if (limbIndex == 16) {
        rot->y -= this->unk_28E;
    }

    return 0;
}

void func_8089DC84(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    static Vec3f D_8089E38C = { 400.0f, -3600.0f, 0.0f };
    static Vec3f D_8089E398 = { 300.0f, 500.0f, 0.0f };
    static Vec3f D_8089E3A4 = { 700.0f, 400.0f, 0.0f };
    static s8 D_8089E3B0[] = {
        -1, -1, 0, -1, 1, 2, -1, 3, 4, -1, 5, 6, -1, 7, 8, -1, 9, 10, -1, 11, -1,
    };
    EnDinofos* this = THIS;
    Vec3f sp80;
    Vec3f sp74;
    Vec3f sp68;
    Vec3f sp5C;
    s32 sp58;
    Vec3f sp4C;
    MtxF* sp48;

    Collider_UpdateSpheres(limbIndex, &this->colliderJntSph);
    if (D_8089E3B0[limbIndex] != -1) {
        Matrix_GetStateTranslation(&this->limbPos[D_8089E3B0[limbIndex]]);
    }

    if ((limbIndex == 14) && (this->unk_292 != this->unk_290) &&
        ((this->actionFunc == func_8089C56C) || (this->actionFunc == func_8089C2A8))) {
        Math_Vec3f_Copy(&sp74, &this->colliderQuad.dim.quad[0]);
        Math_Vec3f_Copy(&sp80, &this->colliderQuad.dim.quad[1]);
        Matrix_MultiplyVector3fByState(&D_8089E38C, &sp68);
        Matrix_MultiplyVector3fByState(&D_8089E398, &sp5C);
        Collider_SetQuadVertices(&this->colliderQuad, &sp5C, &sp68, &sp74, &sp80);
        if (this->colliderQuad.base.atFlags & AT_ON) {
            EffectBlure_AddVertex(Effect_GetByIndex(this->unk_2A0), &sp68, &sp5C);
        }
        this->unk_292 = this->unk_290;
    }

    if (limbIndex == 4) {
        Matrix_GetStateTranslationAndScaledX(300.0f, &this->actor.shape.feetPos[0]);
    } else if (limbIndex == 7) {
        Matrix_GetStateTranslationAndScaledX(300.0f, &this->actor.shape.feetPos[1]);
    }

    if ((limbIndex == 16) && (this->actionFunc == func_8089B580)) {
        if ((this->skelAnime.curFrame > 38.0f) && (this->skelAnime.curFrame <= 55.0f) &&
            (this->unk_292 != this->unk_290)) {
            sp48 = Matrix_GetCurrentState();
            sp58 = 48 - (s32)this->skelAnime.curFrame;
            sp58 = CLAMP_MIN(sp58, 0);
            Matrix_MultiplyVector3fByState(&D_8089E3A4, &sp4C);
            sp4C.x -= sp48->mf[3][0];
            sp4C.y -= sp48->mf[3][1];
            sp4C.z -= sp48->mf[3][2];
            EffectSsDFire_Spawn(globalCtx, &this->limbPos[10], &sp4C, &gZeroVec3f, 30, 22, 255 - (sp58 * 20), 20, 3, 8);
            this->unk_292 = this->unk_290;
        }
    }
}

void EnDinofos_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDinofos* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_288 == 255) {
        func_8012C28C(globalCtx->state.gfxCtx);
        func_800B8050(&this->actor, globalCtx, 0);

        gSPSegment(POLY_OPA_DISP++, 0x08, D_8089E33C[this->unk_289]);
        gDPSetEnvColor(POLY_OPA_DISP++, 20, 40, 40, 255);

        Scene_SetRenderModeXlu(globalCtx, 0, 1);
        POLY_OPA_DISP =
            SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                               this->skelAnime.dListCount, func_8089DC4C, func_8089DC84, &this->actor, POLY_OPA_DISP);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);
        func_800B8118(&this->actor, globalCtx, 0);

        gSPSegment(POLY_XLU_DISP++, 0x08, D_8089E33C[this->unk_289]);
        gDPSetEnvColor(POLY_XLU_DISP++, 20, 40, 40, this->unk_288);

        Scene_SetRenderModeXlu(globalCtx, 1, 2);
        POLY_XLU_DISP =
            SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                               this->skelAnime.dListCount, func_8089DC4C, func_8089DC84, &this->actor, POLY_XLU_DISP);
    }

    Actor_DrawDamageEffects(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), this->drawDmgEffScale,
                            this->drawDmgEffFrozenSteamScale, this->drawDmgEffAlpha, this->drawDmgEffType);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
