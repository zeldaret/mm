/*
 * File: z_bg_ikninside.c
 * Overlay: ovl_Bg_Ikninside
 * Description: Ancient Castle of Ikana Objects
 */

#include "z_bg_ikninside.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgIkninside*)thisx)

void BgIkninside_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkninside_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkninside_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkninside_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C072D0(BgIkninside*, GlobalContext*); /* extern */
// void func_80C07230(BgIkninside*, GlobalContext*); /* extern */
#if 1
const ActorInit Bg_Ikninside_InitVars = {
    ACTOR_BG_IKNINSIDE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKNINSIDE_OBJ,
    sizeof(BgIkninside),
    (ActorFunc)BgIkninside_Init,
    (ActorFunc)BgIkninside_Destroy,
    (ActorFunc)BgIkninside_Update,
    (ActorFunc)BgIkninside_Draw,
};

s32 D_80C076A0[] = { 0x0600A748, 0x0600A5A8 };

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C076A8 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x80000008, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 32, 32, 0, { 0, 0, 0 } },
};

#endif
s32 D_80C076D4[] = { 0x00000000, 0xBF800000, 0x00000000 };

// extern ColliderCylinderInit D_80C076A8;

extern UNK_TYPE D_0600CC78;
extern UNK_TYPE D_0600DE48;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/BgIkninside_Init.s")
/* (matching)
void BgIkninside_Init(Actor* thisx, GlobalContext* globalCtx) {
    CollisionHeader* sp28;
    ColliderCylinder* sp20;
    BgIkninside* this = THIS;

    sp20 = NULL;
    Actor_SetScale(&this->actor, 0.1f);
    this->actionFunc = func_80C072D0;
    DynaPolyActor_Init((DynaPolyActor*)this, 0);
    CollisionHeader_GetVirtual((CollisionHeader*)&D_0600DE48, &sp20);
    this->unk144 = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->actor, sp20);
    Collider_InitAndSetCylinder(globalCtx, &this->unk15C, &this->actor, &D_80C076A8);
    Collider_UpdateCylinder(&this->actor, &this->unk15C);
    if (Flags_GetSwitch(globalCtx, (s32)(this->actor.params & 0xFE00) >> 9) != 0) {
        Actor_MarkForDeath(&this->actor);
    }
}
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/BgIkninside_Destroy.s")
/* (matching)
void BgIkninside_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIkninside* this = (BgIkninside*)thisx;
    Collider_DestroyCylinder(globalCtx, &this->unk15C);
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->unk144);
}
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/func_80C07220.s")
/*
void func_80C07220(s32 arg0, s32 arg1) {

}*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/func_80C07230.s")
/*
void func_80C07230(BgIkninside *arg0, GlobalContext *arg1) {
    if (arg0->actor.cutscene == -1) {
        arg0->unk1AC = func_80C07220;
        return;
    }
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay((s16) arg0->actor.cutscene);
        return;
    }
    if (ActorCutscene_GetCanPlayNext((s16) arg0->actor.cutscene) != 0) {
        ActorCutscene_StartAndSetUnkLinkFields((s16) arg0->actor.cutscene, &arg0->actor);
        arg0->unk1AC = func_80C07220;
        return;
    }
    ActorCutscene_SetIntentToPlay((s16) arg0->actor.cutscene);
}
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/func_80C072D0.s")
/*
void func_80C072D0(BgIkninside* arg0, GlobalContext* arg1) {
    f32 spB0;
    f32 spAC;
    f32 spA8;
    f32 spA0;
    f32 sp9C;
    f32 temp_fs0;
    f32 temp_fs0_2;
    f32 temp_fs0_3;
    f32 temp_fs1;
    s16 temp_s0;
    s16 temp_s1;
    s16 temp_v0_2;
    s32 temp_s2;
    s32 phi_s2;
    if ((arg0->unk15C.base.acFlags & 2) != 0) {
        if ((arg0->unk15C.info.acHitInfo != NULL) &&
            ((phi_s2 = 0, arg0->unk15C.info.acHitInfo->toucher.dmgFlags & 0x80000000))) {
            do {
                temp_s0 = Rand_S16Offset(0x1800, 0x2800);
                temp_s1 = (s16)(Rand_Next() >> 0x10);
                temp_fs1 = Rand_ZeroFloat(3.0f) + 8.0f;
                temp_fs0 = Math_CosS(temp_s0);
                sp9C = Math_SinS(temp_s1) * (temp_fs1 * temp_fs0);
                temp_fs0_2 = Math_SinS(temp_s0);
                spA0 = Rand_ZeroFloat(5.0f) + (temp_fs1 * temp_fs0_2);
                temp_fs0_3 = Math_CosS(temp_s0);
                spA8 = (Rand_ZeroFloat(10.0f) * sp9C) + arg0->actor.world.pos.x;
                spAC = (Rand_ZeroFloat(1.0f) * spA0) + arg0->actor.world.pos.y;
                spB0 =
                    ((Rand_ZeroFloat(10.0f) * Math_CosS(temp_s1)) * (temp_fs1 * temp_fs0_3)) + arg0->actor.world.pos.z;
                spA8 = (Rand_ZeroFloat(10.0f) * sp9C) + arg0->actor.world.pos.x;
                EffectSsHahen_Spawn(arg1, (Vec3f*)(&spA8), (Vec3f*)(&sp9C), (Vec3f*)D_80C076D4, (s16)0, (s16)0x1E,
                                    (s16)0x236, (s16)0x19, (Gfx*)D_80C076A0[phi_s2 & 1]);
                temp_s2 = phi_s2 + 1;
                phi_s2 = temp_s2;
            } while (temp_s2 != 0x14);
            Flags_SetSwitch(arg1, ((s32)(arg0->actor.params & 0xFE00)) >> 9);
            arg0->actionFunc = func_80C07230;
            arg0->actor.draw = NULL;
            func_800C62BC(arg1, &arg1->colCtx.dyna, arg0->unk144);
        } else {
            arg0->unk1AA = 0x14;
        }
    }
    temp_v0_2 = arg0->unk1AA;
    if (temp_v0_2 > 0) {
        if ((temp_v0_2 & 1) != 0) {
            arg0->actor.world.pos.y = arg0->actor.home.pos.y - 1.0f;
        } else {
            arg0->actor.world.pos.y = arg0->actor.home.pos.y;
        }
        arg0->unk1AA += -1;
    } else {
        arg0->unk1AA = 0;
        arg0->actor.world.pos.y = arg0->actor.home.pos.y;
    }
    CollisionCheck_SetAC(arg1, &arg1->colChkCtx, &arg0->unk15C.base);
}
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/BgIkninside_Update.s")
/*
void BgIkninside_Update(Actor *thisx, GlobalContext *globalCtx) {
    BgIkninside *this = (BgIkninside *) thisx;
    this->unk1AC();
}
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikninside/BgIkninside_Draw.s")
/*
void BgIkninside_Draw(Actor *thisx, GlobalContext *globalCtx) {
    //GraphicsContext *sp24;
    Gfx *sp1C;
    Gfx *temp_v0;
    Gfx *temp_v0_2;
    GraphicsContext *temp_a2;
    BgIkninside *this = (BgIkninside *) thisx;

    //OPEN_DISPS(globalCtx->state.gfxCtx);
    temp_a2 = globalCtx->state.gfxCtx;
    temp_v0 = temp_a2->polyOpa.p;
    temp_a2->polyOpa.p = temp_v0 + 8;
    temp_v0->words.w0 = 0xDA380003;
    //sp24 = temp_a2;
    sp1C = temp_v0;
    sp1C->words.w1 = Matrix_NewMtx(globalCtx->state.gfxCtx);
    //sp24 = temp_a2;
    func_8012C28C(globalCtx->state.gfxCtx);
    //temp_a2->polyOpa.p = temp_v0_2 + 8;

    //temp_v0_2 = temp_a2->polyOpa.p;
    //temp_v0_2->words.w0 = 0xDE000000;
    //temp_v0_2->words.w1 = (u32) &D_0600CC78;
    gSPDisplayList(POLY_OPA_DISP++, &D_0600CC78);

}*/
