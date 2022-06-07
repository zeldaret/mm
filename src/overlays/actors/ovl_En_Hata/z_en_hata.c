/*
 * File: z_en_hata.c
 * Overlay: ovl_En_Hata
 * Description: Red Flag on Post
 */

#include "z_en_hata.h"

#define FLAGS 0x00000000

#define THIS ((EnHata*)thisx)

void EnHata_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHata_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHata_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHata_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Hata_InitVars = {
    ACTOR_EN_HATA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HATA,
    sizeof(EnHata),
    (ActorFunc)EnHata_Init,
    (ActorFunc)EnHata_Destroy,
    (ActorFunc)EnHata_Update,
    (ActorFunc)EnHata_Draw,
};

#endif

extern UNK_TYPE D_06002FD0;

extern CollisionHeader D_060000C0;
extern AnimationHeader D_06000444;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hata/EnHata_Init.s")

void EnHata_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 new_var;
    EnHata* this = THIS;
    f32 sp34;
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06002FD0, NULL, &this->unk1A0, &this->unk21E,
                   0x15);
    sp34 = Animation_GetLastFrame(&D_06000444);
    Animation_Change(&this->skelAnime, &D_06000444, 1.0f, 0.0f, sp34, 0, 0.0f);
    new_var = (s32)Rand_ZeroFloat((f32)sp34);
    this->skelAnime.curFrame = (f32)new_var;
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &D_060000C0);
    Actor_SetScale(&this->dyna.actor, 0.013f);
    this->dyna.actor.uncullZoneScale = 500.0f;
    this->dyna.actor.uncullZoneDownward = 500.0f;
    this->dyna.actor.uncullZoneForward = 2200.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hata/EnHata_Destroy.s")
void EnHata_Destroy(Actor *thisx, GlobalContext *globalCtx) {
    EnHata *this = THIS;
    
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hata/EnHata_Update.s")

void EnHata_Update(Actor *thisx, GlobalContext *globalCtx) {
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 *sp24;
    f32 *temp_a0;
    f32 temp_ft3;
    f32 temp_fv1;
    f32 phi_fv0;
    f32 phi_fv0_2;
    f32 phi_fv0_3;
    EnHata *this = THIS;

    temp_fv1 = globalCtx->envCtx.windSpeed / 120.0f;
    phi_fv0 = 0.0f;
    if (temp_fv1 < 0.0f) {

    } else if (temp_fv1 > 1.0f) {
        phi_fv0 = 1.0f;
    } else {
        phi_fv0 = temp_fv1;
    }
    this->skelAnime.playSpeed = 2.75f * phi_fv0;
    sp30 = phi_fv0;
    sp24 = globalCtx + 0x10000;
    this->skelAnime.playSpeed += 1.0f + Rand_ZeroFloat(1.25f);
    temp_a0 = &this->unk2A4;
    sp34 = (f32) globalCtx->envCtx.windDir.x;
    temp_ft3 = (f32) globalCtx->envCtx.windDir.y + ((1.0f - phi_fv0) * 240.0f);
    sp38 = temp_ft3;
    if (temp_ft3 < -118.0f) {
        sp38 = -118.0f;
    } else {
        if (sp38 > 118.0f) {
            phi_fv0_2 = 118.0f;
        } else {
            phi_fv0_2 = sp38;
        }
        sp38 = phi_fv0_2;
    }
    sp3C = (f32) globalCtx->envCtx.windDir.z;
    phi_fv0_3 = 0.1f;
    if (phi_fv0 < 0.1f) {

    } else if (phi_fv0 > 0.4f) {
        phi_fv0_3 = 0.4f;
    } else {
        phi_fv0_3 = phi_fv0;
    }
    sp24 = temp_a0;
    sp30 = phi_fv0_3;
    Math_ApproachF(temp_a0, sp34, phi_fv0_3, 1000.0f);
    Math_ApproachF(&this->unk2A8, sp38, phi_fv0_3, 1000.0f);
    Math_ApproachF(&this->unk2AC, sp3C, phi_fv0_3, 1000.0f);
    sp34.unk0 = sp24->unk0;
    sp34.unk4 = (s32) sp24->unk4;
    sp34.unk8 = (s32) sp24->unk8;
    this->unk29C = Math_Vec3f_Pitch(&gZeroVec3f, (Vec3f *) &sp34);
    this->unk29C = -this->unk29C;
    this->unk2A0 = Math_Vec3f_Yaw(&gZeroVec3f, (Vec3f *) &sp34);
    this->unk2A0 += -0x4000;
    SkelAnime_Update(&this->skelAnime);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hata/func_8089EC68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hata/EnHata_Draw.s")
