/*
 * File: z_en_dinofos.c
 * Overlay: ovl_En_Dinofos
 * Description: Dinolfos
 */

#include "z_en_dinofos.h"

#define FLAGS 0x00000435

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

extern FlexSkeletonHeader D_06009570;
extern AnimationHeader D_06002E40;
extern AnimationHeader D_060025B4;
extern AnimationHeader D_06000580;
extern AnimationHeader D_06001CCC;
extern AnimationHeader D_0600ABD0;
extern AnimationHeader D_0600D62C;
extern AnimationHeader D_06001040;
extern AnimationHeader D_060013C0;
extern AnimationHeader D_060017B8;
extern AnimationHeader D_0600C974;
extern AnimationHeader D_06009B70;
extern AnimationHeader D_06000AF0;
extern AnimationHeader D_0600D21C;
extern Gfx D_06008E30[];
extern Gfx D_06009030[];
extern Gfx D_06009230[];
extern Gfx D_06009030[];

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

static Gfx* D_8089E33C[] = {
    D_06008E30,
    D_06009030,
    D_06009230,
    D_06009030,
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
    static EffBlureInit2 D_8089E368 = {
        0, 8, 0, { 255, 255, 255, 255 }, { 255, 255, 255, 64 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, 8,
        0, 2, 0, { 0, 0, 0, 0 },         { 0, 0, 0, 0 },
    };
    EnDinofos* this = THIS;
    s32 i;
    ColliderJntSphElementDim* dim;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B42F8, 90.0f);
    Effect_Add(globalCtx, &this->unk_2A0, 2, 0, 0, &D_8089E368);
    Collider_InitAndSetJntSph(globalCtx, &this->colliderJntSph, &this->actor, &sJntSphInit,
                              this->colliderJntSphElement);
    Collider_InitAndSetQuad(globalCtx, &this->colliderQuad, &this->actor, &sQuadInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    SkelAnime_InitSV(globalCtx, &this->skelAnime, &D_06009570, &D_06002E40, this->jointTable, this->morphTable, 21);

    if (D_8089E364 == 0) {
        for (i = 0; i < ARRAY_COUNT(D_8089E33C); i++) {
            D_8089E33C[i] = (Gfx*)Lib_SegmentedToVirtual(D_8089E33C[i]);
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
        this->actor.flags |= 0x100000;
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
            if (!func_800BC5EC(globalCtx, &this->actor) &&
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
    if (this->camId != 0) {
        Camera* camera = Play_GetCamera(globalCtx, this->camId);

        Play_CameraSetAtEye(globalCtx, 0, &camera->at, &camera->eye);
        this->camId = 0;
        ActorCutscene_Stop(this->actor.cutscene);
        if (this->actor.colChkInfo.health == 0) {
            func_800B724C(globalCtx, &this->actor, 6);
        }
    }
}

void func_8089AC70(EnDinofos* this) {
    this->unk_28A = 10;
    this->unk_2B4 = 0.55f;
    this->colliderJntSph.base.colType = COLTYPE_HIT3;
    this->unk_2B8 = 0.82500005f;
    this->unk_2B0 = 1.0f;
    this->unk_290 = 80;
    this->actor.flags &= ~0x400;
    func_800BCB70(&this->actor, 0x4000, 255, 0, 80);
}

void func_8089ACEC(EnDinofos* this, GlobalContext* globalCtx) {
    if (this->unk_28A == 10) {
        this->unk_28A = 0;
        this->colliderJntSph.base.colType = COLTYPE_HIT0;
        this->unk_2B0 = 0.0f;
        func_800BF7CC(globalCtx, &this->actor, this->unk_2D4, 12, 2, 0.3f, 0.2f);
        this->actor.flags |= 0x400;
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
    Player* player = PLAYER;
    s16 temp_v1;
    s16 temp_v1_2;
    Actor* temp_v0;
    s32 i;

    temp_v0 = func_800BC270(globalCtx, &this->actor, 80.0f, 0x138B0);
    if (temp_v0 != NULL) {
        temp_v1 = (Actor_YawBetweenActors(&this->actor, temp_v0) - this->actor.shape.rot.y) - this->unk_28E;
        if (ABS_ALT(temp_v1) < 0x3000) {
            func_8089D11C(this, temp_v1 + this->unk_28E);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_WARAU);
            return true;
        }
    }

    temp_v0 = func_800BC444(globalCtx, &this->actor, 80.0f);
    if ((temp_v0 != NULL) && (temp_v0->id == ACTOR_EN_BOM_CHU)) {
        temp_v1_2 = (Actor_YawBetweenActors(&this->actor, temp_v0) - this->actor.shape.rot.y) - this->unk_28E;
        if (ABS_ALT(temp_v1_2) < 0x3000) {
            func_8089C024(this, 1);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_WARAU);
            return true;
        }
    }

    if (globalCtx->actorCtx.unk2 != 0) {
        func_8089C024(this, 1);
        return true;
    }

    if ((this->actor.xzDistToPlayer < 100.0f) && (player->swordState != 0) && this->actor.isTargeted &&
        (Rand_ZeroOne() < 0.5f) && func_8089A968(this) && Actor_IsLinkFacingActor(&this->actor, 0x2000, globalCtx)) {
        if (Rand_ZeroOne() < 0.5f) {
            func_8089C024(this, 2);
        } else {
            func_8089C024(this, 3);
        }
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_WARAU);
        return true;
    }

    if ((gSaveContext.playerForm == PLAYER_FORM_GORON) && (player->actor.velocity.y < -5.0f) &&
        (player->unk_AE7 == 1) && (this->unk_28B == 0)) {
        this->unk_28B = 1;
        for (i = 0; i < ARRAY_COUNT(this->colliderJntSphElement) - 3; i++) {
            this->colliderJntSph.elements[i].info.bumper.dmgFlags &= ~0x400;
        }
    }

    return false;
}

void func_8089B100(EnDinofos* this, GlobalContext* globalCtx) {
    Camera* camera = Play_GetCamera(globalCtx, this->camId);
    Player* player = PLAYER;
    Vec3f sp3C;

    SkelAnime_ChangeAnim(&this->skelAnime, &D_06001CCC, 1.0f, SkelAnime_GetFrameCount(&D_06001CCC.common),
                         SkelAnime_GetFrameCount(&D_06001CCC.common), 2, 0.0f);
    func_800BE33C(&camera->eye, &camera->at, &this->unk_29A, 1);
    Math_Vec3f_Diff(&this->actor.world.pos, &player->actor.world.pos, &sp3C);
    this->unk_2BC.x = player->actor.world.pos.x + (0.4f * sp3C.x);
    this->unk_2BC.y = player->actor.world.pos.y + 5.0f;
    this->unk_2BC.z = player->actor.world.pos.z + (0.4f * sp3C.z);
    this->unk_2C8.x = this->actor.world.pos.x;
    this->unk_2C8.y = this->actor.focus.pos.y - 400.0f;
    this->unk_2C8.z = this->actor.world.pos.z;
    this->unk_2AC = Math_Vec3f_DistXYZ(&camera->eye, &this->unk_2BC) * 0.05f;
    this->unk_2A8 = Math_Vec3f_DistXYZ(&camera->at, &this->unk_2C8) * 0.05f;
    this->unk_290 = 20;
    this->actionFunc = func_8089B288;
}

void func_8089B288(EnDinofos* this, GlobalContext* globalCtx) {
    Camera* camera = Play_GetCamera(globalCtx, this->camId);

    this->unk_290--;
    Math_Vec3f_StepTo(&camera->eye, &this->unk_2BC, this->unk_2AC);
    Math_Vec3f_StepTo(&camera->at, &this->unk_2C8, this->unk_2A8);
    Play_CameraSetAtEye(globalCtx, this->camId, &camera->at, &camera->eye);
    if (this->unk_290 == 0) {
        func_8089B320(this);
    }
}

void func_8089B320(EnDinofos* this) {
    this->actor.gravity = -2.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_CRY);
    this->unk_2BC.x = (Math_SinS(this->actor.shape.rot.y - 0x0E00) * 86.0f) + this->actor.world.pos.x;
    this->unk_2BC.y = this->actor.floorHeight + 6.0f;
    this->unk_2BC.z = (Math_CosS(this->actor.shape.rot.y - 0x0E00) * 86.0f) + this->actor.world.pos.z;
    this->unk_290 = 0;
    this->actionFunc = func_8089B3D4;
}

void func_8089B3D4(EnDinofos* this, GlobalContext* globalCtx) {
    Camera* camera = Play_GetCamera(globalCtx, this->camId);
    Vec3f sp28;

    Math_Vec3f_StepTo(&camera->eye, &this->unk_2BC, 10.0f);
    this->unk_290++;
    if (this->unk_290 == 10) {
        func_801A2E54(0x38);
    }

    sp28.x = this->actor.world.pos.x;
    sp28.z = this->actor.world.pos.z;
    if (this->actor.focus.pos.y <= camera->at.y) {
        sp28.y = this->actor.focus.pos.y;
    } else {
        sp28.y = camera->at.y;
    }

    Play_CameraSetAtEye(globalCtx, this->camId, &sp28, &camera->eye);
    if (this->actor.bgCheckFlags & 1) {
        func_8089B4A4(this);
    }
}

void func_8089B4A4(EnDinofos* this) {
    if (this->unk_290 < 10) {
        func_801A2E54(0x38);
    }
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_0600C974);
    this->unk_2BC.x = (Math_SinS(this->actor.shape.rot.y + 0x200) * 123.0f) + this->actor.world.pos.x;
    this->unk_2BC.y = this->actor.floorHeight + 11.0f;
    this->unk_2BC.z = (Math_CosS(this->actor.shape.rot.y + 0x200) * 123.0f) + this->actor.world.pos.z;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BOMCHU_WALK);
    this->unk_290 = 0;
    this->unk_292 = -1;
    this->actionFunc = func_8089B580;
}

void func_8089B580(EnDinofos* this, GlobalContext* globalCtx) {
    Camera* camera = Play_GetCamera(globalCtx, this->camId);

    this->unk_290++;
    if (this->unk_290 < 8) {
        Play_CameraSetAtEye(globalCtx, this->camId, &this->actor.focus.pos, &camera->eye);
    }

    if (this->skelAnime.animCurrentFrame > 35.0f) {
        if ((globalCtx->sceneNum == SCENE_MITURIN) && func_801378B8(&this->skelAnime, 38.0f)) {
            globalCtx->envCtx.unk_C3 = 11;
        }

        Math_Vec3f_StepTo(&camera->eye, &this->unk_2BC, 10.0f);
        Play_CameraSetAtEye(globalCtx, this->camId, &this->actor.focus.pos, &camera->eye);
        if (this->skelAnime.animCurrentFrame <= 55.0f) {
            func_800B9010(&this->actor, NA_SE_EN_DODO_J_FIRE - SFX_FLAG);
        }
    }

    if ((globalCtx->sceneNum == SCENE_MITURIN) && func_801378B8(&this->skelAnime, 55.0f)) {
        globalCtx->envCtx.unk_C3 = 0xFF;
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        func_8089B6E8(this);
    }
}

void func_8089B6E8(EnDinofos* this) {
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06009B70, -3.0f);
    this->actionFunc = func_8089B72C;
}

void func_8089B72C(EnDinofos* this, GlobalContext* globalCtx) {
    if (func_801378B8(&this->skelAnime, 2.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_ATTACK);
    }

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        func_8089ABF4(this, globalCtx);
        this->actor.flags &= ~0x00100000;
        this->actor.cutscene = -1;
        func_8089B7B0(this);
    }
}

void func_8089B7B0(EnDinofos* this) {
    SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06002E40, -4.0f);
    this->unk_290 = (s32)Rand_ZeroFloat(20.0f) + 40;
    this->unk_292 = 30;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    func_8089AD70(this);
    this->actionFunc = func_8089B834;
}

void func_8089B834(EnDinofos* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
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
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000580, -4.0f);
        if (func_800BC5EC(globalCtx, &this->actor)) {
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

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (!func_8089AE00(this, globalCtx)) {
        if (func_800BC5EC(globalCtx, &this->actor)) {
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

        if (func_801378B8(&this->skelAnime, 0.0f) || func_801378B8(&this->skelAnime, 6.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_WALK);
        }
    }
}

void func_8089BAC0(EnDinofos* this) {
    if (this->actionFunc != func_8089BB60) {
        SkelAnime_ChangeAnimTransitionRepeat(&this->skelAnime, &D_06000580, -4.0f);
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
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->unk_28C, 0x400)) {
        func_8089A9B0(this, globalCtx);
    }
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void func_8089BBB4(EnDinofos* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

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
            this->skelAnime.animPlaybackSpeed = this->actor.speedXZ * 0.166666671634f;
        } else {
            SkelAnime_ChangeAnim(&this->skelAnime, &D_0600D62C, this->actor.speedXZ * 0.166666671634f, 0.0f, 0.0f, 0,
                                 -4.0f);
        }

        this->actor.world.rot.y = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
        this->unk_2A4 = 0;
        this->unk_292 = (s32)Rand_ZeroFloat(10.0f) + 5;
    }

    this->actionFunc = func_8089BD28;
}

void func_8089BD28(EnDinofos* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
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
            this->skelAnime.animPlaybackSpeed = 1.0f;
        } else {
            this->skelAnime.animPlaybackSpeed = -1.0f;
        }

        this->actor.world.rot.y = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
        if (func_800BC5EC(globalCtx, &this->actor)) {
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
        SkelAnime_FrameUpdateMatrix(&this->skelAnime);
        if (this->unk_292 != 0) {
            this->unk_292--;
        } else {
            func_8089A9B0(this, globalCtx);
        }

        if (func_801378B8(&this->skelAnime, 0.0f) || func_801378B8(&this->skelAnime, 5.0f)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_WALK);
        }
    }
}

void func_8089C024(EnDinofos* this, s32 arg1) {
    if (arg1 == 0) {
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06001CCC, 2.0f);
        func_8089AD70(this);
    } else {
        SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06001CCC, -1.0f);
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
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (func_801378B8(&this->skelAnime, 1.0f)) {
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
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_JUMP);
    this->actionFunc = func_8089C1F8;
}

void func_8089C1F8(EnDinofos* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->actor.bgCheckFlags & 1) {
        func_8089C398(this);
    }
}

void func_8089C244(EnDinofos* this) {
    this->actor.bgCheckFlags &= ~1;
    this->actor.speedXZ = 8.0f;
    this->actor.velocity.y = 16.0f;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_JUMP);
    this->unk_290 = 0;
    this->unk_292 = -1;
    this->actionFunc = func_8089C2A8;
}

void func_8089C2A8(EnDinofos* this, GlobalContext* globalCtx) {
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    this->unk_290++;
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x1800);
    if ((this->actor.velocity.y < 0.0f) && (this->skelAnime.animCurrentSeg == &D_06001CCC)) {
        this->colliderQuad.base.atFlags |= AT_ON;
        this->colliderJntSph.base.acFlags |= AC_ON;
        SkelAnime_ChangeAnim(&this->skelAnime, &D_060025B4, 1.0f, 7.0f, 13.0f, 2, -2.0f);
    }

    if (this->actor.bgCheckFlags & 1) {
        this->colliderQuad.base.atFlags &= ~AT_ON;
        func_8089C398(this);
    }
}

void func_8089C398(EnDinofos* this) {
    if (this->actionFunc != func_8089C2A8) {
        SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_06000AF0);
    } else {
        this->skelAnime.animFrameCount = SkelAnime_GetFrameCount(&D_060025B4.common);
    }

    if (this->actor.speedXZ < 0.0f) {
        this->unk_290 = 1;
    } else {
        this->unk_290 = 0;
    }

    this->actor.speedXZ = 0.0f;
    func_8089AD70(this);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_BOMCHU_WALK);
    this->actionFunc = func_8089C44C;
}

void func_8089C44C(EnDinofos* this, GlobalContext* globalCtx) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        if ((this->unk_290 == 1) && (this->actor.xzDistToPlayer < 280.0f) && func_8089A968(this) &&
            (Rand_ZeroOne() < 0.6f)) {
            func_8089CA14(this);
        } else {
            func_8089A9B0(this, globalCtx);
        }
    }
}

void func_8089C4F8(EnDinofos* this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_060025B4);
    this->colliderQuad.base.atFlags &= ~AT_BOUNCED;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_CRY);
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
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        func_800A8514(Effect_GetParams(this->unk_2A0));
        this->colliderQuad.base.atFlags &= ~AT_ON;
        func_8089A9B0(this, globalCtx);
    } else if (func_801378B8(&this->skelAnime, 7.0f)) {
        this->colliderQuad.base.atFlags |= AT_ON;
        func_8089AD70(this);
    } else if (func_801378B8(&this->skelAnime, 13.0f)) {
        this->colliderQuad.base.atFlags &= ~AT_ON;
    } else if (func_801378B8(&this->skelAnime, 11.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_ATTACK);
    } else if (this->skelAnime.animCurrentFrame < 7.0f) {
        func_8089AE00(this, globalCtx);
    }
}

void func_8089C690(EnDinofos* this) {
    SkelAnime_ChangeAnim(&this->skelAnime, &D_060025B4, -1.0f, this->skelAnime.animCurrentFrame, 0.0f, 2, 0.0f);
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

    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
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
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_0600D21C);
    func_800BE5CC(&this->actor, &this->colliderJntSph, arg1);
    this->actor.shape.rot.y = BINANG_ROT180(this->actor.world.rot.y);
    this->actor.speedXZ = 10.0f;
    if (this->actor.velocity.y > 0.0f) {
        this->actor.velocity.y = 0.0f;
    }
    this->unk_28E = 0;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_DAMAGE);
    this->colliderJntSph.base.acFlags &= ~AC_ON;
    func_800BCB70(&this->actor, 0x4000, 255, 0, 18);
    this->actionFunc = func_8089C938;
}

void func_8089C938(EnDinofos* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime) && (this->actor.bgCheckFlags & 1)) {
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
    SkelAnime_ChangeAnimTransitionStop(&this->skelAnime, &D_06001040, -5.0f);
    this->colliderJntSph.base.acFlags |= AC_ON;
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_8089CA74;
}

void func_8089CA74(EnDinofos* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x800);
    Math_StepToF(&this->actor.speedXZ, 0.0f, 0.5f);
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        func_8089CB10(this, globalCtx);
    } else if (!func_8089AE00(this, globalCtx) && func_801378B8(&this->skelAnime, 12.0f)) {
        this->actor.speedXZ = 8.0f;
    }
}

void func_8089CB10(EnDinofos* this, GlobalContext* globalCtx) {
    s32 i;
    Sphere16* worldSphere;

    SkelAnime_ChangeAnimDefaultRepeat(&this->skelAnime, &D_060013C0);
    this->unk_290 = 20;
    this->actor.speedXZ = 0.0f;
    this->colliderJntSph.base.atFlags |= AT_ON;
    func_8089AD70(this);

    for (i = 6; i < ARRAY_COUNT(this->colliderJntSphElement); i++) {
        worldSphere = &this->colliderJntSph.elements[i].dim.worldSphere;
        worldSphere->center.x = this->unk_34C.x;
        worldSphere->center.y = this->unk_34C.y;
        worldSphere->center.z = this->unk_34C.z;
    }

    if (globalCtx->sceneNum == SCENE_MITURIN) {
        globalCtx->envCtx.unk_C3 = 11;
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

    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
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
    EffectSsDFire_Spawn(globalCtx, &this->unk_34C, &sp88, &sp7C, 30, 22, 255 - (temp_s0 * 20), 20, 3, 8);

    for (end = 6, i = 3; i > 0; i--) {
        if (this->unk_290 < (20 + -(i * 2))) {
            end = i + 6;
            break;
        }
    }

    for (i = 6; i < end; i++) {
        dim = &this->colliderJntSph.elements[i].dim;
        temp_s3 = (s32)(cos_rad((this->unk_290 + ((i - 5) << 1)) * (M_PI / 20)) * 0x2C00) + this->actor.shape.rot.y;

        dim->worldSphere.center.x = (s32)(Math_SinS(temp_s3) * dim->modelSphere.center.z) + (s32)this->unk_34C.x;
        dim->worldSphere.center.y = (s32)this->unk_34C.y + (s32)dim->modelSphere.center.y;
        dim->worldSphere.center.z = (s32)(Math_CosS(temp_s3) * dim->modelSphere.center.z) + (s32)this->unk_34C.z;
    }

    if (this->unk_290 != 0) {
        this->unk_290--;
    } else {
        func_8089CF00(this, globalCtx);
    }
}

void func_8089CF00(EnDinofos* this, GlobalContext* globalCtx) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_060017B8);
    this->colliderJntSph.base.atFlags &= ~AT_ON;
    if (globalCtx->sceneNum == SCENE_MITURIN) {
        globalCtx->envCtx.unk_C3 = 255;
    }
    this->actionFunc = func_8089CF70;
}

void func_8089CF70(EnDinofos* this, GlobalContext* globalCtx) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
        func_8089A9B0(this, globalCtx);
    }
}

void func_8089CFAC(EnDinofos* this) {
    SkelAnime_ChangeAnimDefaultStop(&this->skelAnime, &D_0600ABD0);
    this->actor.flags &= ~1;
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_DEAD);
    this->actor.speedXZ = 0.0f;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc = func_8089D018;
}

void func_8089D018(EnDinofos* this, GlobalContext* globalCtx) {
    if (SkelAnime_FrameUpdateMatrix(&this->skelAnime)) {
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

        if (this->unk_2B0 > 0.0f) {
            this->unk_2B0 = this->unk_288 * (1.0f / 255.0f);
        }

        this->actor.shape.shadowAlpha = this->unk_288;
    } else if (func_801378B8(&this->skelAnime, 26.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_GERUDOFT_DOWN);
    }
}

void func_8089D11C(EnDinofos* this, s16 arg1) {
    if (arg1 >= 0) {
        this->actor.speedXZ = -15.0f;
    } else {
        this->actor.speedXZ = 15.0f;
    }
    SkelAnime_ChangeAnim(&this->skelAnime, &D_0600D62C, this->actor.speedXZ * (1.0f / 7.5f), 0.0f, 0.0f, 0, -4.0f);
    this->actor.world.rot.y = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
    this->unk_292 = 10;
    this->unk_2A4 = 0.0f;
    func_8089AD70(this);
    this->actionFunc = func_8089D1E0;
}

void func_8089D1E0(EnDinofos* this, GlobalContext* globalCtx) {
    Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0xBB8);
    Math_StepToF(&this->actor.speedXZ, 0.0f, 2.0f);

    this->skelAnime.animPlaybackSpeed =
        (1.0f + fabsf(this->actor.speedXZ * (1.0f / 15.0f))) * ((this->actor.speedXZ >= 0.0f) ? 1.0f : -1.0f);
    this->actor.world.rot.y = BINANG_ADD(this->actor.shape.rot.y, 0x4000);
    SkelAnime_FrameUpdateMatrix(&this->skelAnime);
    if (this->unk_292 != 0) {
        this->unk_292--;
    } else {
        func_8089A9B0(this, globalCtx);
    }

    if (func_801378B8(&this->skelAnime, 0.0f) || func_801378B8(&this->skelAnime, 5.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_RIZA_WALK);
    }
}

void func_8089D2E0(EnDinofos* this) {
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    this->actionFunc = func_8089D318;
}

void func_8089D318(EnDinofos* this, GlobalContext* globalCtx) {
    Vec3f sp24;

    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        if (this->actor.colChkInfo.health == 0) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
            func_800B724C(globalCtx, &this->actor, 7);
        } else {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        }
        this->camId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
        if (this->actor.colChkInfo.health == 0) {
            sp24.x = (Math_SinS(this->actor.shape.rot.y) * 150.0f) + this->actor.focus.pos.x;
            sp24.y = this->actor.focus.pos.y;
            sp24.z = (Math_CosS(this->actor.shape.rot.y) * 150.0f) + this->actor.focus.pos.z;
            Play_CameraSetAtEye(globalCtx, this->camId, &this->actor.focus.pos, &sp24);
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
    } else if (!func_801690CC(globalCtx)) {
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
        func_800BE2B8(&this->actor, &this->colliderJntSph);

        for (i = 0; i < ARRAY_COUNT(this->colliderJntSphElement); i++) {
            if (this->colliderJntSph.elements[i].info.bumperFlags & BUMP_HIT) {
                break;
            }
        }

        if (i == ARRAY_COUNT(this->colliderJntSphElement)) {
            return false;
        }

        if ((this->unk_28A == 10) && (this->colliderJntSph.elements[i].info.acHitInfo->toucher.dmgFlags & 0xDB0B3)) {
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
            globalCtx->envCtx.unk_C3 = 255;
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
            func_800BCB70(&this->actor, 0, 255, 0, 40);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_COMMON_FREEZE);
            func_8089C784(this);
            return true;
        }

        if (this->actor.colChkInfo.damageEffect == 5) {
            this->unk_290 = 40;
            func_800BCB70(&this->actor, 0, 255, 0, 40);
            this->unk_2B4 = 0.55f;
            this->unk_2B0 = 2.0f;
            this->unk_28A = 31;
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_COMMON_FREEZE);
            func_8089C784(this);
            return true;
        }

        if (this->actor.colChkInfo.damageEffect == 2) {
            this->unk_2B0 = 4.0f;
            this->unk_2B4 = 0.55f;
            this->unk_28A = 0;
        } else if (this->actor.colChkInfo.damageEffect == 4) {
            this->unk_2B0 = 4.0f;
            this->unk_2B4 = 0.55f;
            this->unk_28A = 20;
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
    EnDinofos* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s32 pad;
    Vec3f sp30;

    if (this->actionFunc != func_8089C7B8) {
        func_8089A900(this);
    }

    if (!func_8089D60C(this, globalCtx) && (this->colliderQuad.base.atFlags & AT_BOUNCED)) {
        func_8089C690(this);
    }

    this->actionFunc(this, globalCtx);
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 25.0f, 30.0f, 60.0f, 0x5D);
    if (this->actionFunc != func_8089C7B8) {
        if ((this->actor.yDirDistToWaterSurface > 0.0f) && (this->actor.yDirDistToWaterSurface < 10.0f)) {
            if (!((globalCtx->gameplayFrames % 4) & 1)) {
                Math_Vec3f_Copy(&sp30, &this->unk_2D4[1 + (globalCtx->gameplayFrames % 4)]);
                sp30.y = this->actor.world.pos.y + this->actor.yDirDistToWaterSurface;
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

    Math_Vec3f_Copy(&this->actor.focus.pos, &this->unk_304);
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

    if (this->unk_2B0 > 0.0f) {
        if (this->unk_28A != 10) {
            Math_StepToF(&this->unk_2B0, 0.0f, 0.05f);
            this->unk_2B4 = (this->unk_2B0 + 1.0f) * (11.0f / 40.0f);
            this->unk_2B4 = CLAMP_MAX(this->unk_2B4, 0.55f);
        } else if (!Math_StepToF(&this->unk_2B8, 0.55f, 0.01375f)) {
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
        SysMatrix_GetStateTranslation(&this->unk_2D4[D_8089E3B0[limbIndex]]);
    }

    if ((limbIndex == 14) && (this->unk_292 != this->unk_290) &&
        ((this->actionFunc == func_8089C56C) || (this->actionFunc == func_8089C2A8))) {
        Math_Vec3f_Copy(&sp74, &this->colliderQuad.dim.quad[0]);
        Math_Vec3f_Copy(&sp80, &this->colliderQuad.dim.quad[1]);
        SysMatrix_MultiplyVector3fByState(&D_8089E38C, &sp68);
        SysMatrix_MultiplyVector3fByState(&D_8089E398, &sp5C);
        Collider_SetQuadVertices(&this->colliderQuad, &sp5C, &sp68, &sp74, &sp80);
        if (this->colliderQuad.base.atFlags & AT_ON) {
            func_800A81F0(Effect_GetParams(this->unk_2A0), &sp68, &sp5C);
        }
        this->unk_292 = this->unk_290;
    }

    if (limbIndex == 4) {
        SysMatrix_GetStateTranslationAndScaledX(300.0f, &this->actor.shape.feetPos[0]);
    } else if (limbIndex == 7) {
        SysMatrix_GetStateTranslationAndScaledX(300.0f, &this->actor.shape.feetPos[1]);
    }

    if ((limbIndex == 16) && (this->actionFunc == func_8089B580)) {
        if ((this->skelAnime.animCurrentFrame > 38.0f) && (this->skelAnime.animCurrentFrame <= 55.0f) &&
            (this->unk_292 != this->unk_290)) {
            sp48 = SysMatrix_GetCurrentState();
            sp58 = 48 - (s32)this->skelAnime.animCurrentFrame;
            sp58 = CLAMP_MIN(sp58, 0);
            SysMatrix_MultiplyVector3fByState(&D_8089E3A4, &sp4C);
            sp4C.x -= sp48->mf[3][0];
            sp4C.y -= sp48->mf[3][1];
            sp4C.z -= sp48->mf[3][2];
            EffectSsDFire_Spawn(globalCtx, &this->unk_34C, &sp4C, &D_801D15B0, 30, 22, 255 - (sp58 * 20), 20, 3, 8);
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
            SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                              this->skelAnime.dListCount, func_8089DC4C, func_8089DC84, &this->actor, POLY_OPA_DISP);
    } else {
        func_8012C2DC(globalCtx->state.gfxCtx);
        func_800B8118(&this->actor, globalCtx, 0);

        gSPSegment(POLY_XLU_DISP++, 0x08, D_8089E33C[this->unk_289]);
        gDPSetEnvColor(POLY_XLU_DISP++, 20, 40, 40, this->unk_288);

        Scene_SetRenderModeXlu(globalCtx, 1, 2);
        POLY_XLU_DISP =
            SkelAnime_DrawSV2(globalCtx, this->skelAnime.skeleton, this->skelAnime.limbDrawTbl,
                              this->skelAnime.dListCount, func_8089DC4C, func_8089DC84, &this->actor, POLY_XLU_DISP);
    }

    func_800BE680(globalCtx, &this->actor, this->unk_2D4, 12, this->unk_2B4, this->unk_2B8, this->unk_2B0,
                  this->unk_28A);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
