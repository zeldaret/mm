/*
 * File: z_bg_kin2_bombwall.c
 * Overlay: ovl_Bg_Kin2_Bombwall
 * Description: Ocean Spider House - Bombable Wall
 */
#include "z_bg_kin2_bombwall.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_10000000)

#define THIS ((BgKin2Bombwall*)thisx)

void BgKin2Bombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgKin2Bombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80B6E020(BgKin2Bombwall*, GlobalContext*);
void func_80B6E090(BgKin2Bombwall*, GlobalContext*);
void BgKin2Bombwall_SetupWait(BgKin2Bombwall*);
void BgKin2Bombwall_Wait(BgKin2Bombwall*, GlobalContext*);
void BgKin2Bombwall_SetupPlayCutscene(BgKin2Bombwall*);
void BgKin2Bombwall_PlayCutscene(BgKin2Bombwall*, GlobalContext*);
void BgKin2Bombwall_SetupEndCutscene(BgKin2Bombwall*);
void BgKin2Bombwall_EndCutscene(BgKin2Bombwall*, GlobalContext*);

extern Gfx D_06000128[];
extern Gfx D_060002C0[];
extern Gfx D_06000360[];
extern Gfx D_06000490[];

ActorInit Bg_Kin2_Bombwall_InitVars = {
    ACTOR_BG_KIN2_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Bombwall),
    (ActorFunc)BgKin2Bombwall_Init,
    (ActorFunc)BgKin2Bombwall_Destroy,
    (ActorFunc)BgKin2Bombwall_Update,
    (ActorFunc)BgKin2Bombwall_Draw,
};

ColliderCylinderInit D_80B6E6F0 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000008, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 60, 60, 0, { 0, 0, 0 } },
};

Color_RGBA8 D_80B6E71C = { 0xD2, 0xD2, 0xD2, 0xFF };
Color_RGBA8 D_80B6E720 = { 0x8C, 0x8C, 0x8C, 0xFF };

Vec3f D_80B6E724 = { 0.0f, 0.33f, 0.0f };

s8 D_80B6E730[] = { -0x3C, -0x22, -8, 0x12, 0x2C };
s16 D_80B6E738[] = { 0x19, 0x17, 0x15, 0x13, 0x11, 0xF, 0xD, 0xA };

InitChainEntry D_80B6E748[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 300, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

// suggested name: BgKin2Bombwall_HadNearbyACCollision
// The distance here actually matters:
// replacing 6400.0f by a distance too large makes the wall explode from a bomb quite far away.
s32 func_80B6E020(BgKin2Bombwall *this, GlobalContext *globalCtx) {
    Actor *bombwallCollider;

    if (this->collider.base.acFlags & 2) {
        bombwallCollider = this->collider.base.ac;
        if ((bombwallCollider != NULL) && 
            (Math3D_Vec3fDistSq(&this->dyna.actor.world.pos, &bombwallCollider->world.pos) < 6400.0f)) {
            return true;
        }
    }
    return false;
}

// first idea: with all the random numbers fetched, this is probably related to particle effects from slashing or
// blowing up
void func_80B6E090(BgKin2Bombwall* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f pos;
    Vec3f velocity;
    Vec3f spD8;
    Vec3f spCC;
    s32 j;
    s32 temp_s3;
    f32 temp_a0;
    s32 temp_s2;
    s16 phi_s0;
    s16 phi_s1;

    Matrix_RotateYS(this->dyna.actor.shape.rot.y, 0);

    for (i = 0, temp_s3 = 0; i < 6; i++) {
        temp_a0 = (i + 1) * 15.f;
        for (j = 0; j < ARRAY_COUNT(D_80B6E730); j++) {
            temp_s3++;
            temp_s3 &= 7;

            spD8.x = D_80B6E730[j] + (s32)(((u32)Rand_Next()) >> 0x1C);
            spD8.y = ((Rand_ZeroOne() - 0.5f) * 15.0f) + temp_a0;
            spD8.z = (Rand_ZeroOne() * 20.0f) - 10.0f;

            spCC.x = (2.0f * (Rand_ZeroOne() - 0.5f)) + (spD8.x * 0.018461538f);
            spCC.y = (Rand_ZeroOne() * 7.0f) + 4.0f;
            spCC.z = spD8.z * 0.3f;

            Matrix_MultVec3f(&spD8, &pos);
            Matrix_MultVec3f(&spCC, &velocity);

            pos.x += this->dyna.actor.world.pos.x;
            pos.y += this->dyna.actor.world.pos.y;
            pos.z += this->dyna.actor.world.pos.z;

            if (Rand_Next() % 4 == 0) {
                phi_s0 = 0x20;
            } else {
                phi_s0 = 0x40;
            }

            if (temp_s3 < 2 || Rand_Next() > 0) {
                phi_s0 |= 1;
                phi_s1 = 1;
                func_800B0E48(globalCtx, &pos, &gZeroVec3f, &D_80B6E724, &D_80B6E71C, &D_80B6E720,
                              (((u32)Rand_Next() >> 0x1B) + 0x46),
                              ((((u32)Rand_Next()) >> 0x1A) + 0x3C)); // for dust spawn
            } else {
                phi_s1 = 0;
            }
            EffectSsKakera_Spawn(globalCtx, &pos, &velocity, &pos, -0x226, phi_s0, 0x1E, 0, 0, D_80B6E738[temp_s3],
                                 phi_s1, 0, 0x32, -1, 0x1F5, D_06000128);
        }
    }
}

void BgKin2Bombwall_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgKin2Bombwall* this = (BgKin2Bombwall*)thisx;
    ColliderCylinder* bombwallCollider;

    Actor_ProcessInitChain(&this->dyna.actor, D_80B6E748);
    DynaPolyActor_Init((DynaPolyActor*)this, 0);
    bombwallCollider = &this->collider;
    Collider_InitCylinder(globalCtx, bombwallCollider);
    if (Flags_GetSwitch(globalCtx, this->dyna.actor.params & 0x7F) != 0) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }
    DynaPolyActor_LoadMesh(globalCtx, (DynaPolyActor*)this, (CollisionHeader*)&D_06000490);
    Collider_SetCylinder(globalCtx, bombwallCollider, &this->dyna.actor, &D_80B6E6F0);
    Collider_UpdateCylinder(&this->dyna.actor, bombwallCollider);
    Actor_SetFocus(&this->dyna.actor, 60.0f);
    BgKin2Bombwall_SetupWait(this);
}

void BgKin2Bombwall_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgKin2Bombwall* this = (BgKin2Bombwall*)thisx;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void BgKin2Bombwall_SetupWait(BgKin2Bombwall* arg0) {
    arg0->actionFunc = BgKin2Bombwall_Wait;
}

void BgKin2Bombwall_Wait(BgKin2Bombwall* arg0, GlobalContext* arg1) {
    if (func_80B6E020(arg0, arg1) != 0) { // checks if AC collision happened
        arg0->collider.base.acFlags &= 0xFFFD;
        ActorCutscene_SetIntentToPlay((s16)arg0->dyna.actor.cutscene);
        BgKin2Bombwall_SetupPlayCutscene(arg0);
        return;
    }
    CollisionCheck_SetAC(arg1, &arg1->colChkCtx, &arg0->collider.base);
}

void BgKin2Bombwall_SetupPlayCutscene(BgKin2Bombwall* arg0) {
    arg0->actionFunc = BgKin2Bombwall_PlayCutscene;
}

void BgKin2Bombwall_PlayCutscene(BgKin2Bombwall* arg0, GlobalContext* arg1) {
    if (ActorCutscene_GetCanPlayNext((s16)arg0->dyna.actor.cutscene) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields((s16)arg0->dyna.actor.cutscene, &arg0->dyna.actor);
        Flags_SetSwitch(arg1, arg0->dyna.actor.params & 0x7F);
        SoundSource_PlaySfxAtFixedWorldPos(arg1, &arg0->dyna.actor.world.pos, 0x3C, 0x2810U);
        func_800C62BC(arg1, &arg1->colCtx.dyna, arg0->dyna.bgId);
        arg0->dyna.actor.draw = NULL;
        func_80B6E090(arg0, arg1); // not sure yet, but takes care of the explosion effects and particles like dust.
        BgKin2Bombwall_SetupEndCutscene(arg0);
        return;
    }
    ActorCutscene_SetIntentToPlay((s16)arg0->dyna.actor.cutscene);
}

void BgKin2Bombwall_SetupEndCutscene(BgKin2Bombwall* arg0) {
    arg0->unk_1AC[0] = 0x28;
    arg0->actionFunc = BgKin2Bombwall_EndCutscene;
}

void BgKin2Bombwall_EndCutscene(BgKin2Bombwall* arg0, GlobalContext* arg1) {
    arg0->unk_1AC[0]--;
    if ((s32)arg0->unk_1AC[0] <= 0) {
        ActorCutscene_Stop((s16)arg0->dyna.actor.cutscene);
        Actor_MarkForDeath(&arg0->dyna.actor);
    }
}

void BgKin2Bombwall_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgKin2Bombwall* this = (BgKin2Bombwall*)thisx;
    this->actionFunc(this, globalCtx);
}

void BgKin2Bombwall_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgKin2Bombwall* this = (BgKin2Bombwall*)thisx;
    Gfx_DrawDListOpa(globalCtx, (Gfx*)&D_06000360);
    Gfx_DrawDListXlu(globalCtx, D_060002C0);
}
