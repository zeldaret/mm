/*
 * File: z_en_bigokuta.c
 * Overlay: ovl_En_Bigokuta
 * Description: Big Octo
 */

#include "z_en_bigokuta.h"

#define FLAGS 0x00000005

#define THIS ((EnBigokuta*)thisx)

void EnBigokuta_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AC28B4(EnBigokuta* this, GlobalContext* globalCtx, Vec3f* at, Vec3f* eye);
void func_80AC299C(EnBigokuta* this, GlobalContext* globalCtx);
// void func_80AC2A7C(EnBigokuta *this, GlobalContext *globalCtx);
void func_80AC2B4C(GlobalContext* globalCtx, Actor* arg1);
s32 func_80AC2B98(EnBigokuta* this, GlobalContext* globalCtx);
// void func_80AC2C30(EnBigokuta *this, GlobalContext *globalCtx);
void func_80AC2C84(EnBigokuta* this);
void func_80AC2CE8(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC2DAC(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC2EBC(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC2F20(EnBigokuta* this);
void func_80AC2F64(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC30EC(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC31EC(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC33A4(EnBigokuta* this);
void func_80AC33C0(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC3460(EnBigokuta* this);
void func_80AC34A8(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC35E8(EnBigokuta* this);
void func_80AC3650(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC39A0(EnBigokuta* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bigokuta_InitVars = {
    ACTOR_EN_BIGOKUTA,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGOKUTA,
    sizeof(EnBigokuta),
    (ActorFunc)EnBigokuta_Init,
    (ActorFunc)EnBigokuta_Destroy,
    (ActorFunc)EnBigokuta_Update,
    (ActorFunc)EnBigokuta_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AC4530 = {
    { COLTYPE_HARD, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFC74F, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 75, 125, 0, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AC455C = {
    { COLTYPE_HIT0, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x000038B0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 70, 125, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80AC4588 = { 4, 130, 120, MASS_HEAVY };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AC4590[] = {
    ICHAIN_F32(uncullZoneForward, 2500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 89, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 33, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80AC4530;
extern ColliderCylinderInit D_80AC455C;
extern CollisionCheckInfoInit D_80AC4588;
extern InitChainEntry D_80AC4590[];

extern AnimationHeader D_06000444;
extern AnimationHeader D_06000A74;
extern AnimationHeader D_060014B8;
extern FlexSkeletonHeader D_06006BC0;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Init.s")
void EnBigokuta_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBigokuta* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80AC4590);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_06006BC0, &D_060014B8, this->jointTable, this->morphTable, 0x14);
    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &D_80AC4530);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &D_80AC455C);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &D_80AC4588);
    this->cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
    if ((gSaveContext.weekEventReg[20] & 2) ||
        ((this->actor.params != 0xFF) && (Flags_GetSwitch(globalCtx, this->actor.params)))) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.world.pos.y -= 99.0f;
        func_80AC2C84(this);
    }
    this->unk_2AC.x = ((Math_SinS(this->actor.home.rot.y) * 66.0f) + this->actor.world.pos.x);
    this->unk_2AC.y = ((this->actor.home.pos.y - 49.5f) + 42.899998f);
    this->unk_2AC.z = ((Math_CosS(this->actor.home.rot.y) * 66.0f) + this->actor.world.pos.z);
    this->unk_144 = func_80AC2B4C;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Destroy.s")
void EnBigokuta_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBigokuta* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC28B4.s")
/*void func_80AC28B4(EnBigokuta *this, GlobalContext *globalCtx, Vec3f *at, Vec3f *eye) {
    s16 phi_a0;

    ActorCutscene_Start(this->actor.cutscene, &this->actor);
    this->unk_194 = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
    Play_CameraSetAtEye(globalCtx, this->unk_194, at, eye);
    if ((Actor_YawToPoint(&this->actor, eye) - this->actor.home.rot.y) > 0) {
        phi_a0 = (this->actor.home.rot.y + 0x1800);
    } else {
        phi_a0 = (this->actor.home.rot.y - 0x1800);
    }
    this->unk_2B8.x = (Math_SinS(phi_a0) * 250.0f) + this->unk_2AC.x;
    this->unk_2B8.y = (this->unk_2AC.y + 100.0f);
    this->unk_2B8.z = (Math_CosS(phi_a0) * 250.0f) + this->unk_2AC.z;
}
*/

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC299C.s")
void func_80AC299C(EnBigokuta* this, GlobalContext* globalCtx) {
    Camera* camera = Play_GetCamera(globalCtx, this->unk_194);
    Math_Vec3f_StepTo(&camera->eye, &this->unk_2B8, 20.0f);
    Math_Vec3f_StepTo(&camera->at, &this->unk_2AC, 20.0f);
    Play_CameraSetAtEye(globalCtx, this->unk_194, &camera->at, &camera->eye);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2A1C.s")
void func_80AC2A1C(EnBigokuta* this, GlobalContext* globalCtx) {
    Camera* camera;

    if (this->unk_194 != 0) {
        camera = Play_GetCamera(globalCtx, this->unk_194);
        Play_CameraSetAtEye(globalCtx, 0, &camera->at, &camera->eye);
        this->unk_194 = 0;
        ActorCutscene_Stop(this->actor.cutscene);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2A7C.s")
void func_80AC2A7C(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
    if (&this->actor == player->actor.parent) {
        player->actor.parent = NULL;
        player->unk_AE8 = 100;
        player->actor.velocity.y = 0.0f;
        player->actor.world.pos.x += 20.0f * Math_SinS(this->actor.home.rot.y);
        player->actor.world.pos.z += 20.0f * Math_CosS(this->actor.home.rot.y);
        func_800B8D50(globalCtx, &this->actor, 10.0f, this->actor.home.rot.y, 10.0f, 4);
    }
    func_80AC2A1C(this, globalCtx);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2B4C.s")
void func_80AC2B4C(GlobalContext* globalCtx, Actor* actor) {
    func_8013A530(globalCtx, actor, 3, &actor->focus.pos, &actor->shape.rot, 280.0f, 1800.0f, -1);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2B98.s")
/*s32 func_80AC2B98(EnBigokuta *this, GlobalContext *globalCtx) {
    DynaWaterBoxList list;
    s32 phi_v0;

    this->actor.floorHeight = BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &this->actor.floorPoly,
    &list.unk0, &this->actor, &this->actor.world.pos);
    if ((WaterBox_GetSurface1_2(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
    &this->actor.home.pos.y, &list.boxes) == 0) || (this->actor.home.pos.y <= this->actor.floorHeight)) {
        phi_v0 = 0;
    } else {
        phi_v0 = 1;
    }
    return phi_v0;
}
*/

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2C30.s")
void func_80AC2C30(EnBigokuta* this, GlobalContext* globalCtx) {
    Vec3f ripple_pos;

    ripple_pos.x = this->actor.world.pos.x;
    ripple_pos.y = this->actor.home.pos.y;
    ripple_pos.z = this->actor.world.pos.z;
    EffectSsGRipple_Spawn(globalCtx, &ripple_pos, 1000, 1400, 0);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2C84.s")
void func_80AC2C84(EnBigokuta* this) {
    Animation_Change(&this->skelAnime, &D_060014B8, 0.5f, 0.0f, 0.0f, 1, -3.0f);
    this->actionFunc = func_80AC2CE8;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2CE8.s")
void func_80AC2CE8(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y - 99.0f, 2.5f);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000);
    if ((this->actor.xzDistToPlayer < 300.0f) && ((player->actor.world.pos.y - this->actor.home.pos.y) < 100.0f)) {
        func_80AC2DAC(this, globalCtx);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2DAC.s")
void func_80AC2DAC(EnBigokuta* this, GlobalContext* globalCtx) {
    Vec3f splash_pos;
    s32 i;
    s16 angle = 0;

    Animation_PlayOnce(&this->skelAnime, &D_06000444);
    splash_pos.y = this->actor.home.pos.y;
    for (i = 0; i < 8; i++) {
        splash_pos.x = (Math_SinS(angle) * 70.0f) + this->actor.world.pos.x;
        splash_pos.z = (Math_CosS(angle) * 70.0f) + this->actor.world.pos.z;
        EffectSsGSplash_Spawn(globalCtx, &splash_pos, NULL, NULL, 0, Rand_S16Offset(1000, 200));
        angle = BINANG_ADD(angle, 0x2000);
    }
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIOCTA_LAND);
    this->actionFunc = func_80AC2EBC;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2EBC.s")
void func_80AC2EBC(EnBigokuta* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y - 16.5f, 15.0f);
    if (SkelAnime_Update(&this->skelAnime)) {
        func_80AC2F20(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2F20.s")
void func_80AC2F20(EnBigokuta* this) {
    Animation_MorphToLoop(&this->skelAnime, &D_060014B8, -5.0f);
    this->actionFunc = func_80AC2F64;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC2F64.s")
void func_80AC2F64(EnBigokuta* this, GlobalContext* globalCtx) {

    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y - 16.5f, 2.5f);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000);
    if ((this->actor.xzDistToPlayer > 400.0f) || (this->actor.playerHeightRel > 200.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIOCTA_SINK);
        func_80AC2C84(this);
    } else if ((this->actor.xzDistToPlayer < 200.0f) &&
               (globalCtx->grabPlayer(globalCtx, GET_PLAYER(globalCtx)) != 0)) {
        func_80AC30EC(this, globalCtx);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3054.s")
void func_80AC3054(EnBigokuta* this, GlobalContext* globalCtx) {
    Camera* camera;

    if (this->actor.cutscene != -1) {
        if (this->unk_194 != 0) {
            func_80AC299C(this, globalCtx);
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            camera = Play_GetCamera(globalCtx, 0);
            func_80AC28B4(this, globalCtx, &camera->at, &camera->eye);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC30EC.s")
void func_80AC30EC(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
    player->actor.parent = &this->actor;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    Math_Vec3f_Copy(&this->unk_294, &player->actor.world.pos);
    this->unk_192 = 0;
    Animation_Change(&this->skelAnime, &D_060014B8, 1.0f, 12.0f, 12.0f, 2, -3.0f);
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    this->unk_2A0.x = ((Math_SinS(this->actor.shape.rot.y) * 66.0f) + this->actor.world.pos.x);
    this->unk_2A0.y = ((this->actor.home.pos.y - 49.5f) + 42.899998f);
    this->unk_2A0.z = ((Math_CosS(this->actor.shape.rot.y) * 66.0f) + this->actor.world.pos.z);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_SLIME_DEAD);
    this->actionFunc = func_80AC31EC;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC31EC.s")
/*void func_80AC31EC(EnBigokuta *this, GlobalContext *globalCtx) {
    Player *player;
    s16 sp3A;

    player = GET_PLAYER(globalCtx);
    func_80AC3054(this, globalCtx);
    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y - 49.5f, 10.0f);
    if (this->unk_192 < 9) {
        this->unk_192++;
    }
    player->unk_AE8 = 0;
    Math_Vec3f_Copy(&player->actor.world.pos, &this->unk_294);
    if (Math_Vec3f_StepTo(&player->actor.world.pos, &this->unk_2A0, sqrtf(this->unk_192) * 5.0f) < 0.1f) {
        sp3A = this->actor.shape.rot.y;
        if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x800)) {
            func_80AC33A4(this);
        }
        this->unk_2A0.x = (Math_SinS(this->actor.shape.rot.y) * 66.0f) + this->actor.world.pos.x;
        this->unk_2A0.y = (this->actor.home.pos.y - 49.5f) + 42.899998f;
        this->unk_2A0.z = (Math_CosS(this->actor.shape.rot.y) * 66.0f) + this->actor.world.pos.z;
        Math_Vec3f_Copy(&player->actor.world.pos, &this->unk_2A0);
        Math_Vec3f_Copy(&this->unk_294, &player->actor.world.pos);
        player->actor.shape.rot.y += BINANG_SUB(this->actor.shape.rot.y, sp3A);
    } else {
        Math_Vec3f_Copy(&this->unk_294, &player->actor.world.pos);
        player->actor.velocity.y = 0.0f;
    }
}
*/

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC33A4.s")
void func_80AC33A4(EnBigokuta* this) {
    this->unk_192 = 0xC;
    this->actionFunc = func_80AC33C0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC33C0.s")
void func_80AC33C0(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player;

    player = GET_PLAYER(globalCtx);
    this->unk_192--;
    if (this->unk_192 >= 0) {
        func_80AC3054(this, globalCtx);
        Math_Vec3f_Copy(&player->actor.world.pos, &this->unk_2A0);
        if (this->unk_192 == 0) {
            func_80AC2A7C(this, globalCtx);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIOCTA_REVERSE);
        }
    } else if (this->unk_192 == -0x18) {
        func_80AC2F20(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3460.s")
void func_80AC3460(EnBigokuta* this) {
    ActorCutscene_SetIntentToPlay(this->cutscene);
    this->unk_192 = 0;
    this->collider2.base.acFlags &= ~1;
    this->actionFunc = func_80AC34A8;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC34A8.s")
void func_80AC34A8(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player;

    this->actor.colorFilterTimer = Animation_GetLastFrame(&D_06000A74);
    if (this->unk_192 != 0) {
        this->unk_192--;
        if (this->unk_192 == 0) {
            this->unk_190 = 0;
            this->unk_288.x = 0.0f;
            func_800BF7CC(globalCtx, &this->actor, this->limbPos, 0xD, 2, 0.5f, 0.35f);
            func_80AC35E8(this);
        }
    } else if (ActorCutscene_GetCanPlayNext(this->cutscene) != 0) {
        ActorCutscene_Start(this->cutscene, &this->actor);
        if ((!(gSaveContext.eventInf[4] & 2)) && (!(gSaveContext.eventInf[3] & 0x20))) {
            func_800B724C(globalCtx, &this->actor, 7U);
        } else {
            player = GET_PLAYER(globalCtx);
            player->stateFlags1 |= 0x20;
        }

        if (this->unk_190 == 0xA) {
            this->unk_192 = 3;
            return;
        } else {
            func_80AC35E8(this);
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->cutscene);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC35E8.s")
void func_80AC35E8(EnBigokuta* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &D_06000A74, -5.0f);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIOCTA_DEAD2);
    this->actor.flags &= -2;
    this->unk_192 = 0xA;
    this->actionFunc = func_80AC3650;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3650.s")
extern Vec3f D_80AC45A4;
extern Color_RGBA8 D_80AC45B0;
extern Color_RGBA8 D_80AC45B4;
extern Color_RGBA8 D_80AC45B8;

/*void func_80AC3650(EnBigokuta *this, GlobalContext *globalCtx) {
    s32 phi_s0;
    Player *player;
    Vec3f sp84;
    Vec3f sp74;
    Vec3f sp68;

    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.world.pos.y -= 0.2f;
        if (this->unk_192 > 0) {
            this->unk_192--;
            if (this->unk_192 == 6) {
                sp84.x = this->actor.world.pos.x;
                sp84.y = this->actor.world.pos.y + 150.0f;
                sp84.z = this->actor.world.pos.z;
                func_800B0DE0(globalCtx, &sp84, &D_801D15B0, &D_801D15B0, &D_80AC45B0, &D_80AC45B4, 0x4B0, 0x14);
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_OCTAROCK_DEAD2);
            }
        } else {
            this->actor.world.pos.y -= 0.2f;
            if (Math_StepToF(&this->actor.scale.y, 0.001f, 0.001f)) {
                Audio_PlaySoundAtPosition(globalCtx, &this->actor.world.pos, 0x32, NA_SE_EN_COMMON_WATER_MID);
                sp68.y = this->actor.world.pos.y;
                /*do {
                    sp74.x = randPlusMinusPoint5Scaled(10.0f);
                    sp74.y = Rand_ZeroFloat(5.5f) + 5.5f;
                    temp_f0 = randPlusMinusPoint5Scaled(10.0f);
                    sp74.z = temp_f0;
                    sp68.x = this->actor.world.pos.x + (2.0f * sp74.x);
                    sp68.z = this->actor.world.pos.z + (2.0f * temp_f0);
                    EffectSsDtBubble_SpawnCustomColor(globalCtx, &sp68, &sp74, &D_80AC45A4, &D_80AC45B0, &D_80AC45B8,
Rand_S16Offset(0x96, 0x32), 0x19, 0); temp_s0 = phi_s0 + 1; phi_s0 = temp_s0; } while (temp_s0 != 0x14); * for (phi_s0 =
0; phi_s0 < 0x14; phi_s0++) { sp74.x = randPlusMinusPoint5Scaled(10.0f); sp74.y = Rand_ZeroFloat(5.5f) + 5.5f; sp74.z =
randPlusMinusPoint5Scaled(10.0f); sp68.x = this->actor.world.pos.x + (2.0f * sp74.x); sp68.z = this->actor.world.pos.z +
(2.0f * sp74.z); EffectSsDtBubble_SpawnCustomColor(globalCtx, &sp68, &sp74, &D_80AC45A4, &D_80AC45B0, &D_80AC45B8,
Rand_S16Offset(0x96, 0x32), 0x19, 0);
                }
                if (this->actor.params != 0xFF) {
                    Actor_SetSwitchFlag(globalCtx, this->actor.params);
                }
                ActorCutscene_Stop(this->cutscene);
                Actor_MarkForDeath(&this->actor);
                if (((gSaveContext.eventInf[4] & 2) == 0) && ((gSaveContext.eventInf[3] & 0x20) == 0)) {
                    func_800B724C(globalCtx, &this->actor, 6);
                } else {
                    player = GET_PLAYER(globalCtx);
                    player->stateFlags1 &= ~0x20;
                }
            }
            if (this->unk_288.x > 0.0f) {
                this->unk_288.x = this->actor.scale.y * 30.30303f;
            }
        }
    } else {
        Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y - 16.5f, 15.0f);
    }
}
*/

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3930.s")
s32 func_80AC3930(EnBigokuta* this, GlobalContext* globalCtx) {
    this->actor.child = func_ActorCategoryIterateById(globalCtx, NULL, 1, ACTOR_BG_INGATE);
    if ((this->actor.child != NULL) && (Actor_XZDistanceBetweenActors(&this->actor, this->actor.child) < 250.0f)) {
        return 1;
    } else {
        return 0;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC39A0.s")
void func_80AC39A0(EnBigokuta* this, GlobalContext* globalCtx) {
    if ((this->collider2.base.acFlags & 1) &&
        ((this->collider2.base.acFlags & 2) ||
         (((globalCtx->sceneNum == 0x45) || (globalCtx->sceneNum == 0)) && (func_80AC3930(this, globalCtx))))) {
        Enemy_StartFinishingBlow(globalCtx, &this->actor);
        if (this->collider2.base.acFlags & 2) {
            if (this->collider2.info.acHitInfo->toucher.dmgFlags & 0x1000) {
                this->unk_190 = 0xA;
                this->unk_288.y = 1.2f;
                this->unk_288.z = 1.8000001f;
                this->unk_288.x = 1.0f;
            } else if (this->collider2.info.acHitInfo->toucher.dmgFlags & 0x2000) {
                this->unk_190 = 0x14;
                this->unk_288.y = 1.2f;
                this->unk_288.x = 4.0f;
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->collider2.info.bumper.hitPos.x,
                            this->collider2.info.bumper.hitPos.y, this->collider2.info.bumper.hitPos.z, 0, 0, 0, 4);
            }
        }
        this->collider2.base.acFlags &= ~2;
        func_800BCB70(&this->actor, 0x4000, 0xFF, 0, Animation_GetLastFrame(&D_06000A74));
        func_80AC2A7C(this, globalCtx);
        func_80AC3460(this);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Update.s")
/*void EnBigokuta_Update(Actor *thisx, GlobalContext *globalCtx) {
    EnBigokuta *this = THIS;
    f32 temp_f0;

    if (!func_80AC2B98(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if ((globalCtx->gameplayFrames % 7) == 0) {
        func_80AC2C30(this, globalCtx);
    }
    func_80AC39A0(this, globalCtx);
    this->actionFunc(this, globalCtx);
    if (this->collider2.base.acFlags & 1) {
        this->collider1.dim.pos.x = ((Math_SinS(this->actor.shape.rot.y) * -20.0f) + this->actor.world.pos.x);
        this->collider1.dim.pos.y = this->actor.world.pos.y;
        this->collider1.dim.pos.z = ((Math_CosS(this->actor.shape.rot.y) * -20.0f) + this->actor.world.pos.z);
        this->collider2.dim.pos.x = this->collider1.dim.pos.x;
        this->collider2.dim.pos.y = this->collider1.dim.pos.y;
        this->collider2.dim.pos.z = this->collider1.dim.pos.z;
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        Actor_SetHeight(&this->actor, 82.5f);
    }
    if (this->unk_288.x > 0.0f) {
        if (this->unk_190 != 0xA) {
            Math_StepToF(&this->unk_288.x, 0.0f, 0.05f);
            temp_f0 = (this->unk_288.x + 1.0f) * 0.6f;
            if (temp_f0 > 1.2f) {
                this->unk_288.y = 1.2f;
            } else {
                this->unk_288.y = temp_f0;
            }
            //this->unk_288.y = CLAMP_MAX((this->unk_288.x + 1.0f) * 0.6f, 1.2f);
        } else if (!Math_StepToF(&this->unk_288.z, 1.2f, 0.030000001f)) {
            func_800B9010(&this->actor, 0x20B2U);
        }
    }
}
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC3D48.s")
/*s32 func_80AC3D48(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *actor, Gfx
**gfx) { EnBigokuta *this = (EnBigokuta*)actor; f32 temp_f0; f32 temp_f12_2; f32 temp_f2; f32 temp_f2_2; f32 temp_f12;
    s16 phi_v1;

    if (limbIndex == 0xA) {
        s32 phi_a3;
        if (this->actionFunc == func_80AC3650) {
            temp_f0 = Animation_GetLastFrame(&D_06000A74);
            phi_a3 = ((255.0f / temp_f0) * (temp_f0 - this->skelAnime.curFrame));
        } else {
            phi_a3 = 0xFF;
        }
        gDPPipeSync((*gfx)++);
        gDPSetEnvColor((*gfx)++, phi_a3, phi_a3, phi_a3, phi_a3);
        if (this->actionFunc == func_80AC31EC) {
            phi_v1 = (s16)(this->unk_192 * 6144.0f * (1.0f / 9.0f));
            rot->x -= phi_v1;
        } else if (this->actionFunc == func_80AC33C0) {
            if (this->unk_192 == 1) {
                phi_v1 = 0;
            } else if (this->unk_192 == 0) {
                phi_v1 = -0xC00;
            } else if (this->unk_192 > 0) {
                phi_v1 = 0x1800;
            } else {
                phi_v1 = ((this->unk_192 + 0x18) * 0.041666668f * -6144.0f);
            }
            rot->x -= phi_v1;
        }
    } else if (limbIndex == 0x11) {
        if (this->actionFunc == func_80AC3650) {
            if (this->unk_192 < 5) {
                Matrix_Scale(1.0f, 1.0f, (this->unk_192 * 0.2f * 0.25f) + 1.0f, 1);
            } else if (this->unk_192 < 8) {
                temp_f12 = (this->unk_192 - 5) * (1.0f / 12.0f);
                Matrix_Scale(1.0f + temp_f12, 1.0f + temp_f12, 1.25f - temp_f12, 1);
            } else {
                Matrix_Scale(1.25f - ((this->unk_192 - 8) * 0.125f), 1.25f - ((this->unk_192 - 8) * 0.125f), 1.0f, 1);
            }
        } else if (this->actionFunc == func_80AC31EC) {
            temp_f2 = sin_rad(this->unk_192 * (M_PI / 3.0f)) * 0.5f;
            Matrix_Scale(((this->unk_192 * (2.0f / 9.0f)) * (0.5f + temp_f2)) + 1.0f, ((this->unk_192 * (2.0f / 9.0f)) *
(0.5f - temp_f2)) + 1.0f, 1.0f - ((this->unk_192 * 0.3f) / 9.0f), 1); } else if (this->actionFunc == func_80AC33C0) { if
(this->unk_192 != 1) { if (this->unk_192 == 0) { Matrix_Scale(0.9f, 0.9f, 1.15f, 1); } else if (this->unk_192 > 0) {
                    temp_f2_2 = sin_rad(this->unk_192 * (M_PI / 3.0f)) * 0.5f;
                    Matrix_Scale(((0.5f + temp_f2_2) * 0.2f) + 1.0f, ((0.5f - temp_f2_2) * 0.2f) + 1.0f, 0.7f, 1);
                } else {
                    Matrix_Scale(1.0f - ((this->unk_192 + 0x18) * 0.2f * 0.041666668f), 1.0f - ((this->unk_192 + 0x18) *
0.2f * 0.041666668f), ((this->unk_192 + 0x18) * 0.3f * 0.041666668f) + 1.0f, 1);
                }
            }
        }
    }
    return 0;
}
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/func_80AC4204.s")
extern s8 D_80AC45BC[];
extern Vec3f D_80AC45D0[];
// extern ? D_80AC460C;
/*void func_80AC4204(GlobalContext *globalCtx, s32 limbIndex, Gfx **dList, Vec3s *rot, Actor *actor, Gfx **gfx) {
    EnBigokuta* this = (EnBigokuta*)actor;
    s32 temp_s0;
    s8 temp_v0 = D_80AC45BC[limbIndex];

    if (temp_v0 != -1) {
        if (temp_v0 < 6) {
            Matrix_GetStateTranslationAndScaledX(800.0f, &this->limbPos[temp_v0]);
        } else if (temp_v0 < 8) {
            Matrix_GetStateTranslation(&this->limbPos[temp_v0]);
        } else {
            for (temp_s0 = 0; temp_s0 < 5; temp_s0++) {
                Matrix_MultiplyVector3fByState(&D_80AC45D0[temp_s0], &this->limbPos[temp_s0]);
            }
        }
/*        phi_s0 = &D_80AC45D0;
        phi_s1 = actor + (temp_v0 * 0xC) + 0x2C4;
        do {
            Matrix_MultiplyVector3fByState(phi_s0, phi_s1);
            temp_s0 = phi_s0 + 0xC;
            phi_s0 = temp_s0;
            phi_s1 += 0xC;
        } while (temp_s0 != &D_80AC460C);
/    }
}
*/

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bigokuta/EnBigokuta_Draw.s")
s32 func_80AC3D48(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* actor,
                  Gfx** gfx); /* extern */
void func_80AC4204(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor,
                   Gfx** gfx); /* extern */

void EnBigokuta_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBigokuta* this = THIS;
    Gfx* gfx;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if ((this->actionFunc != func_80AC3650) || (this->unk_192 != 0)) {
        Scene_SetRenderModeXlu(globalCtx, 0, 1);
        gfx = POLY_OPA_DISP;
        gSPDisplayList(&gfx[0], &sSetupDL[0x96]);
        gDPSetEnvColor(&gfx[1], 255, 255, 255, 255);
        POLY_OPA_DISP =
            SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                               this->skelAnime.dListCount, func_80AC3D48, func_80AC4204, &this->actor, &gfx[2]);
    } else {
        Scene_SetRenderModeXlu(globalCtx, 1, 2);
        gfx = POLY_XLU_DISP;
        gSPDisplayList(&gfx[0], &sSetupDL[0x96]);
        gDPSetEnvColor(&gfx[1], 0, 0, 0, (this->actor.scale.y * 7727.273f));
        POLY_XLU_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, NULL, func_80AC4204, &this->actor, &gfx[2]);
    }
    func_800BE680(globalCtx, &this->actor, this->limbPos, 0xD, this->unk_288.y, this->unk_288.z, this->unk_288.x,
                  this->unk_190);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
