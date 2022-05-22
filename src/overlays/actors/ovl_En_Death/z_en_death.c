/*
 * File: z_en_death.c
 * Overlay: ovl_En_Death
 * Description: Gomess
 */

#include "z_en_death.h"
#include "z64rumble.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_UNFRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_IGNORE_QUAKE)

#define THIS ((EnDeath*)thisx)

void EnDeath_Init(Actor* thisx, PlayState* play);
void EnDeath_Destroy(Actor* thisx, PlayState* play);
void EnDeath_Update(Actor* thisx, PlayState* play);
void EnDeath_Draw(Actor* thisx, PlayState* play);

void func_808C589C(EnDeath* this, PlayState* play);
void func_808C5AB8(EnDeath* this, PlayState* play);
void func_808C5CB4(EnDeath* this, PlayState* play);
void func_808C5E90(EnDeath* this, PlayState* play);
void func_808C6070(EnDeath* this, PlayState* play);
void func_808C64DC(EnDeath* this, PlayState* play);
void func_808C66A8(EnDeath* this, PlayState* play);
void func_808C682C(EnDeath* this, PlayState* play);
void func_808C692C(EnDeath* this, PlayState* play);
void func_808C6AB0(EnDeath* this, PlayState* play);
void func_808C6CDC(EnDeath* this, PlayState* play);
void func_808C6F6C(EnDeath* this, PlayState* play);
void func_808C72AC(EnDeath* this, PlayState* play);
void func_808C74F8(EnDeath* this, PlayState* play);
void func_808C7888(EnDeath* this, PlayState* play);
void func_808C7AAC(EnDeath* this, PlayState* play);
void func_808C7B88(EnDeath* this, PlayState* play);
void func_808C7C88(EnDeath* this, PlayState* play);
void func_808C7D34(EnDeath* this, PlayState* play);
void func_808C7DCC(EnDeath* this, PlayState* play);

void func_808C597C(EnDeath* this, PlayState* play);
void func_808C5C0C(EnDeath* this);
void func_808C5D6C(EnDeath* this, PlayState* play);
void func_808C5F58(EnDeath* this, PlayState* play);
void func_808C645C(EnDeath* this);
void func_808C6620(EnDeath* this);
void func_808C67C8(EnDeath* this);
void func_808C68B8(EnDeath* this);
void func_808C6A08(EnDeath* this);
void func_808C70D8(EnDeath* this, PlayState* play);
void func_808C74A4(EnDeath* this);
void func_808C7A30(EnDeath* this, PlayState* play);
void func_808C7AEC(EnDeath* this);
void func_808C7C04(EnDeath* this);
void func_808C7CFC(EnDeath* this);
void func_808C7DB8(EnDeath* this);

#if 0
ActorInit En_Death_InitVars = {
    /**/ ACTOR_EN_DEATH,
    /**/ ACTORCAT_ENEMY,
    /**/ FLAGS,
    /**/ OBJECT_DEATH,
    /**/ sizeof(EnDeath),
    /**/ EnDeath_Init,
    /**/ EnDeath_Destroy,
    /**/ EnDeath_Update,
    /**/ EnDeath_Draw,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_808C98E0 = {
    { COLTYPE_HIT3, AT_NONE, AC_NONE | AC_TYPE_GET_PLAYER(play), OC1_NONE, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 1, { { 0, 0, 0 }, 22 }, 100 },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_808C990C = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 35, 90, 20, { 0, 0, 0 } },
};

// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_808C9938[2] = {
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x20 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
    },
    {
        { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x04, 0x20 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_808C99B0 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_TRIS, },
    ARRAY_COUNT(sTrisElementsInit), D_808C9938, // sTrisElementsInit,
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_808C99C0 = {
    { COLTYPE_NONE, AT_NONE | AT_TYPE_ENEMY, AC_NONE, OC1_NONE, OC2_TYPE_2, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x04, 0x20 }, { 0x00000000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL | TOUCH_UNK7, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// static DamageTable sDamageTable = {
static DamageTable D_808C9A10 = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(1, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(1, 0x0),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(1, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0x2),
    /* Ice arrow      */ DMG_ENTRY(1, 0x3),
    /* Light arrow    */ DMG_ENTRY(2, 0x4),
    /* Goron spikes   */ DMG_ENTRY(1, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(1, 0x0),
    /* Deku launch    */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
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
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_808C9A30 = { 20, 28, 90, 20, 100 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808C9A60[] = {
    ICHAIN_VEC3F(scale, 0, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, TATL_HINT_ID_GOMESS, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 6000, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, TARGET_MODE_5, ICHAIN_STOP),
};

#endif

extern ColliderSphereInit D_808C98E0;
extern ColliderCylinderInit D_808C990C;
extern ColliderTrisElementInit D_808C9938[2];
extern ColliderTrisInit D_808C99B0;
extern ColliderQuadInit D_808C99C0;
extern DamageTable D_808C9A10;
extern CollisionCheckInfoInit2 D_808C9A30;
extern InitChainEntry D_808C9A60[];
extern UNK_TYPE D_808C9A3C;
extern Vec3f D_808C9AF4;
extern Vec3f D_808C9B00;
extern Vec3f D_808C9B0C[];
extern s8 D_808C9B48[];
extern Vec3f D_808C9ABC;
extern Color_RGBA8 D_808C9AC8;
extern Color_RGBA8 D_808C9ACC;

extern FlexSkeletonHeader D_0600AD08;
extern AnimationHeader D_06003CAC;
extern AnimationHeader D_0600CB2C;
extern AnimationHeader D_0600B284;
extern AnimationHeader D_0600B284;
extern AnimationHeader D_0600B508;
extern AnimationHeader D_06001F80;
extern AnimationHeader D_06000E64;
extern AnimationHeader D_06002DE8;
extern AnimationHeader D_0600352C;
extern AnimationHeader D_06001834;
extern AnimationHeader D_060015B4;
extern AnimatedMaterial D_0600CBC0;
extern AnimatedMaterial D_0600CB84;
extern Gfx D_06009988[];
extern Gfx D_06009BA0[];
extern Gfx D_06006F88[];
extern Gfx D_060073D0[];

typedef struct {
    Actor actor;
    char unk_144[0x18];
    f32 unk_15C;
} UnkActor;

void EnDeath_Init(Actor* thisx, PlayState* play) {
    EnDeath* this = THIS;
    PlayState* play2 = play;

    f32 phi_f20 = 15.0f;
    s16 phi_s3 = 0;

    s32 i;

    Actor_ProcessInitChain(&this->actor, D_808C9A60);
    ActorShape_Init(&this->actor.shape, 5500.0f, ActorShadow_DrawCircle, 80.0f);

    SkelAnime_InitFlex(play2, &this->skelAnime, &D_0600AD08, &D_06003CAC, this->unk_1E2, this->unk_266, 22);

    Collider_InitAndSetSphere(play2, &this->unk_808, &this->actor, &D_808C98E0);
    Collider_InitAndSetCylinder(play2, &this->unk_73C, &this->actor, &D_808C990C);
    Collider_InitAndSetQuad(play2, &this->unk_788, &this->actor, &D_808C99C0);
    Collider_InitAndSetTris(play2, &this->unk_860, &this->actor, &D_808C99B0, this->unk_880);

    this->unk_808.dim.worldSphere.radius = this->unk_808.dim.modelSphere.radius;

    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &D_808C9A10, &D_808C9A30);

    Effect_Add(play2, &this->unk_300, 2, 0, 0, &D_808C9A3C);

    if (!(gSaveContext.eventInf[6] & 8)) {
        this->actor.world.pos.y += 400.0f;
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_6E4); i++) {
        this->unk_6E4[i] = Actor_SpawnAsChild(&play2->actorCtx, &this->actor, play2, ACTOR_EN_MINIDEATH,
                                              this->actor.world.pos.x, this->actor.world.pos.y + phi_f20,
                                              this->actor.world.pos.z, 0, phi_s3, 0, i);
        if (this->unk_6E4[i] == NULL) {
            Actor_Kill(&this->actor);
        }
        phi_s3 += 0x3A00;
        phi_f20 += 4.0f;
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_6E4) - 1; i++) {
        this->unk_6E4[i]->child = this->unk_6E4[i + 1];
    }

    this->unk_734 = Lib_SegmentedToVirtual(&D_0600CBC0);
    this->unk_738 = Lib_SegmentedToVirtual(&D_0600CB84);

    if (gSaveContext.eventInf[6] & 8) {
        this->unk_18E = 1;
        Actor_SetScale(&this->actor, 0.01f);
        this->unk_191 = 0x17;
        this->actor.params = 0x14;
        this->unk_304 = 1.0f;
        func_808C7DB8(this);
        return;
    }
    this->unk_192 = 1;
    this->actor.flags &= ~1;
    func_808C7CFC(this);
}

void EnDeath_Destroy(Actor* thisx, PlayState* play) {
    EnDeath* this = THIS;

    Collider_DestroySphere(play, &this->unk_808);
    Collider_DestroyCylinder(play, &this->unk_73C);
    Collider_DestroyQuad(play, &this->unk_788);
    Collider_DestroyTris(play, &this->unk_860);
    AudioSfx_StopByPos(&this->unk_338);
    Effect_Destroy(play, this->unk_300);
}

void func_808C5310(PlayState* play) {
    LightSettings* lightSettings;
    s32 i;

    play->envCtx.lightSettingOverride = 0x14;
    play->envCtx.lightSetting = 0x14;
    play->envCtx.prevLightSetting = 0x14;
    play->envCtx.lightBlend = 1.0f;
    lightSettings = &play->envCtx.lightSettingsList[20];

    for (i = 0; i != 3; i++) {
        lightSettings->light1Dir[i] = play->envCtx.lightSettings.light1Dir[i];
        lightSettings->light2Dir[i] = play->envCtx.lightSettings.light2Dir[i];
    }
}

void func_808C5394(EnDeath* this) {
    Actor_PlaySfx_Flagged(&this->actor, 0x3260);

    if (this->unk_2EA == 0) {
        this->unk_2EA = 0x28;
    }
    this->unk_2EA--;
    this->actor.world.pos.y = (1.0f - Math_CosS(this->unk_2EA * 0x666)) * 7.5f + this->actor.home.pos.y;
}

s32 func_808C5428(EnDeath* this, PlayState* play) {
    Actor* temp_v0 = func_800BC270(play, &this->actor, 80.0f, 0x138B0);
    s16 ret;

    if (temp_v0 != NULL &&
        (ret = Actor_WorldYawTowardActor(&this->actor, temp_v0) - this->actor.shape.rot.y, ABS_ALT(ret) < 0x2000) &&
        (ret = Actor_WorldPitchTowardPoint(temp_v0, &this->actor.focus.pos) - temp_v0->world.rot.x, ABS_ALT(ret) < 0x3000)) {
        return 1;
    }
    return 0;
}

void func_808C54F0(EnDeath* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C54F0.s")
/*
void func_808C54F0(EnDeath *this) {
    f32 sp64 = Math_SinS(this->actor.shape.rot.y);
    f32 sp60 = Math_CosS(this->actor.shape.rot.y);
    Vec3f sp54;
    Vec3f sp48;
    Vec3f sp3C;

    sp3C.x = this->actor.world.pos.x - (70.0f * sp60) + (75.0f * sp64);
    sp3C.y = this->actor.world.pos.y + -10.0f;
    sp3C.z = this->actor.world.pos.z + (70.0f * sp64) + (75.0f * sp60);

    sp48.x = this->actor.world.pos.x + (70.0f * sp60) + (65.0f * sp64);
    sp48.y = sp3C.y + 150.0f;
    sp48.z = this->actor.world.pos.z - (70.0f * sp64) + (65.0f * sp60);

    sp54.x = sp3C.x + (-10.0f * sp64);
    sp54.y = sp3C.y + 150.0f;
    sp54.z = sp3C.z + (-10.0f * sp60);

    Collider_SetTrisVertices(&this->unk_860, 0, &sp3C, &sp48, &sp54);

    sp54.x = sp48.x + (10.0f * sp64);
    sp54.y = sp3C.y;
    sp54.z = sp48.z + (10.0f * sp60);

    Collider_SetTrisVertices(&this->unk_860, 1, &sp3C, &sp54, &sp48);
}
*/

#ifdef NON_MATCHING
// regalloc differences
f32 func_808C566C(EnDeath* this) {
    this->unk_308 = this->actor.world.pos.y - this->actor.home.pos.y;
    this->unk_308 = CLAMP_MIN(this->unk_308, 0.0f);
    this->unk_308 *= 0.02f;
    this->unk_308 = SQ(this->unk_308) * 3.0f + 80.0f;
    this->unk_2F6 += (s16)(65536.0f * (22.5f / (this->unk_308 * (2 * M_PI))));
}
#else
f32 func_808C566C(EnDeath* this);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C566C.s")
#endif

void func_808C571C(EnDeath* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f sp30;
    Vec3f sp24;

    this->actor.shape.rot.y = this->actor.shape.rot.y - 0x657A;
    this->unk_2EE = 0x3C;
    sp30.x = (Math_SinS(this->actor.home.rot.y + 0x98) * 542.0f) + this->actor.world.pos.x;
    sp30.z = (Math_CosS(this->actor.home.rot.y + 0x98) * 542.0f) + this->actor.world.pos.z;
    sp30.y = this->actor.home.pos.y + 3.0f;
    sp24.x = this->actor.world.pos.x;
    sp24.z = this->actor.world.pos.z;
    sp24.y = this->actor.world.pos.y - 116.0f;
    player->actor.world.pos.x = Math_SinS(this->actor.home.rot.y - 0x370) * 463.0f + this->actor.world.pos.x;
    player->actor.world.pos.z = Math_CosS(this->actor.home.rot.y - 0x370) * 463.0f + this->actor.world.pos.z;
    player->actor.shape.rot.y = Actor_WorldYawTowardActor(&player->actor, &this->actor);
    Play_SetCameraAtEye(play, this->unk_2FA, &sp24, &sp30);
    Play_SetCameraFov(play, this->unk_2FA, 77.0f);
    Player_SetCsAction(play, &this->actor, 0x15);
    this->unk_188 = func_808C589C;
}

void func_808C589C(EnDeath* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->actor.world.pos.x = Math_SinS(this->actor.home.rot.y - 0x370) * 463.0f + this->actor.world.pos.x;
    player->actor.world.pos.z = Math_CosS(this->actor.home.rot.y - 0x370) * 463.0f + this->actor.world.pos.z;
    player->actor.shape.rot.y = Actor_WorldYawTowardActor(&player->actor, &this->actor);

    if (this->unk_2EE == 0x19) {
        Player_SetCsAction(play, &this->actor, 0x51);
    }
    if (this->unk_2EE > 0) {
        this->unk_2EE--;
    } else {
        func_808C597C(this, play);
    }
    func_808C566C(this);
}

void func_808C597C(EnDeath* this, PlayState* play) {
    Camera* sp24 = Play_GetCamera(play, this->unk_2FA);
    s32 i;

    func_808C5310(play);

    for (i = 0; i < ARRAY_COUNT(this->unk_6E4); i++) {
        this->unk_6E4[i]->params = 7;
    }

    this->unk_2EE = 0x32;
    this->unk_344.x = Math_SinS(this->actor.home.rot.y) * 140.0f + this->actor.world.pos.x;
    this->unk_344.z = Math_CosS(this->actor.home.rot.y) * 140.0f + this->actor.world.pos.z;
    this->unk_344.y = this->actor.home.pos.y + 20.0f;
    this->unk_350.x = this->actor.world.pos.x;
    this->unk_350.z = this->actor.world.pos.z;
    this->unk_350.y = this->actor.home.pos.y + 50.0f;
    this->unk_30C = Math_Vec3f_DistXYZ(&sp24->eye, &this->unk_344) * 0.0225f;
    this->unk_310 = Math_Vec3f_DistXYZ(&sp24->at, &this->unk_350) * 0.0225f;
    this->unk_188 = func_808C5AB8;
}

void func_808C5AB8(EnDeath* this, PlayState* play) {
    Camera* sp2C = Play_GetCamera(play, this->unk_2FA);

    if (this->unk_2EE == 0x2A) {
        Player_SetCsAction(play, &this->actor, 4);
    } else if (this->unk_2EE == 0x1B) {
        Player_SetCsAction(play, &this->actor, 0x7B);
    }
    if (this->unk_2EE <= 0) {
        if (this->actor.world.pos.y < (this->actor.home.pos.y + 400.0f) - 225.0f) {
            play->envCtx.lightSettingOverride = 0x1A;
        }
        Math_Vec3f_StepTo(&sp2C->eye, &this->unk_344, this->unk_30C);
        Math_Vec3f_StepTo(&sp2C->at, &this->unk_350, this->unk_310);
        Play_SetCameraAtEye(play, this->unk_2FA, &sp2C->at, &sp2C->eye);
        if (Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y, 9.0f) != 0) {
            this->unk_2EE--;
            if (this->unk_2EE == -0x14) {
                func_808C5C0C(this);
            }
        }
    } else {
        this->unk_2EE--;
    }
    func_808C566C(this);
}

void func_808C5C0C(EnDeath* this) {
    gSaveContext.eventInf[6] |= 8;
    Animation_Change(&this->skelAnime, &D_0600B284, 0.0f, 0.0f, Animation_GetLastFrame(&D_0600B284), 2, 0.0f);
    this->actor.scale.y = 0.01f;
    this->actor.shape.rot.y += 0x777F;
    Actor_PlaySfx(&this->actor, 0x3AB4);
    this->unk_188 = func_808C5CB4;
}

void func_808C5CB4(EnDeath* this, PlayState* play) {
    s32 temp_v0 = Math_StepToF(&this->actor.scale.x, 0.01f, 0.0005f);
    f32 temp;

    this->actor.scale.z = this->actor.scale.x;
    temp = 0.01f - this->actor.scale.x;
    if (temp > 0.0025f) {
        temp = 0.0025f;
    }
    this->actor.shape.rot.y += (s16)(temp * 4505600.0f);
    if (temp_v0 != 0) {
        this->unk_192 = 0;
        func_808C5D6C(this, play);
    }
    func_808C566C(this);
}

void func_808C5D6C(EnDeath* this, PlayState* play) {
    Camera* sp24 = Play_GetCamera(play, this->unk_2FA);
    f32 sp20 = 1.0f / Animation_GetLastFrame(&D_0600B284);

    this->unk_2EE = 0xA;
    this->skelAnime.playSpeed = 1.0f;
    this->actor.shape.rot.y = this->actor.home.rot.y;
    this->unk_344.x = Math_SinS(this->actor.home.rot.y) * 50.0f + this->actor.world.pos.x;
    this->unk_344.z = Math_CosS(this->actor.home.rot.y) * 50.0f + this->actor.world.pos.z;
    this->unk_344.y = this->actor.home.pos.y + 95.0f;
    this->unk_350.x = this->actor.world.pos.x;
    this->unk_350.z = this->actor.world.pos.z;
    this->unk_350.y = this->actor.world.pos.y + 100.0f;
    this->unk_30C = Math_Vec3f_DistXYZ(&sp24->eye, &this->unk_344) * sp20;
    this->unk_310 = Math_Vec3f_DistXYZ(&sp24->at, &this->unk_350) * sp20;

    this->unk_188 = func_808C5E90;
}

void func_808C5E90(EnDeath* this, PlayState* play) {
    Camera* temp_v1 = Play_GetCamera(play, this->unk_2FA);

    if (this->unk_191 < 23) {
        this->unk_191++;
    }
    Math_Vec3f_StepTo(&temp_v1->eye, &this->unk_344, this->unk_30C);
    Math_Vec3f_StepTo(&temp_v1->at, &this->unk_350, this->unk_310);
    Play_SetCameraAtEye(play, this->unk_2FA, &temp_v1->at, &temp_v1->eye);
    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->unk_2EE > 0) {
            this->unk_2EE--;
        } else {
            func_808C5F58(this, play);
        }
    }
    func_808C566C(this);
}

void func_808C5F58(EnDeath* this, PlayState* play) {
    Camera* sp24 = Play_GetCamera(play, this->unk_2FA);

    Animation_PlayOnce(&this->skelAnime, &D_0600CB2C);
    this->unk_191 = 0x17;
    Audio_PlayBgm_StorePrevBgm(0x38);
    this->unk_344.x = Math_SinS(this->actor.home.rot.y) * 230.0f + this->actor.world.pos.x;
    this->unk_344.z = Math_CosS(this->actor.home.rot.y) * 230.0f + this->actor.world.pos.z;
    this->unk_344.y = this->actor.home.pos.y + 40.0f;
    this->unk_350.y = this->actor.world.pos.y + 85.0f;
    this->unk_30C = Math_Vec3f_DistXYZ(&sp24->eye, &this->unk_344) * 0.14285715f;
    this->unk_310 = Math_Vec3f_DistXYZ(&sp24->at, &this->unk_350) * 0.14285715f;
    Audio_PlaySfx_AtPos(&this->unk_338, 0x3AB0);
    this->unk_188 = func_808C6070;
}

void func_808C6070(EnDeath* this, PlayState* play) {
    Camera* sp44 = Play_GetCamera(play, this->unk_2FA);
    f32 phi_f2;

    if (Animation_OnFrame(&this->skelAnime, 12.0f)) {
        play->envCtx.lightSettingOverride = 0x1B;
    } else if (Animation_OnFrame(&this->skelAnime, 25.0f)) {
        play->envCtx.lightSettingOverride = 0x1A;
    } else if (Animation_OnFrame(&this->skelAnime, 38.0f)) {
        s32 i;

        for (i = 0; i < ARRAY_COUNT(this->unk_6E4); i++) {
            this->unk_6E4[i]->params = 9;
        }
    } else if (Animation_OnFrame(&this->skelAnime, 14.0f)) {
        s32 i;

        for (i = 0; i < ARRAY_COUNT(this->unk_6E4); i++) {
            this->unk_6E4[i]->params = 8;
            this->unk_6E4[i]->world.pos.x =
                (this->unk_6E4[i]->world.pos.x - this->actor.world.pos.x) * 1.8f + this->actor.world.pos.x;
            this->unk_6E4[i]->world.pos.z =
                (this->unk_6E4[i]->world.pos.z - this->actor.world.pos.z) * 1.8f + this->actor.world.pos.z;
            this->unk_6E4[i]->world.pos.y =
                (this->unk_6E4[i]->world.pos.y - this->actor.world.pos.y) * 1.7f + this->actor.world.pos.y;
        }
        this->unk_18E = 1;
        this->unk_304 = 1.0f;
    }
    Math_Vec3f_StepTo(&sp44->eye, &this->unk_344, this->unk_30C);
    Math_Vec3f_StepTo(&sp44->at, &this->unk_350, this->unk_310);
    Math_StepToF(&sp44->fov, 60.0f, 2.4285715f);
    Play_SetCameraFov(play, this->unk_2FA, sp44->fov);
    Play_SetCameraAtEye(play, this->unk_2FA, &sp44->at, &sp44->eye);

    phi_f2 = CLAMP(this->skelAnime.curFrame, 10.0f, 14.0f) - 10.0f;
    this->unk_304 = phi_f2 * 0.25f;
    if (phi_f2 < 14.0f) {
        func_808C566C(this);
    }
    if (SkelAnime_Update(&this->skelAnime)) {
        CutsceneManager_Stop(this->actor.csId);
        Player_SetCsAction(play, &this->actor, 6);
        this->actor.flags |= 1;
        this->unk_808.base.acFlags |= 1;
        func_808C645C(this);
    }
}

void func_808C645C(EnDeath* this) {
    Animation_MorphToLoop(&this->skelAnime, &D_06003CAC, 10.0f);

    this->actor.speed = 1.5f;
    if (this->unk_188 == func_808C682C || this->unk_188 == func_808C6AB0) {
        this->unk_2EE = 0x8C;
    } else {
        this->unk_2EE = 0x64;
    }
    this->unk_188 = func_808C64DC;
}

void func_808C64DC(EnDeath* this, PlayState* play) {
    if (play->envCtx.lightSettingOverride == 0x14) {
        play->envCtx.lightSettingOverride = 0x1A;
    }
    func_808C5394(this);
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 8, 0x1000, 0x100);

    if (this->unk_2EE > 0) {
        this->unk_2EE--;
    }
    if (this->actor.params < 5 && Rand_ZeroOne() < 0.4f && func_808C5428(this, play)) {
        func_808C68B8(this);
        return;
    }
    if (this->unk_2EE < 0x64 && this->actor.xzDistToPlayer < 200.0f) {
        func_808C6620(this);
        return;
    }
    if (this->unk_2EE == 0) {
        if (this->actor.params >= 5) {
            func_808C7AEC(this);
            return;
        }
        func_808C6A08(this);
    }
}

void func_808C6620(EnDeath* this) {
    Animation_Change(&this->skelAnime, &D_06000E64, 1.0f, 0.0f, 10.0f, 2, -3.0f);
    this->unk_2EE = 0;
    this->unk_2EA = 0;
    this->actor.speed = 8.0f;
    Actor_PlaySfx(&this->actor, NA_SE_EN_DEATH_ATTACK);
    this->unk_188 = func_808C66A8;
}

void func_808C66A8(EnDeath* this, PlayState* play) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0x1000, 0x200);
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y, 3.0f);
    this->actor.shape.rot.x = (s16)((100.0f - this->actor.xzDistToPlayer) * 0.01f * 1024.0f);
    this->actor.shape.rot.x = CLAMP_MIN(this->actor.shape.rot.x, 0);

    if (this->unk_2EE > 0) {
        this->unk_2EE++;
        if (this->unk_2EE == 3) {
            func_808C67C8(this);
            return;
        }
    } else if (SkelAnime_Update(&this->skelAnime) && this->actor.xzDistToPlayer < 100.0f) {
        Audio_PlaySfx_AtPos(&this->unk_338, 0x3AAC);
        this->unk_2EE++;
        this->actor.speed = 0.0f;
    }
}

void func_808C67C8(EnDeath* this) {
    this->skelAnime.endFrame = Animation_GetLastFrame(&D_06000E64);
    this->unk_2EE = 0;
    this->unk_2EC = -1;
    this->unk_18C = 1;
    this->unk_188 = func_808C682C;
    this->actor.speed = 0.0f;
}

void func_808C682C(EnDeath* this, PlayState* play) {
    this->unk_2EE++;
    if (this->skelAnime.curFrame > 20.0f) {
        this->unk_18C = 0;
        this->unk_788.base.atFlags &= 0xFFFE;
        Math_ScaledStepToS(&this->actor.shape.rot.x, 0, 0x200);
    }
    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.shape.rot.x = 0;
        func_808C645C(this);
    }
}

void func_808C68B8(EnDeath* this) {
    Animation_MorphToLoop(&this->skelAnime, &D_0600B508, -3.0f);
    this->unk_2EC = 0x1F;
    this->unk_2EE = 0x1E;
    this->actor.speed = 0.0f;
    func_808C54F0(this);
    this->unk_18C = 1;
    this->unk_190 = -3;
    this->unk_188 = func_808C692C;
}

void func_808C692C(EnDeath* this, PlayState* play) {
    func_808C5394(this);

    this->unk_2EE--;
    if (this->unk_190 < 7) {
        this->unk_190++;
    }
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        Audio_PlaySfx_AtPos(&this->unk_338, 0x3AAD);
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 8, 0x1000, 0x100);
    func_808C54F0(this);
    if (this->unk_2EE == 0) {
        if (this->actor.xzDistToPlayer > 200.0f) {
            func_808C6A08(this);
            return;
        }
        func_808C645C(this);
    }
}

void func_808C6A08(EnDeath* this) {
    if (this->unk_188 != func_808C692C) {
        Animation_MorphToLoop(&this->skelAnime, &D_0600B508, -3.0f);
        this->unk_190 = -3;
        this->unk_2EE = 0;
        this->unk_2EC = -1;
        this->unk_18C = 1;
        this->actor.speed = 0.0f;
    } else {
        this->unk_2EE = 0xA;
        this->unk_2EC = 9;
        this->actor.speed = 10.0f;
    }
    func_808C54F0(this);
    this->unk_188 = func_808C6AB0;
}

void func_808C6AB0(EnDeath* this, PlayState* play) {
    func_808C5394(this);
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 0.0f)) {
        Audio_PlaySfx_AtPos(&this->unk_338, 0x3AAD);
    }
    if (this->unk_190 < 7) {
        this->unk_190++;
    }
    this->unk_2EE++;
    if (this->unk_2EE < 10) {
        Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 8, 0x1000, 0x100);
    } else if (this->unk_2EE == 10) {
        this->actor.speed = 10.0f;
    }
    func_808C54F0(this);
    Math_ScaledStepToS(&this->unk_2F2, (s32)(Math_SinS(this->unk_2EE * 0x2000) * 2048.0f) + 0x3000, 0x1000);
    Math_ScaledStepToS(&this->unk_2F4, (s32)(Math_SinS(this->unk_2EE * 0x2000 - 0x8000) * 2048.0f), 0x1000);
    if ((this->actor.bgCheckFlags & 8) || (this->unk_788.base.atFlags & 2) || (this->unk_860.base.atFlags & 2)) {
        this->unk_18C = 0;
        this->unk_788.base.atFlags &= 0xFFFC;
        this->unk_860.base.atFlags &= 0xFFFD;
        func_808C645C(this);
    }
}

void func_808C6C5C(EnDeath* this) {
    Animation_PlayOnce(&this->skelAnime, &D_06001F80);
    this->actor.speed = 10.0f;
    func_800BE568(&this->actor, &this->unk_808);
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 0xF);
    Actor_PlaySfx(&this->actor, 0x3AB1);
    this->unk_188 = func_808C6CDC;
}

void func_808C6CDC(EnDeath* this, PlayState* play) {
    func_808C5394(this);
    Math_StepToF(&this->actor.speed, 0.0f, 0.5f);
    if (SkelAnime_Update(&this->skelAnime)) {
        this->unk_808.base.acFlags |= 1;
        func_808C6A08(this);
    }
}

void func_808C6D40(EnDeath* this, PlayState* play) {
    Vec3f sp3C;
    Vec3f sp30;
    s32 i;

    this->actor.flags &= ~0x1001;
    Animation_PlayOnce(&this->skelAnime, &D_06002DE8);

    for (i = 0; i < ARRAY_COUNT(this->unk_6E4); i++) {
        this->unk_6E4[i]->params = 6;
    }

    this->unk_18D = 0;
    this->unk_808.base.acFlags &= 0xFFFE;
    Actor_SetColorFilter(&this->actor, 0x4000, 0xFF, 0, 0x1E);
    this->unk_2EE = 0x23;
    this->actor.world.pos.y = this->actor.home.pos.y;
    this->actor.speed = 0.0f;
    this->unk_344.x = Math_SinS(this->actor.shape.rot.y + 0x900) * 79.0f + this->actor.world.pos.x;
    this->unk_344.z = Math_CosS(this->actor.shape.rot.y + 0x900) * 79.0f + this->actor.world.pos.z;
    this->unk_344.y = this->actor.home.pos.y + 63.0f;
    sp30.x = this->actor.world.pos.x;
    sp30.y = this->actor.world.pos.y + 100.0f;
    sp30.z = this->actor.world.pos.z;
    sp3C.x = Math_SinS(this->actor.shape.rot.y + 0x900) * 179.0f + this->actor.world.pos.x;
    sp3C.z = Math_CosS(this->actor.shape.rot.y + 0x900) * 179.0f + this->actor.world.pos.z;
    sp3C.y = this->actor.home.pos.y + 30.0f;
    Play_SetCameraAtEye(play, this->unk_2FA, &sp30, &sp3C);
    this->unk_30C = Math_Vec3f_DistXYZ(&sp3C, &this->unk_344) * 0.05f;
    this->actor.shape.rot.y += 0x2000;
    Player_SetCsAction(play, &this->actor, 7);
    Actor_PlaySfx(&this->actor, 0x3AB2);
    this->unk_188 = func_808C6F6C;
}

void func_808C6F6C(EnDeath* this, PlayState* play) {
    Camera* camera = Play_GetCamera(play, this->unk_2FA);
    f32 sp28 = Math_Vec3f_StepTo(&camera->eye, &this->unk_344, this->unk_30C);

    Play_SetCameraAtEye(play, this->unk_2FA, &camera->at, &camera->eye);
    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.shape.rot.y += 0x2000;
        Animation_PlayLoop(&this->skelAnime, &D_0600352C);
    } else if (this->skelAnime.animation == &D_06002DE8) {
        this->actor.shape.rot.y += 0x2000;
        if (this->skelAnime.curFrame > 3.0f) {
            SysMatrix_SetCurrentState(&this->unk_6A4);
            SysMatrix_InsertXRotation_s(-0x1000, 1);
            SysMatrix_CopyCurrentState(&this->unk_6A4);
            this->unk_18E = 0;
            this->unk_6A4.wy += 18.0f;
            Actor_PlaySfx(&this->actor, 0x3AAC);
        }
    }
    if (sp28 < 0.1f) {
        if (this->unk_2EE == 35) {
            Audio_PlaySfx_AtPosWithVolumeTransition(&this->unk_338, 0x3AAE, 0x41);
        }
        if (this->unk_2EE > 0) {
            this->unk_2EE--;
        }
        if (this->unk_2EE == 0) {
            func_808C70D8(this, play);
        }
    }
}

void func_808C70D8(EnDeath* this, PlayState* play) {
    LightSettings* lightSettings1;
    LightSettings* lightSettings2;
    Player* player = GET_PLAYER(play);
    Vec3f sp40;
    Vec3f sp34;
    f32 sp30;
    f32 sp2C;
    s32 i;

    Animation_PlayLoop(&this->skelAnime, &D_0600352C);
    this->unk_2EE = 0x1E;
    player->actor.shape.rot.y = Actor_WorldYawTowardPoint(&player->actor, &this->actor.home.pos) + 0x1000;
    this->actor.shape.rot.y = player->actor.shape.rot.y + 0x6000;
    sp30 = Math_SinS(player->actor.shape.rot.y);
    sp2C = Math_CosS(player->actor.shape.rot.y);
    this->actor.world.pos.x = player->actor.world.pos.x + (260.0f * sp30);
    this->actor.world.pos.z = player->actor.world.pos.z + (260.0f * sp2C);
    this->actor.world.pos.y = this->actor.home.pos.y + 15.0f;
    sp40.x = (Math_SinS((s16)(player->actor.shape.rot.y - 0x2500)) * 182.0f) + this->actor.world.pos.x;
    sp40.z = (Math_CosS((s16)(player->actor.shape.rot.y - 0x2500)) * 182.0f) + this->actor.world.pos.z;
    sp40.y = this->actor.world.pos.y - 13.0f;
    sp34.x = player->actor.world.pos.x + (120.0f * sp30);
    sp34.y = player->actor.world.pos.y + 90.0f;
    sp34.z = player->actor.world.pos.z + (120.0f * sp2C);
    Play_SetCameraAtEye(play, this->unk_2FA, &sp34, &sp40);

    lightSettings1 = &play->envCtx.lightSettingsList[20];
    lightSettings2 = &play->envCtx.lightSettingsList[21];

    for (i = 0; i < 3; i++) {
        lightSettings1->light1Dir[i] = lightSettings2->light1Dir[i];
        lightSettings1->light2Dir[i] = lightSettings2->light2Dir[i];
    }

    this->unk_188 = func_808C72AC;
}

void func_808C72AC(EnDeath* this, PlayState* play) {
    f32 sin;
    f32 cos;
    s16 temp_v1;

    SkelAnime_Update(&this->skelAnime);

    this->unk_2EE--;
    if (this->unk_2EE >= 0 && this->unk_2EE < 3) {
        temp_v1 = Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000;
        sin = Math_SinS(temp_v1);
        cos = Math_CosS(temp_v1);
        SysMatrix_InsertTranslation(this->actor.world.pos.x + (83.0f * sin) + (-38.0f * cos),
                                    this->actor.world.pos.y + 53.0f + 15.0f * this->unk_2EE,
                                    this->actor.world.pos.z + (83.0f * cos) - (-38.0f * sin), 0);
        Matrix_RotateY(temp_v1 - 0x3300, 1);
        SysMatrix_InsertXRotation_s(0x1100 - this->unk_2EE * 0x1800, 1);
        SysMatrix_InsertZRotation_s(-0xA00, 1);
        Matrix_Scale(0.01f, 0.01f, 0.01f, 1);
        SysMatrix_CopyCurrentState(&this->unk_6A4);
        if (this->unk_2EE == 0) {
            Camera_AddQuake(GET_ACTIVE_CAM(play), 2, 4, 6);
            Rumble_Request(this->actor.xyzDistToPlayerSq, 0xB4, 0x14, 0x64);
            AudioSfx_StopByPosAndId(&this->unk_338, 0x3AAE);
            Audio_PlaySfx_AtPos(&this->unk_338, 0x3AAF);
        }
    }
    if (this->unk_2EE < -0x19) {
        play->envCtx.lightSettingOverride = 0x14;
        func_808C74A4(this);
    }
}

void func_808C74A4(EnDeath* this) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_6E4); i++) {
        this->unk_6E4[i]->params = 5;
    }

    this->unk_2EE = 0;
    this->unk_188 = func_808C74F8;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C74F8.s")

void func_808C7800(EnDeath* this) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_1A9); i++) {
        this->unk_1A9[i] = 0;
    }

    Math_Vec3f_Copy(&this->actor.world.pos, &this->actor.focus.pos);
    this->actor.bgCheckFlags &= 0xFFFE;
    this->unk_2EE = 0;
    this->unk_188 = func_808C7888;
    this->actor.gravity = -1.0f;
    this->actor.shape.yOffset = 0.0f;
}

#ifdef NON_MATCHING
// needs in-function static D_808C9ABC
void func_808C7888(EnDeath* this, PlayState* play) {
    Vec3f sp74;
    s32 i;

    if (this->unk_2EE == 0) {
        if ((this->actor.bgCheckFlags & 1) || this->actor.floorHeight == -32000.0f) {
            Actor_SetScale(&this->actor, 0.0f);
            this->unk_2EE++;

            for (i = 0; i < 40; i++) {
                D_808C9ABC.y = -0.2f;
                sp74.x = Rand_CenteredFloat(4.0f);
                sp74.y = Rand_CenteredFloat(4.0f);
                sp74.z = Rand_ZeroFloat(2.0f) + 3.0f;
                EffectSsKirakira_SpawnSmall(play, &this->actor.world.pos, &sp74, &D_808C9ABC, &D_808C9AC8,
                                            &D_808C9ACC);
            }
            Actor_PlaySfx(&this->actor, 0x3AB5);
        }
    } else {
        this->unk_2EE++;
        if (this->unk_2EE == 20) {
            func_808C7A30(this, play);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C7888.s")
#endif

void func_808C7A30(EnDeath* this, PlayState* play) {
    CutsceneManager_Stop(this->actor.csId);
    Player_SetCsAction(play, &this->actor, 6);
    Flags_SetClearTemp(play, play->roomCtx.curRoom.num);
    this->unk_2EE = 0xFF;
    play->envCtx.lightSettingOverride = 0xFF;
    this->unk_188 = func_808C7AAC;
}

void func_808C7AAC(EnDeath* this, PlayState* play) {
    if (this->unk_2EE > 0) {
        this->unk_2EE -= 5;
        if (this->unk_2EE <= 0) {
            this->unk_2EE = 0;
            Actor_Kill(&this->actor);
        }
    }
}

void func_808C7AEC(EnDeath* this) {
    s32 i;

    Actor_PlaySfx(&this->actor, 0x3AB0);
    Animation_MorphToPlayOnce(&this->skelAnime, &D_060015B4, 5.0f);
    this->actor.speed = 0.0f;

    for (i = 0; i < ARRAY_COUNT(this->unk_6E4); i++) {
        this->unk_6E4[i]->params = 3;
    }

    this->unk_2EA = 0;
    this->unk_188 = func_808C7B88;
}

void func_808C7B88(EnDeath* this, PlayState* play) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 8, 0x1000, 0x100);
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y, 5.0f);
    if (SkelAnime_Update(&this->skelAnime)) {
        play->envCtx.lightSettingOverride = 0x1B;
        func_808C7C04(this);
    }
}

void func_808C7C04(EnDeath* this) {
    s32 i;

    Animation_PlayLoop(&this->skelAnime, &D_06001834);

    for (i = 0; i < ARRAY_COUNT(this->unk_6E4); i++) {
        this->unk_6E4[i]->params = 4;
    }

    this->unk_188 = func_808C7C88;
    this->actor.speed = 0.0f;
}

void func_808C7C88(EnDeath* this, PlayState* play) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 8, 0x1000, 0x100);
    SkelAnime_Update(&this->skelAnime);
    if (this->actor.params >= 5) {
        play->envCtx.lightSettingOverride = 0x1A;
        func_808C645C(this);
    }
}

void func_808C7CFC(EnDeath* this) {
    CutsceneManager_Queue(this->actor.csId);
    this->unk_188 = func_808C7D34;
}

void func_808C7D34(EnDeath* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->actor.csId)) {
        CutsceneManager_Start(this->actor.csId, &this->actor);
        this->unk_2FA = CutsceneManager_GetCurrentSubCamId(this->actor.csId);
        if (this->actor.colChkInfo.health == 0) {
            func_808C6D40(this, play);
        } else {
            func_808C571C(this, play);
        }
    } else {
        CutsceneManager_Queue(this->actor.csId);
    }
}

void func_808C7DB8(EnDeath* this) {
    this->unk_188 = func_808C7DCC;
}

void func_808C7DCC(EnDeath* this, PlayState* play) {
    if (Play_InCsMode(play) == 0) {
        func_808C5310(play);
        this->unk_808.base.acFlags |= 1;
        Audio_PlayBgm_StorePrevBgm(0x38);
        func_808C645C(this);
    }
}

void func_808C7E24(EnDeath* this, PlayState* play) {
    if (this->unk_18D != 0) {
        this->unk_320.y += this->unk_308;
        this->unk_308 -= 1.0f;
        this->unk_2F6 += 0x1800;
        if (this->unk_320.y < this->actor.floorHeight) {
            this->unk_320.y = this->actor.floorHeight;
            func_800B3030(play, &this->unk_320, &gZeroVec3f, &gZeroVec3f, 0x64, 0, 0);
            SoundSource_PlaySfxAtFixedWorldPos(play, &this->unk_320, 0xB, 0x3878);
            this->unk_18D = 0;
        }
    }
}

void func_808C7EDC(EnDeath* this, PlayState* play) {
    s32 i;

    if (this->unk_2F8 > 0) {
        this->unk_2F8--;
    }
    if (this->unk_808.base.acFlags & 2) {
        this->unk_808.base.acFlags &= 0xFFFD;

        if (this->actor.params >= 5) {
            this->unk_18D = 1;
            this->unk_308 = -1.0f;
            this->unk_2F6 = this->actor.shape.rot.y;
            Math_Vec3s_ToVec3f(&this->unk_320, &this->unk_808.dim.worldSphere.center);
            SoundSource_PlaySfxAtFixedWorldPos(play, &this->unk_320, 0x1E, 0x3842);

            if (this->actor.colChkInfo.damageEffect == 4 && this->unk_188 != func_808C7B88) {
                for (i = 0; i < ARRAY_COUNT(this->unk_6E4); i++) {
                    this->unk_6E4[i]->params = 1;
                }
                play->envCtx.lightSettingOverride = 0x1C;

                this->unk_2FC = 0x14;
                if (this->unk_188 == func_808C64DC) {
                    this->unk_2EE = 0x64;
                }
            } else if (this->actor.colChkInfo.damageEffect == 0xF) {
                this->unk_2F8 = 0xA;
            }
        } else if (this->actor.colChkInfo.damageEffect != 0xF || this->unk_2F8 == 0) {
            this->unk_18C = 0;
            this->unk_788.base.atFlags &= 0xFFFE;
            this->unk_808.base.acFlags &= 0xFFFE;

            if (this->actor.colChkInfo.damageEffect == 4) {
                this->unk_31C = 3.0f;
                this->unk_314 = 0.8f;
                this->unk_18F = 0x14;
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_CLEAR_TAG, this->unk_808.info.bumper.hitPos.x,
                            this->unk_808.info.bumper.hitPos.y, this->unk_808.info.bumper.hitPos.z, 0, 0, 0, 4);
            }
            if (play->envCtx.lightSettingOverride == 0x1B) {
                play->envCtx.lightSettingOverride = 0x1A;
            }
            this->actor.shape.rot.x = 0;

            if (Actor_ApplyDamage(&this->actor) == 0) {
                Enemy_StartFinishingBlow(play, &this->actor);
                Audio_RestorePrevBgm();
                func_808C7CFC(this);
            } else {
                for (i = 0; i < ARRAY_COUNT(this->unk_6E4); i++) {
                    this->unk_6E4[i]->params = 2;
                }

                func_808C6C5C(this);
            }
        }
    }
}

void EnDeath_Update(Actor* thisx, PlayState* play) {
    EnDeath* this = THIS;
    UnkActor* unkActor;
    s32 pad;

    if (this->unk_2FC > 0) {
        this->unk_2FC--;
        unkActor = (UnkActor*)SubS_FindActor(play, NULL, 7, 0x7F);
        if (unkActor != NULL) {
            unkActor->unk_15C = -100.0f;
        }
        if (this->unk_2FC == 0) {
            play->envCtx.lightSettingOverride = 0x1A;
        }
    }
    func_808C7EDC(this, play);
    func_808C7E24(this, play);
    if (this->unk_188 != func_808C6AB0) {
        Math_ScaledStepToS(&this->unk_2F2, 0, 0x800);
        Math_ScaledStepToS(&this->unk_2F4, 0, 0x800);
    }
    this->unk_188(this, play);

    if (this->unk_188 != func_808C6CDC) {
        this->actor.world.rot.y = this->actor.shape.rot.y;
    }
    Actor_MoveWithGravity(&this->actor);

    Actor_UpdateBgCheckInfo(play, &this->actor, 40.0f, (this->unk_188 == func_808C6AB0) ? 50.0f : 100.0f, 40.0f,
                            7);

    this->unk_73C.dim.pos.x = this->actor.world.pos.x + Math_SinS(this->actor.shape.rot.y) * 3.0f;
    this->unk_73C.dim.pos.z = this->actor.world.pos.z + Math_CosS(this->actor.shape.rot.y) * 3.0f;
    this->unk_73C.dim.pos.y = this->actor.world.pos.y;

    if (this->actor.params < 5) {
        this->unk_808.dim.worldSphere.radius = this->unk_808.dim.modelSphere.radius + 5;
    } else {
        this->unk_808.dim.worldSphere.radius = this->unk_808.dim.modelSphere.radius;
    }

    if (this->unk_188 != func_808C7AAC) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->unk_73C.base);
    }
    if (this->unk_808.base.acFlags & 1) {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_808.base);
    }
    if (this->unk_788.base.atFlags & 1) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk_788.base);
    }
    if (this->unk_188 == func_808C692C || this->unk_188 == func_808C6AB0) {
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->unk_860.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk_860.base);
    }

    if (this->unk_31C > 0.0f) {
        if (this->unk_18F != 0xA) {
            Math_StepToF(&this->unk_31C, 0.0f, 0.05f);
            this->unk_314 = (this->unk_31C + 1.0f) * 0.4f;

            this->unk_314 = CLAMP_MAX(this->unk_314, 0.8f);

            return;
        }
        if (Math_StepToF(&this->unk_318, 0.8f, 0.02f) == 0) {
            Actor_PlaySfx_Flagged(&this->actor, 0x20B2);
        }
    }
}

#ifdef NON_MATCHING
// single reodering, stack
void func_808C84A4(EnDeath* this, PlayState* play) {
    Gfx* phi_s0;
    s32 phi_s2;
    s32 phi_s3;
    s32 phi_s4;

    func_800B8118(&this->actor, play, 0);
    Scene_SetRenderModeXlu(play, 1, 2);

    OPEN_DISPS(play->state.gfxCtx);

    phi_s0 = POLY_XLU_DISP;

    for (phi_s2 = 1, phi_s3 = 0xDC, phi_s4 = 0x2100; phi_s2 < this->unk_190;
         phi_s2++, phi_s3 -= 0x23, phi_s4 += 0x2100) {
        gDPPipeSync(phi_s0++);
        gDPSetEnvColor(phi_s0++, 30, 30, 0, phi_s3);

        SysMatrix_SetCurrentState(&this->unk_6A4);
        SysMatrix_InsertXRotation_s(phi_s4, 1);

        gSPMatrix(phi_s0++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(phi_s0++, D_06006F88);

        SysMatrix_InsertTranslation(0.0f, -1084.0f, 7012.0f, 1);
        SysMatrix_InsertRotation(-0x4000, 0, -0x4000, 1);

        gSPMatrix(phi_s0++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(phi_s0++, D_060073D0);
    }
    POLY_XLU_DISP = phi_s0;

    CLOSE_DISPS(play->state.gfxCtx);
}
#else
void func_808C84A4(EnDeath* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C84A4.s")
#endif

void func_808C8690(EnDeath* this, PlayState* play) {
    Gfx* dl;
    s32 pad;

    if (this->unk_188 == func_808C7AAC) {
        func_800B8118(&this->actor, play, 0);
        Scene_SetRenderModeXlu(play, 1, 2);
    }

    OPEN_DISPS(play->state.gfxCtx);

    if (this->unk_188 == func_808C7AAC) {
        dl = POLY_XLU_DISP;

        gDPPipeSync(dl++);
        gDPSetEnvColor(dl++, 30, 30, 0, this->unk_2EE);
    } else {
        dl = POLY_OPA_DISP;
    }

    SysMatrix_SetCurrentState(&this->unk_6A4);
    Matrix_Scale(this->unk_304, this->unk_304, this->unk_304, 1);

    gSPMatrix(&dl[0], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dl[1], D_06006F88);

    SysMatrix_InsertTranslation(0.0f, -1084.0f, 7012.0f, 1);
    SysMatrix_InsertRotation(-0x4000, 0, -0x4000, 1);

    gSPMatrix(&dl[2], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dl[3], D_060073D0);

    SysMatrix_GetStateTranslation(&this->unk_32C);

    if (this->unk_188 == func_808C7AAC) {
        POLY_XLU_DISP = &dl[4];
    } else {
        POLY_OPA_DISP = &dl[4];
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_808C882C(EnDeath* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C882C.s")

void func_808C8D18(EnDeath* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C8D18.s")

void func_808C9160(EnDeath* this, PlayState* play) {
    s32 pad;
    Gfx* dl;

    OPEN_DISPS(play->state.gfxCtx);

    dl = POLY_OPA_DISP;
    SysMatrix_NormalizeXYZ(&play->billboardMtxF);

    gSPMatrix(&dl[0], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(&dl[1], D_06009988);

    if (this->actor.params >= 5) {
        gSPDisplayList(&dl[2], D_06009BA0);
        POLY_OPA_DISP = dl + 3;
    } else {
        POLY_OPA_DISP = dl + 2;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

s32 func_808C9220(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDeath* this = THIS;
    f32 temp_f12;
    s32 temp_v0;

    if (this->unk_193[limbIndex] == 1) {
        *dList = NULL;
    } else if (limbIndex == 0xD && this->unk_188 == func_808C74F8) {
        temp_v0 = this->unk_2EE - 5;
        if (temp_v0 > 0) {
            temp_f12 = 1.0f - (temp_v0 * 0.1f);
            Matrix_Scale(temp_f12, temp_f12, temp_f12, 1);
        }
    }
    if (limbIndex == 0x14 || limbIndex == 0x15) {
        if (this->unk_18E == 0) {
            *dList = NULL;
        }
    } else if (limbIndex == 0xC) {
        rot->z = rot->z + this->unk_2F2;
    } else if (limbIndex == 0xD) {
        rot->z = rot->z + this->unk_2F4;
    }
    return 0;
}

#ifdef NON_MATCHING
// A lot towards the bottom, original wants to mult but mine optimizes to shifts
void func_808C9340(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDeath* this = THIS;
    Vec3f sp6C;
    Vec3f sp60;
    Vec3f sp54;
    Vec3f sp48;
    s32 sp44;
    f32 temp_f0;
    s32 temp_s0;
    s32 temp_v0_2;
    s8 temp_v1;
    s32 phi_v0;
    Vec3f* phi_s1;
    Vec3f* phi_s0;

    if (limbIndex == 0x15) {
        SysMatrix_GetStateTranslation(&this->unk_32C);
        if ((this->unk_788.base.atFlags & 1) && this->unk_2EC != this->unk_2EE) {
            Math_Vec3f_Copy(&sp6C, &this->unk_788.dim.quad[0]);
            Math_Vec3f_Copy(&sp60, &this->unk_788.dim.quad[1]);
            if (this->unk_188 == func_808C682C) {
                SysMatrix_GetStateTranslationAndScaledX(6000.0f, &sp54);
                SysMatrix_MultiplyVector3fByState(&D_808C9AF4, &sp48);
            } else {
                SysMatrix_GetStateTranslationAndScaledY(5000.0f, &sp48);
                SysMatrix_MultiplyVector3fByState(&D_808C9B00, &sp54);
            }
            Collider_SetQuadVertices(&this->unk_788, &sp48, &sp54, &sp6C, &sp60);
            EffectBlure_AddVertex(Effect_GetByIndex(this->unk_300), &sp54, &sp48);
            this->unk_2EC = this->unk_2EE;
        } else if (this->unk_18C != 0) {
            if (this->unk_188 == func_808C682C) {
                Matrix_MultVecX(6000.0f, &this->unk_788.dim.quad[1]);
                Matrix_MultVec3f(&D_808C9AF4, &this->unk_788.dim.quad[0]);
            } else {
                Matrix_MultVecY(5000.0f, &this->unk_788.dim.quad[0]);
                Matrix_MultVec3f(&D_808C9B00, &this->unk_788.dim.quad[1]);
            }
            this->unk_18C = 0;
            this->unk_788.base.atFlags |= 1;
            this->unk_2EC = this->unk_2EE;
        }
    } else if (limbIndex == 2 && this->unk_188 != func_808C7AAC) {
        SysMatrix_StatePush();
        func_808C9160(this, play);
        Matrix_Pop();
        Matrix_MultZero(&this->actor.focus.pos);
        this->unk_808.dim.worldSphere.center.x = this->actor.focus.pos.x;
        this->unk_808.dim.worldSphere.center.y = this->actor.focus.pos.y;
        this->unk_808.dim.worldSphere.center.z = this->actor.focus.pos.z;
        if (this->actor.params < 5) {
            this->unk_808.dim.worldSphere.center.y = this->actor.focus.pos.y + 5.0f;
        }
    } else if (limbIndex == 0x14) {
        if (!(this->unk_188 != func_808C6AB0 && this->unk_188 != func_808C692C && this->unk_188 != func_808C6070) ||
            (this->unk_188 == func_808C6F6C && this->unk_18E == 1)) {
            SysMatrix_CopyCurrentState(&this->unk_6A4);
        }
    }
    temp_v1 = D_808C9B48[limbIndex];
    if (temp_v1 != -1) {
        if (temp_v1 < 7) {
            SysMatrix_GetStateTranslation(&this->unk_35C[temp_v1]);
            return;
        }
        if (temp_v1 == 7) {
            for (phi_v0 = 0; phi_v0 != 5; phi_v0++) {
                SysMatrix_MultiplyVector3fByState(&D_808C9B0C[phi_v0], &this->unk_35C[phi_v0 + temp_v1]);
            }
            return;
        }
        if (temp_v1 == 0xC) {
            SysMatrix_GetStateTranslation(&this->unk_35C[temp_v1]);
            SysMatrix_GetStateTranslationAndScaledY(-2000.0f, &this->unk_35C[temp_v1 + 1]);
        }
    }
}
#else
void func_808C9340(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Death/func_808C9340.s")
#endif

void EnDeath_Draw(Actor* thisx, PlayState* play) {
    EnDeath* this = THIS;
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    func_800B8050(&this->actor, play, 0);
    AnimatedMat_DrawStepOpa(play, this->unk_734, this->unk_191);
    AnimatedMat_DrawOpa(play, this->unk_738);
    Scene_SetRenderModeXlu(play, 0, 1);

    gDPSetEnvColor(POLY_OPA_DISP++, 30, 30, 0, 255);

    if (this->unk_188 != func_808C7AAC && this->unk_188 != func_808C7888) {
        SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                         func_808C9220, func_808C9340, &this->actor);
    }
    if (this->unk_188 == func_808C7888) {
        func_808C9160(this, play);
    }
    if (this->unk_18E == 0) {
        func_808C8690(this, play);
    }
    if (this->actor.colorFilterTimer != 0) {
        func_800AE5A0(play);
    }
    Actor_DrawDamageEffects(play, &this->actor, this->unk_35C, 0xE, this->unk_314, this->unk_318, this->unk_31C, this->unk_18F);
    if (this->unk_188 == func_808C6AB0 || this->unk_188 == func_808C692C) {
        func_808C84A4(this, play);
    }
    func_808C882C(this, play);
    if (this->unk_188 == func_808C7AAC || this->unk_188 == func_808C7888 ||
        (this->unk_188 == func_808C74F8 && this->unk_2EE > 0)) {
        func_808C8D18(this, play);
    }
    SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &this->unk_32C, &this->unk_338);

    CLOSE_DISPS(play->state.gfxCtx);
}
