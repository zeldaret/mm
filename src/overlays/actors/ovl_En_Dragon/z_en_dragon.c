/*
 * File: z_en_dragon.c
 * Overlay: ovl_En_Dragon
 * Description: Deep Python
 */

#include "z_en_dragon.h"
#include "objects/object_utubo/object_utubo.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnDragon*)thisx)

void EnDragon_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDragon_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDragon_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDragon_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B5EDF0(EnDragon* this);
void func_80B5EE3C(EnDragon* this, GlobalContext* globalCtx);
void func_80B5EF88(EnDragon* this);
void func_80B5EFD0(EnDragon* this, GlobalContext* globalCtx);
void func_80B5F508(EnDragon* this, GlobalContext* globalCtx);
void func_80B5F888(EnDragon* this);
void func_80B5F8D8(EnDragon* this, GlobalContext* globalCtx);
void func_80B5FD68(EnDragon* this, GlobalContext* globalCtx);

static s32 D_80B605D0 = 0;

const ActorInit En_Dragon_InitVars = {
    ACTOR_EN_DRAGON,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_UTUBO,
    sizeof(EnDragon),
    (ActorFunc)EnDragon_Init,
    (ActorFunc)EnDragon_Destroy,
    (ActorFunc)EnDragon_Update,
    (ActorFunc)EnDragon_Draw,
};

// static DamageTable sDamageTable = {
static DamageTable D_80B605F4 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// static ColliderJntSphElementInit sJntSphElementsInit[8] = {
static ColliderJntSphElementInit D_80B60614[8] = {
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 13, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 12, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 12, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 10, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 10, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 9, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 9, { { 0, 0, 0 }, 0 }, 1 },
    },
    {
        {
            ELEMTYPE_UNK1,
            { 0xF7CFFFFF, 0x00, 0x00 },
            { 0xF7CFFFFF, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 9, { { 0, 0, 0 }, 0 }, 1 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80B60734 = {
    {
        COLTYPE_HIT6,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    8,
    D_80B60614, // sJntSphElementsInit,
};

static AnimationHeader* D_80B60744[] = {
    &object_utubo_Anim_0048B8,
    &object_utubo_Anim_004ABC,
    &object_utubo_Anim_004740,
    &object_utubo_Anim_0048B8,
};

static u8 D_80B60754[] = { ANIMMODE_LOOP, ANIMMODE_LOOP, ANIMMODE_ONCE, ANIMMODE_ONCE };

static Color_RGBA8 D_80B60758[] = {
    { 255, 255, 255, 255 },
    { 150, 255, 255, 255 },
    { 100, 255, 255, 255 },
};

static Color_RGBA8 D_80B60764[] = {
    { 150, 150, 150, 0 },
    { 0, 100, 0, 255 },
    { 0, 0, 255, 255 },
};

void EnDragon_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDragon* this = THIS;

    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_utubo_Skel_004398, &object_utubo_Anim_0048B8,
                       this->jointTable, this->morphTable, 0x10);
    this->actor.colChkInfo.health = 4;
    this->actor.colChkInfo.damageTable = &D_80B605F4;
    this->actor.targetMode = 0xA;
    Collider_InitAndSetJntSph(globalCtx, &this->unk_2DC, &this->actor, &D_80B60734, this->unk_2FC);

    this->unk_2DC.elements[0].dim.scale = this->unk_2DC.elements[1].dim.scale = this->unk_2DC.elements[2].dim.scale =
        this->unk_2DC.elements[3].dim.scale = this->unk_2DC.elements[4].dim.scale =
            this->unk_2DC.elements[5].dim.scale = this->unk_2DC.elements[6].dim.scale =
                this->unk_2DC.elements[7].dim.scale = 1.0f;
    this->unk_2DC.elements[0].dim.modelSphere.radius = 150;
    this->unk_2DC.elements[0].dim.modelSphere.center.x = 420;
    this->unk_2DC.elements[1].dim.modelSphere.radius = 160;
    this->unk_2DC.elements[1].dim.modelSphere.center.x = 630;
    this->unk_2DC.elements[2].dim.modelSphere.radius = 130;
    this->unk_2DC.elements[2].dim.modelSphere.center.x = 630;
    this->unk_2DC.elements[3].dim.modelSphere.radius = 170;
    this->unk_2DC.elements[3].dim.modelSphere.center.x = 920;
    this->unk_2DC.elements[4].dim.modelSphere.radius = 150;
    this->unk_2DC.elements[4].dim.modelSphere.center.x = 530;
    this->unk_2DC.elements[5].dim.modelSphere.radius = 140;
    this->unk_2DC.elements[5].dim.modelSphere.center.x = 730;
    this->unk_2DC.elements[6].dim.modelSphere.radius = 120;
    this->unk_2DC.elements[6].dim.modelSphere.center.x = 430;
    this->unk_2DC.elements[7].dim.modelSphere.radius = 110;
    this->unk_2DC.elements[7].dim.modelSphere.center.x = 160;
    this->unk_250 = (this->actor.params >> 7) & 0x1F;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_2BA = 0;
    this->actor.hintId = 0xE;
    this->unk_2D4 = 0.5f;
    this->actor.flags &= ~ACTOR_FLAG_8000000;
    func_80B5EDF0(this);
}

void EnDragon_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDragon* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->unk_2DC);
}

void func_80B5EAA0(EnDragon* this, s32 arg1) {
    f32 phi_f0;

    this->unk_24C = arg1;
    this->unk_2D0 = Animation_GetLastFrame(D_80B60744[arg1]);
    phi_f0 = 0.0f;
    if (this->unk_24C == 3) {
        phi_f0 = this->unk_2D0;
    }

    Animation_Change(&this->skelAnime, D_80B60744[arg1], 1.0f, phi_f0, this->unk_2D0, D_80B60754[this->unk_24C], -4.0f);
}

void func_80B5EB40(EnDragon* this, GlobalContext* globalCtx, Vec3f arg2) {
    static Vec3f D_80B60770 = { 0.0f, 0.0f, 0.0f };
    static Vec3f D_80B6077C = { 0.0f, 0.1f, 0.0f };
    s32 phi_v0;
    s16 phi_s1;
    s16 temp;
    Vec3f sp9C;
    s32 i;

    phi_v0 = (s32)randPlusMinusPoint5Scaled(5.0f) + 10;
    phi_s1 = 0;
    if (this->unk_2BA == 6) {
        phi_s1 = 1;
        phi_v0 = (s32)randPlusMinusPoint5Scaled(5.0f) + 10;
    }

    for (i = 0; i < phi_v0; i++) {
        Math_Vec3f_Copy(&sp9C, &arg2);
        D_80B60770.x = Rand_ZeroFloat(1.0f) * 23.0f;
        D_80B60770.y = Rand_ZeroFloat(1.0f) * 10.0f;
        D_80B60770.z = Rand_ZeroFloat(1.0f) * 23.0f;
        sp9C.x += randPlusMinusPoint5Scaled(i * 30.0f);
        sp9C.y += randPlusMinusPoint5Scaled(5.0f);
        sp9C.z += randPlusMinusPoint5Scaled(i * 30.0f);
        D_80B6077C.y = Rand_ZeroFloat(1.0f) * 20.0f * 3.0f;
        temp = Rand_S16Offset(380, 240);
        EffectSsDtBubble_SpawnCustomColor(globalCtx, &sp9C, &D_80B60770, &D_80B6077C, &D_80B60758[phi_s1],
                                          &D_80B60764[phi_s1], temp, 30, 0);
    }
}

void func_80B5ED90(EnDragon* this, GlobalContext* globalCtx) {
    if (this->unk_2B4 == 0) {
        func_800B8D50(globalCtx, &this->actor, 10.0f, this->actor.world.rot.y, 10.0f, 8);
        func_80B5EDF0(this);
    }
}

void func_80B5EDF0(EnDragon* this) {
    func_80B5EAA0(this, 3);
    this->unk_2BE = 0;
    this->unk_2CC = 0;
    this->unk_2B8 = 0;
    this->unk_2CA = 0;
    this->unk_2B4 = 0x1E;
    this->actionFunc = func_80B5EE3C;
}

void func_80B5EE3C(EnDragon* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (this->unk_2BA == 1) {
        func_80B5EF88(this);
    } else if ((this->unk_2B4 != 0) && (fabsf(this->actor.world.pos.x - this->actor.home.pos.x) > 101.0f) &&
               (fabsf(this->actor.world.pos.z - this->actor.home.pos.z) > 101.0f)) {
        this->actor.speedXZ = -100.0f;
    } else {
        this->actor.speedXZ = 0.0f;

        if ((fabsf(this->actor.world.pos.x - this->actor.home.pos.x) > 4.0f) &&
            (fabsf(this->actor.world.pos.z - this->actor.home.pos.z) > 4.0f)) {
            Math_ApproachF(&this->actor.world.pos.x, this->actor.home.pos.x, 0.3f, 200.0f);
            Math_ApproachF(&this->actor.world.pos.z, this->actor.home.pos.z, 0.3f, 200.0f);
        } else if (this->unk_2BA != 0) {
            this->unk_2BA = 0;
        }
    }
}

void func_80B5EF88(EnDragon* this) {
    this->unk_2BE = 0;
    this->unk_2B0 = this->unk_2BE;
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_APPEAR_TRG);
    this->unk_2AE = 0xFA;
    this->actionFunc = func_80B5EFD0;
}

void func_80B5EFD0(EnDragon* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 currentFrame = this->skelAnime.curFrame;
    s16 phi_v1;

    func_80B5EB40(this, globalCtx, this->unk_254);

    if (this->unk_2BA >= 3) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_BACK);
        func_80B5EDF0(this);
    } else if (this->unk_2AE == 0) {
        this->unk_2BA = 4;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_BACK);
        func_80B5EDF0(this);
    } else if (this->unk_2BE == 0) {
        Vec3f sp38;

        Math_Vec3f_Copy(&sp38, &this->unk_260);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_APPEAR - SFX_FLAG);
        sp38.x += Math_SinS(this->actor.world.rot.y) * -530.0f;
        sp38.z += Math_CosS(this->actor.world.rot.y) * -530.0f;
        this->actor.speedXZ = 40.0f;
        Math_SmoothStepToS(&this->unk_2A8, 0xFA0, 5, 0xBB8, 0x14);

        if ((fabsf(this->actor.world.pos.x - sp38.x) < 51.0f) && (fabsf(this->actor.world.pos.z - sp38.z) < 51.0f)) {
            this->actor.speedXZ = 0.0f;
            Math_ApproachF(&this->actor.world.pos.x, sp38.x, 0.3f, 50.0f);
            Math_ApproachF(&this->actor.world.pos.z, sp38.z, 0.3f, 50.0f);
            if ((fabsf(this->actor.world.pos.x - sp38.x) < 4.0f) && (fabsf(this->actor.world.pos.z - sp38.z) < 4.0f)) {
                if (this->unk_24C != 1) {
                    func_80B5EAA0(this, 1);
                }

                this->unk_2BE = 1;
            }
        }
    } else {
        Math_SmoothStepToS(&this->unk_2A8, 0, 5, 0xBB8, 0x14);
        SkelAnime_Update(&this->skelAnime);
        if (this->unk_2BE == 1) {
            if (currentFrame < this->unk_2D0) {
                return;
            }
            this->unk_2BE = 2;
        }

        phi_v1 = ABS_ALT(BINANG_SUB(Math_Vec3f_Yaw(&this->unk_254, &player->actor.world.pos), this->actor.shape.rot.y));
        if (phi_v1 < 0x5000) {
            if ((this->unk_2D0 <= currentFrame) && (this->unk_2B2 == 0)) {
                if (this->unk_24C != 1) {
                    func_80B5EAA0(this, 1);
                }

                this->unk_2BE = 2;
            }

            this->unk_2B0 = 0;
        } else {
            if (this->unk_2BE == 2) {
                func_80B5EAA0(this, 0);
                this->unk_2B2 = Rand_ZeroFloat(20.0f) + this->unk_2D0;
                this->unk_2BE = 3;
            }

            this->unk_2B0++;
            if (this->unk_2B0 >= 0x3D) {
                this->unk_2BA = 4;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_BACK);
                func_80B5EDF0(this);
            }
        }
    }
}

void func_80B5F3A4(EnDragon* this, GlobalContext* globalCtx, Vec3f arg2, Vec3f arg3) {
    this->unk_2C8 = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
    Math_Vec3f_Copy(&this->unk_278, &arg2);
    Math_Vec3f_Copy(&this->unk_284, &arg3);
    Play_CameraSetAtEye(globalCtx, this->unk_2C8, &this->unk_284, &this->unk_278);
}

void func_80B5F418(EnDragon* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp28;
    s16 temp_v0;

    if (!ActorCutscene_GetCanPlayNext(this->unk_2C0)) {
        ActorCutscene_SetIntentToPlay(this->unk_2C0);
    } else {
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_2C0, &this->actor);
        Math_Vec3f_Copy(&sp28, &this->unk_260);
        sp28.x += Math_SinS(this->actor.world.rot.y) * -530.0f;
        sp28.z += Math_CosS(this->actor.world.rot.y) * -530.0f;
        Math_Vec3f_Copy(&this->actor.world.pos, &sp28);
        temp_v0 = Math_Vec3f_Yaw(&player->actor.world.pos, &this->unk_254);
        player->actor.shape.rot.y = temp_v0;
        player->actor.world.rot.y = temp_v0;
        this->unk_2BE = 0;
        this->unk_2CA = 0;
        this->unk_2B8 = 0;
        func_80B5EAA0(this, 3);
        this->actionFunc = func_80B5F508;
    }
}

static Vec3f D_80B60788[] = {
    { 1600.0f, 0.0f, 1400.0f }, { 1400.0f, 0.0f, 400.0f },  { 1800.0f, 0.0f, 1400.f },  { 1100.0f, -200.0f, 1500.0f },
    { 2000.0f, 0.0f, 1500.0f }, { 1900.0f, 0.0f, 1800.0f }, { 1700.0f, 0.0f, 1100.0f }, { 1700.0f, 0.0f, 1100.0f },
};

static Vec3f D_80B607E8[] = {
    { 300.0f, -100.0f, 1300.0f }, { 1500.0f, 0.0f, 2400.0f }, { 300.0f, -100.0f, 1300.0f }, { 1900.0f, 500.0f, 600.0f },
    { -1000.0f, 0.0f, 1000.0f },  { 1200.0f, 0.0f, 1500.0f }, { 1100.0f, 0.0f, 2000.0f },   { 1100.0f, 0.0f, 2000.0f },
};

static s16 D_80B60848[] = { 0x07D0, 0x07D0, 0x07D0, 0x07D0, 0x07D0, 0x0BB8, 0x0000, 0x0000 };

static s32 D_80B60858[] = { 5, 5, 5, 4, 5, 8, 5, 5 };

void func_80B5F508(EnDragon* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f sp50;
    Vec3f sp44;

    this->unk_2C8 = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
    SkelAnime_Update(&this->skelAnime);

    if (this->unk_2CA == 0) {
        if (this->unk_2B8 == 0) {
            Math_Vec3f_Copy(&player->actor.world.pos, &this->unk_26C);
            Math_Vec3f_Copy(&this->unk_290, &this->unk_26C);
            this->unk_2B8 = 1;
        } else {
            Math_Vec3f_Copy(&player->actor.world.pos, &this->unk_290);
        }

        Math_Vec3f_Copy(&sp50, &this->unk_260);
        sp50.x += Math_SinS(this->actor.world.rot.y) * -930.0f;
        sp50.z += Math_CosS(this->actor.world.rot.y) * -930.0f;
        Math_Vec3f_Copy(&this->actor.world.pos, &sp50);
        this->unk_2A8 = 0x1450;
        this->actor.speedXZ = 60.0f;
    }

    this->unk_2CA++;
    Math_SmoothStepToS(&this->actor.shape.rot.z, D_80B60848[this->unk_250], 0xA, 0x1F4, 0x14);
    func_80B5EB40(this, globalCtx, this->unk_254);

    Math_Vec3f_Copy(&sp50, &this->unk_260);
    sp50.x += Math_SinS(this->actor.world.rot.y) * D_80B60788[this->unk_250].x;
    sp50.y += D_80B60788[this->unk_250].y;
    sp50.z += Math_CosS(this->actor.world.rot.y) * D_80B60788[this->unk_250].z;

    Math_Vec3f_Copy(&sp44, &this->actor.world.pos);
    sp44.x += Math_SinS(this->actor.world.rot.y) * D_80B607E8[this->unk_250].x;
    sp44.y += D_80B607E8[this->unk_250].y;
    sp44.z += Math_CosS(this->actor.world.rot.y) * D_80B607E8[this->unk_250].z;

    func_80B5F3A4(this, globalCtx, sp50, sp44);

    if (D_80B60858[this->unk_250] < this->unk_2CA) {
        if (this->unk_2BE == 0) {
            func_800B7298(globalCtx, &this->actor, 6U);
            this->unk_2BE = 1;
        }

        globalCtx->unk_18770(globalCtx, player);
        player->actor.parent = &this->actor;
        player->unk_AE8 = 50;
        this->unk_2BA = 2;
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_EAT);
        func_80B5F888(this);
    }
}

void func_80B5F888(EnDragon* this) {
    if (this->unk_24C != 1) {
        func_80B5EAA0(this, 1);
    }

    this->unk_2B0 = 0;
    this->unk_2CA = 0;
    this->unk_2BE = 0;
    this->actionFunc = func_80B5F8D8;
}

void func_80B5F8D8(EnDragon* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 currentFrame = this->skelAnime.curFrame;
    Vec3f sp4C;
    Vec3f sp40;

    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->actor.shape.rot.z, 0, 0xA, 0x1388, 0);
    if (!(globalCtx->gameplayFrames & 0xF)) {
        globalCtx->damagePlayer(globalCtx, -2);

        //! @bug: This function should only pass Player*: it uses *(this + 0x153), which is meant to be
        //! player->currentMask, but in this case is garbage in the skelAnime
        func_800B8E58((Player*)this, player->ageProperties->unk_92 + NA_SE_VO_LI_DAMAGE_S);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_BITE);
        CollisionCheck_GreenBlood(globalCtx, NULL, &player->actor.world.pos);
    }

    Math_Vec3f_Copy(&sp4C, &this->actor.world.pos);
    sp4C.x += Math_SinS(this->actor.world.rot.y) * 3000.0f;
    sp4C.y += 600.0f;
    sp4C.z += Math_CosS(this->actor.world.rot.y) * 3000.0f;

    Math_Vec3f_Copy(&sp40, &this->actor.world.pos);
    sp40.x += Math_SinS(this->actor.world.rot.y) * 1200.0f;
    sp40.y += -100.0f;
    sp40.z += Math_CosS(this->actor.world.rot.y) * 1200.0f;

    func_80B5F3A4(this, globalCtx, sp4C, sp40);

    player->actor.world.rot.y = player->actor.shape.rot.y = this->actor.world.rot.y;
    player->actor.world.rot.x = player->actor.shape.rot.x = this->actor.world.rot.x;
    player->actor.world.rot.z = player->actor.shape.rot.z = this->actor.world.rot.z - 0x36B0;
    Math_Vec3f_Copy(&player->actor.world.pos, &this->unk_26C);
    this->unk_2A8 = 0xC8;

    Math_Vec3f_Copy(&sp4C, &this->unk_260);
    sp4C.x += Math_SinS(this->actor.world.rot.y) * -530.0f;
    sp4C.z += Math_CosS(this->actor.world.rot.y) * -530.0f;
    Math_ApproachF(&this->actor.world.pos.x, sp4C.x, 0.3f, 200.0f);
    Math_ApproachF(&this->actor.world.pos.y, sp4C.y, 0.3f, 200.0f);
    Math_ApproachF(&this->actor.world.pos.z, sp4C.z, 0.3f, 200.0f);

    if ((this->unk_2BE <= 0) && (this->unk_2D0 <= currentFrame)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_BITE);
        if (this->unk_24C != 1) {
            func_80B5EAA0(this, 1);
        }
        this->unk_2BE += 1;
    }

    if (((this->unk_2BE != 0) && (this->unk_2D0 <= currentFrame)) || (!(player->stateFlags2 & 0x80)) ||
        ((this->unk_2DC.elements[0].info.bumperFlags & BUMP_HIT)) ||
        (this->unk_2DC.elements[1].info.bumperFlags & BUMP_HIT) ||
        (this->unk_2DC.elements[2].info.bumperFlags & BUMP_HIT)) {
        player->actor.parent = NULL;
        this->unk_2B6 = 0x1E;
        ActorCutscene_Stop(this->unk_2C0);
        if ((player->stateFlags2 & 0x80) != 0) {
            player->unk_AE8 = 100;
        }

        this->actor.flags &= ~ACTOR_FLAG_100000;

        if ((this->unk_2BE != 0) && (this->unk_2D0 <= currentFrame)) {
            this->unk_2B4 = 3;
            this->actionFunc = func_80B5ED90;
        } else {
            func_80B5EDF0(this);
        }
    }
}

void func_80B5FCC0(EnDragon* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->unk_2C2) == 0) {
        ActorCutscene_SetIntentToPlay(this->unk_2C2);
    } else {
        ActorCutscene_StartAndSetUnkLinkFields(this->unk_2C2, &this->actor);
        this->unk_2D0 = Animation_GetLastFrame(&object_utubo_Anim_0048B8);
        Animation_Change(&this->skelAnime, &object_utubo_Anim_0048B8, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f);
        this->unk_2B4 = 0x14;
        this->actionFunc = func_80B5FD68;
    }
}

void func_80B5FD68(EnDragon* this, GlobalContext* globalCtx) {
    Vec3f sp54;

    SkelAnime_Update(&this->skelAnime);
    this->actor.shape.rot.z += 0x1000;
    this->unk_2A8 = 0xFA0;
    func_80B5EB40(this, globalCtx, this->unk_254);

    if ((this->unk_2B4 != 0) && (fabsf(this->actor.world.pos.x - this->actor.home.pos.x) > 121.0f) &&
        (fabsf(this->actor.world.pos.z - this->actor.home.pos.z) > 121.0f)) {
        this->actor.speedXZ = -120.0f;
        if (((this->unk_250 & 1) == 0) && (Rand_ZeroOne() < 0.5f)) {
            if (((!globalCtx->gameplayFrames) & 0x1F)) {
                Item_DropCollectibleRandom(globalCtx, NULL, &this->unk_254, 0x90);
            }
        }
        this->unk_2BA = 6;
        return;
    }

    this->actor.speedXZ = 0.0f;
    if ((fabsf(this->actor.world.pos.x - this->actor.home.pos.x) > 20.0f) &&
        (fabsf(this->actor.world.pos.z - this->actor.home.pos.z) > 20.0f)) {
        Math_ApproachF(&this->actor.world.pos.x, this->actor.home.pos.x, 0.3f, 300.0f);
        Math_ApproachF(&this->actor.world.pos.z, this->actor.home.pos.z, 0.3f, 300.0f);
        return;
    }

    D_80B605D0++;
    if (D_80B605D0 >= (gGameInfo->data[0x987] + 8)) {
        Math_Vec3f_Copy(&sp54, &this->actor.parent->world.pos);
        sp54.x += (Math_SinS((this->actor.parent->world.rot.y + 0x8000)) * (500.0f + gGameInfo->data[0x986]));
        sp54.y += -100.0f + gGameInfo->data[0x981];
        sp54.z += (Math_CosS((this->actor.parent->world.rot.y + 0x8000)) * (500.0f + gGameInfo->data[0x986]));
        if (Actor_SpawnAsChildAndCutscene(&globalCtx->actorCtx, globalCtx, 0x205, sp54.x, sp54.y, sp54.z, 0,
                                          this->actor.shape.rot.y, 0, 0x4000, this->actor.cutscene, this->actor.unk20,
                                          NULL)) {
            gSaveContext.weekEventReg[0xD] |= 1;
            switch (this->unk_250) {
                case 0:
                    gSaveContext.weekEventReg[0x53] |= 0x10;
                    break;

                case 1:
                    gSaveContext.weekEventReg[0x53] |= 0x20;
                    break;

                case 2:
                    gSaveContext.weekEventReg[0x53] |= 0x40;
                    break;

                case 3:
                    gSaveContext.weekEventReg[0x53] |= 0x80;
                    break;
                case 4:
                    gSaveContext.weekEventReg[0x54] |= 1;
                    break;

                case 5:
                    gSaveContext.weekEventReg[0x54] |= 2;
                    break;

                case 6:
                    gSaveContext.weekEventReg[0x54] |= 4;
                    break;

                case 7:
                    gSaveContext.weekEventReg[0x54] |= 8;
                    break;
            }
        }
    }

    Actor_MarkForDeath(&this->actor);
}

void func_80B60138(EnDragon* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    u32 sp30;

    if ((this->unk_2BA == 1) && ((this->unk_2DC.elements[2].info.bumperFlags & BUMP_HIT) ||
                                 (this->unk_2DC.elements[3].info.bumperFlags & BUMP_HIT) ||
                                 (this->unk_2DC.elements[4].info.bumperFlags & BUMP_HIT) ||
                                 (this->unk_2DC.elements[5].info.bumperFlags & BUMP_HIT) ||
                                 (this->unk_2DC.elements[6].info.bumperFlags & BUMP_HIT) ||
                                 (this->unk_2DC.elements[7].info.bumperFlags & BUMP_HIT))) {
        Actor_ApplyDamage(&this->actor);
        Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 25);
        if (this->actor.colChkInfo.health > 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_DAMAGE);
            this->unk_2BA = 3;
        } else {
            Enemy_StartFinishingBlow(globalCtx, &this->actor);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_UTSUBO_DEAD);
            this->actor.flags |= ACTOR_FLAG_8000000;
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->actor.flags |= ACTOR_FLAG_100000;
            this->unk_2BA = 5;
            this->actionFunc = func_80B5FCC0;
        }
    }

    if ((this->unk_2BA == 1) && (this->unk_2B6 == 0) && (player->invincibilityTimer == 0) &&
        (this->unk_2DC.elements[0].info.ocElemFlags & OCELEM_HIT) &&
        (!(func_800B64FC(globalCtx, 1000.0f, &this->actor.world.pos, &sp30) >= 0.0f) || (sp30 != 1))) {
        this->actor.speedXZ = 0.0f;
        this->unk_2BA = 2;
        this->actor.flags |= ACTOR_FLAG_100000;
        this->actionFunc = func_80B5F418;
    }
}

void EnDragon_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnDragon* this = THIS;

    if (this->unk_2AE != 0) {
        this->unk_2AE--;
    }

    if (this->unk_2B4 != 0) {
        this->unk_2B4--;
    }

    if (this->unk_2B2 != 0) {
        this->unk_2B2--;
    }

    if (this->unk_2B6 != 0) {
        this->unk_2B6--;
    }

    func_80B60138(this, globalCtx);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Math_Vec3f_Copy(&this->actor.focus.pos, &this->unk_29C);
    Math_Vec3s_Copy(&this->actor.focus.rot, &this->actor.world.rot);
    Actor_SetScale(&this->actor, this->unk_2D4);

    this->actionFunc(this, globalCtx);
    Actor_MoveWithGravity(&this->actor);

    if (this->unk_2BA != 2) {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->unk_2DC.base);
    }

    if (this->unk_2BA < 3) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->unk_2DC.base);
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->unk_2DC.base);
    }
}

s32 func_80B6043C(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDragon* this = THIS;

    if (limbIndex == 15) {
        rot->x += this->unk_2AC;
        rot->y += this->unk_2AA;
        rot->z += this->unk_2A8;
    }

    return false;
}

void func_80B60494(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDragon* this = THIS;
    Vec3f D_80B60878 = { 350.0f, -120.0f, -60.0f };

    if (limbIndex == 15) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->unk_254);
        D_80B60878.x = 350.0f;
        D_80B60878.y = -120.0f;
        D_80B60878.z = -60.0f;
        Matrix_MultiplyVector3fByState(&D_80B60878, &this->unk_26C);
    }

    if (limbIndex == 11) {
        Matrix_MultiplyVector3fByState(&gZeroVec3f, &this->unk_29C);
    }

    Collider_UpdateSpheres(limbIndex, &this->unk_2DC);
}

void EnDragon_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDragon* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          func_80B6043C, func_80B60494, &this->actor);
}
