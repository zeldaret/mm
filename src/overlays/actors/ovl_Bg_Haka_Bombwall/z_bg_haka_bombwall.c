/*
 * File: z_bg_haka_bombwall.c
 * Overlay: ovl_Bg_Haka_Bombwall
 * Description: Beneath the Grave - Bombable Wall
 */

#include "z_bg_haka_bombwall.h"

#define FLAGS 0x00000000

#define THIS ((BgHakaBombwall*)thisx)

void BgHakaBombwall_Init(Actor* thisx, PlayState* play);
void BgHakaBombwall_Destroy(Actor* thisx, PlayState* play);
void BgHakaBombwall_Update(Actor* thisx, PlayState* play);
void BgHakaBombwall_Draw(Actor* thisx, PlayState* play);

void func_80BD6260(BgHakaBombwall* this);
void func_80BD6274(BgHakaBombwall* this, PlayState* play);
void func_80BD62D0(BgHakaBombwall* this);
s32 func_80BD5E00(BgHakaBombwall* this);
void func_80BD6314(BgHakaBombwall* this, PlayState* play);
void func_80BD5E6C(BgHakaBombwall* this, PlayState* play);
void func_80BD63B4(BgHakaBombwall* this);
void func_80BD63D0(BgHakaBombwall* this, PlayState* play);
#if 0
const ActorInit Bg_Haka_Bombwall_InitVars = {
    ACTOR_BG_HAKA_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HAKA_OBJ,
    sizeof(BgHakaBombwall),
    (ActorFunc)BgHakaBombwall_Init,
    (ActorFunc)BgHakaBombwall_Destroy,
    (ActorFunc)BgHakaBombwall_Update,
    (ActorFunc)BgHakaBombwall_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BD64A0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000008, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 80, 80, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BD64D4[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

static s16 D_80BD64CC[4] = { 0x18, 0xF, 0xA, 5 };

#endif

extern ColliderCylinderInit D_80BD64A0;
extern InitChainEntry D_80BD64D4[];

extern UNK_TYPE D_06000040;
extern UNK_TYPE D_06000148;
extern UNK_TYPE D_06001680;
extern s16 D_80BD64CC[];
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD5E00.s")

s32 func_80BD5E00(BgHakaBombwall* this) {
    if ((this->unk15C.base.acFlags & 2)) {
        if ((this->unk15C.base.ac != NULL) &&
            (Math3D_Vec3fDistSq(&this->dyna.actor.world.pos, &this->unk15C.base.ac->world.pos) < 6400.0f)) {
            return true;
        }
    }
    return false;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD5E6C.s")

void func_80BD5E6C(BgHakaBombwall* this, PlayState* play) {
    s32 i;
    Vec3f spE0;
    Vec3f spD4;
    Vec3f spC8;
    Vec3f spBC;
    f32 temp_fs0;
    f32 phi_fs1;
    s16 phi_s0;
    s16 temp;
    s16 phi_t0;

    Matrix_Push();
    Matrix_RotateYS(this->dyna.actor.shape.rot.y, MTXMODE_NEW);
    temp_fs0 = 0.0f;
    phi_fs1 = 0.1f;

    for (i = 0; i < 30; i++) {
        temp_fs0 = 0.0f + (60.0f +(Rand_ZeroOne() * 20.0f));
        if (temp_fs0 > 75.0f) {
            temp_fs0 -= 150.0f;
        }
        spC8.x = temp_fs0;

        phi_fs1 += 5;
        spC8.y = phi_fs1;

        spC8.z = (Rand_ZeroOne() * 20.0f) - 10.0f;

        spBC.x = ((Rand_ZeroOne() - 0.5f) * 5.0f) + (temp_fs0 * 0.053333335f);
        spBC.y = (Rand_ZeroOne() * 7.0f) - 2.0f;
        spBC.z = (Rand_ZeroOne() * 4.0f) - 2.0f;

        Matrix_MultVec3f(&spC8, &spE0);
        Matrix_MultVec3f(&spBC, &spD4);

        spE0.x += this->dyna.actor.world.pos.x;
        spE0.y += this->dyna.actor.world.pos.y;
        spE0.z += this->dyna.actor.world.pos.z;

        if ((i & 3) == 0) {
            phi_s0 = 32;
            func_800BBFB0(play, &spE0, 50.0f, 2, 100, 120, 1);
        } else {
            phi_s0 = 64;
        }

        if (i & 1) {
            phi_s0 |= 1;
            phi_t0 = 1;
        } else {
            phi_t0 = 0;
        }

        if (D_80BD64CC[i & 3] >= 16) {
            temp = -550;
        } else {
            temp = -450;
        }

        EffectSsKakera_Spawn(play, &spE0, &spD4, &spE0, temp, phi_s0, 30, 0, 0, D_80BD64CC[i & 3], phi_t0, 0, 50, -1,
                             OBJECT_IKANA_OBJ, (Gfx*)&D_06001680);
    }

    Matrix_Pop();
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/BgHakaBombwall_Init.s")

void BgHakaBombwall_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    BgHakaBombwall* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, D_80BD64D4);
    DynaPolyActor_Init(&this->dyna, 0);
    Collider_InitCylinder(play, &this->unk15C);
    if (Flags_GetSwitch(play, this->dyna.actor.params & 0x7F)) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else {
        DynaPolyActor_LoadMesh(play, &this->dyna, (CollisionHeader*)&D_06000148);
        Collider_SetCylinder(play, &this->unk15C, &this->dyna.actor, &D_80BD64A0);
        Collider_UpdateCylinder(&this->dyna.actor, &this->unk15C);
        func_80BD6260(this);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/BgHakaBombwall_Destroy.s")

void BgHakaBombwall_Destroy(Actor* thisx, PlayState* play) {
    BgHakaBombwall* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(play, &this->unk15C);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD6260.s")

void func_80BD6260(BgHakaBombwall* this) {
    this->actionFunc = func_80BD6274;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD6274.s")

void func_80BD6274(BgHakaBombwall* this, PlayState* play) {
    if (func_80BD5E00(this)) {
        func_80BD62D0(this);
    } else {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->unk15C.base);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD62D0.s")

void func_80BD62D0(BgHakaBombwall* this) {
    this->dyna.actor.flags |= 0x10;
    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    this->actionFunc = func_80BD6314;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD6314.s")

void func_80BD6314(BgHakaBombwall* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        func_80BD5E6C(this, play);
        this->dyna.actor.draw = NULL;
        Flags_SetSwitch(play, this->dyna.actor.params & 0x7F);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 0x3C, 0x2810);
        func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
        func_80BD63B4(this);
        return;
    }
    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD63B4.s")

void func_80BD63B4(BgHakaBombwall* this) {
    this->unk1AC = 0x1E;
    this->actionFunc = func_80BD63D0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD63D0.s")

void func_80BD63D0(BgHakaBombwall* this, PlayState* play) {
    this->unk1AC--;
    if (this->unk1AC <= 0) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/BgHakaBombwall_Update.s")

void BgHakaBombwall_Update(Actor* thisx, PlayState* play) {
    BgHakaBombwall* this = THIS;

    this->actionFunc(this, play);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/BgHakaBombwall_Draw.s")

void BgHakaBombwall_Draw(Actor* thisx, PlayState* play) {
    BgHakaBombwall* this = THIS;

    Gfx_DrawDListOpa(play, (Gfx*)&D_06000040);
}