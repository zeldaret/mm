/*
 * File: z_dm_char09.c
 * Overlay: ovl_Dm_Char09
 * Description: Pirates' Fortress cutscene characters
 */

#include "z_dm_char09.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DmChar09*)thisx)

void DmChar09_Init(Actor* thisx, PlayState* play);
void DmChar09_Destroy(Actor* thisx, PlayState* play);
void DmChar09_Update(Actor* thisx, PlayState* play);
void DmChar09_Draw(Actor* thisx, PlayState* play);

void func_80AB1E10(SkelAnime* arg0, s32 arg1, s32 arg2);
void func_80AB1FDC(DmChar09* this, PlayState* play);
void func_80AB2258(DmChar09* this, PlayState* play);
void func_80AB2268(DmChar09* this, PlayState* play);
void func_80AB24BC(DmChar09* this, PlayState* play);
s32 func_80AB25D8(PlayState *play, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx);
void func_80AB1FA0(DmChar09 *this, s32 arg1);
#if 0
const ActorInit Dm_Char09_InitVars = {
    ACTOR_DM_CHAR09,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BEE,
    sizeof(DmChar09),
    (ActorFunc)DmChar09_Init,
    (ActorFunc)DmChar09_Destroy,
    (ActorFunc)DmChar09_Update,
    (ActorFunc)DmChar09_Draw,
};
s32 D_80AB26B0 = 0x0600005C; // object_bee_Anim_00005C
#endif

extern UNK_TYPE D_0600005C;
extern SkeletonHeader D_06001398;
extern f32 D_80AB26D0;
extern f32 D_80AB26D4;
extern f32 D_80AB26D8;
extern f32 D_80AB26DC;
extern f32 D_80AB26E0;
extern f32 D_80AB26E4;
extern f32 D_80AB26E8;
extern UNK_TYPE D_80AB26B0;
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB1E10.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Init.s")

void DmChar09_Init(Actor* thisx, PlayState* play) {
    DmChar09* this = (DmChar09*)thisx;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    SkelAnime_Init(play, &this->skelAnime, &D_06001398, (AnimationHeader*)&D_0600005C, &this->unk188, &this->unk1C4, 0xA);
    func_80AB1E10(&this->skelAnime, &D_80AB26B0, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk228 = Rand_ZeroOne() * 65535.0f;
    this->unk22A = Rand_ZeroOne() * 65535.0f;
    this->actionFunc = func_80AB2258;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Destroy.s")

void DmChar09_Destroy(Actor* thisx, PlayState* play) {
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB1FA0.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB1FDC.s")

void func_80AB1FDC(DmChar09 *this, PlayState *play) {
    Vec3f sp58;
    f32 sp54;
    Vec3f sp40;
    PosRot *sp30;
    Vec3f *sp28;
    PosRot *temp_a1;
    Vec3f *temp_a2;
    f32 temp_fv0;
    f32 temp_fv0_2;
    f32 temp_fv1;
    s32 temp_a0;
    s32 temp_v0;
    unkStruct *temp_v0_2;
    unkStruct *temp_v1;
    f32 phi_fv0;
    f32 phi_fa0;
    s32 phi_a1;

    temp_a1 = &this->actor.world;
    sp30 = temp_a1;
    Math_Vec3f_Copy(&sp40, &temp_a1->pos);
    Math_Vec3s_ToVec3f(&sp58, this->unk224 + (this->unk21C * 6) + (this->unk220 * 6));
    temp_a2 = &this->actor.velocity;
    sp28 = temp_a2;
    Math_Vec3f_Diff(&sp58, &sp30->pos, temp_a2);
    temp_fv0 = Math3D_Vec3fMagnitude(sp28);
    temp_fv1 = this->unk210;
    if ((temp_fv0 < (temp_fv1 * 8.0f)) && (temp_fv1 > 2.0f)) {
        phi_fv0 = ((temp_fv1 - 2.0f) * 0.1f) + 2.0f;
        phi_fa0 = temp_fv1 * 0.03f;
    } else {
        phi_fv0 = temp_fv1;
        phi_fa0 = temp_fv1 * 0.16f;
    }
    sp54 = temp_fv0;
    Math_StepToF(&this->actor.speedXZ, phi_fv0, phi_fa0);
    temp_fv0_2 = this->actor.speedXZ;
    if ((temp_fv0_2 + 0.05f) < temp_fv0) {
        Math_Vec3f_Scale(sp28, temp_fv0_2 / temp_fv0);
        this->actor.world.pos.x += this->actor.velocity.x;
        this->actor.world.pos.y += this->actor.velocity.y;
        this->actor.world.pos.z += this->actor.velocity.z;
    } else {
        temp_v0 = this->unk21C + this->unk220;
        this->unk21C = temp_v0;
        temp_a0 = this->unk218;
        this->actor.speedXZ *= 0.4f;
        phi_a1 = 1;
        if (((temp_v0 >= temp_a0) && (this->unk220 > 0)) || ((temp_v0 <= 0) && (this->unk220 < 0))) {
            temp_v0_2 = this->unk224;
            temp_v1 = temp_v0_2 + (temp_a0 * 6);
            if ((temp_v1->unk0 == temp_v0_2->unk0) && (temp_v1->unk2 == temp_v0_2->unk2) && (temp_v1->unk4 == temp_v0_2->unk4)) {
                this->unk21C = 0;
                this->unk220 = 1;
            } else {
                this->actionFunc = func_80AB2268;
                phi_a1 = 0;
            }
        }
        if (phi_a1 != 0) {
            func_80AB1FA0(this, this->unk21C);
        }
    }
    Math_SmoothStepToS(&this->actor.world.rot.y, (s16) (Math_Vec3f_Yaw(&sp30->pos, &sp40) + 0x7FFF), 1, 0x7D0, (s16) 0);
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB2258.s")

void func_80AB2258(DmChar09* this, PlayState* play) {
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB2268.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB24BC.s")

void func_80AB24BC(DmChar09 *this, PlayState *play) {
    this->unk228 += 0xBB8;
    this->unk22A += 0x1388;
    this->unk204 = Math_SinS(this->unk228) * 150.0f;
    this->unk208 = Math_SinS(this->unk22A) * 150.0f;
    this->unk20C = Math_SinS(this->unk228) * 150.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Update.s")

void DmChar09_Update(Actor *thisx, PlayState *play) {
    DmChar09 *this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, play);
    func_80AB2268(this, play);
    func_80AB24BC(this, play);
    if ((play->csCtx.state != 0) && (this->unk22E != 0) && (this->actor.params & 0x100)) {
        Actor_PlaySfxAtPos(&this->actor, 0x304A);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB25D8.s")

s32 func_80AB25D8(PlayState *play, s32 limbIndex, Gfx **dList, Vec3f *pos, Vec3s *rot, Actor *thisx) {
    DmChar09* this = THIS;

    Matrix_Translate(this->unk204, this->unk208, this->unk20C, MTXMODE_APPLY);
    return 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Draw.s")

void DmChar09_Draw(Actor *thisx, PlayState *play) {
    DmChar09 *this = THIS;

    if ((play->csCtx.state != 0) && (this->unk22E != 0)) {
        func_8012C28C(play->state.gfxCtx);
        func_8012C2DC(play->state.gfxCtx);
        SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, func_80AB25D8, NULL, &this->actor);
    }
}