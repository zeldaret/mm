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

void func_80AB1E10(SkelAnime* skelAnime, AnimationInfo* animation, u16 index);
void func_80AB1FDC(DmChar09* this, PlayState* play);
void func_80AB2258(DmChar09* this, PlayState* play);
void func_80AB2268(DmChar09* this, PlayState* play);
void func_80AB24BC(DmChar09* this, PlayState* play);
s32 func_80AB25D8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void func_80AB1FA0(DmChar09* this, s32 arg1);
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
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB1E10.s")

//void func_80AB1E10(SkelAnime *arg0, s32 arg1, s32 arg2) {
void func_80AB1E10(SkelAnime* skelAnime, AnimationInfo* animation, u16 index) {
    f32 frameCount;

    animation += index;

    if (animation->frameCount < 0.0f) {
        frameCount = Animation_GetLastFrame(animation->animation);
    } else {
        frameCount = animation->frameCount;
    }

    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, frameCount,
                     animation->mode, animation->morphFrames);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Init.s")

void DmChar09_Init(Actor* thisx, PlayState* play) {
    DmChar09* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 19.0f);
    SkelAnime_Init(play, &this->skelAnime, &D_06001398, (AnimationHeader*)&D_0600005C, &this->unk188, &this->unk1C4,
                   0xA);
    func_80AB1E10(&this->skelAnime, &D_80AB26B0, 0);
    Actor_SetScale(&this->actor, 0.01f);
    this->unk228 = Rand_ZeroOne() * 65535.0f;
    this->unk22A = Rand_ZeroOne() * 65535.0f;
    this->actionFunc = func_80AB2258;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Destroy.s")

void DmChar09_Destroy(Actor* thisx, PlayState* play) {
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB1FA0.s")

void func_80AB1FA0(DmChar09 *this, s32 arg1) {
    Math_Vec3s_ToVec3f(&this->actor.world.pos, &this->unk224[arg1]);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB1FDC.s")

void func_80AB1FDC(DmChar09* this, PlayState* play) {
    Actor* thisx = &this->actor;
    Vec3f sp58;
    f32 sp54;
    f32 phi_fa0;
    f32 phi_fv0;
    Vec3f sp40;
    s32 phi_a1;
    Vec3s* temp_v1;

    Math_Vec3f_Copy(&sp40, &thisx->world.pos);
    Math_Vec3s_ToVec3f(&sp58, this->unk224 + this->unk21C + this->unk220);
    Math_Vec3f_Diff(&sp58, &thisx->world.pos, &thisx->velocity);
    sp54 = Math3D_Vec3fMagnitude(&thisx->velocity);
    if ((sp54 < (this->speed * 8.0f)) && (this->speed > 2.0f)) {
        phi_fv0 = ((this->speed - 2.0f) * 0.1f) + 2.0f;
        phi_fa0 = this->speed * 0.03f;
    } else {
        phi_fv0 = this->speed;
        phi_fa0 = this->speed * 0.16f;
    }
    Math_StepToF(&thisx->speedXZ, phi_fv0, phi_fa0);
    if ((thisx->speedXZ + 0.05f) < sp54) {
        Math_Vec3f_Scale(&thisx->velocity, thisx->speedXZ / sp54);
        thisx->world.pos.x += thisx->velocity.x;
        thisx->world.pos.y += thisx->velocity.y;
        thisx->world.pos.z += thisx->velocity.z;
    } else {
        this->unk21C += this->unk220;
        thisx->speedXZ *= 0.4f;
        phi_a1 = 1;
        if (((this->unk21C >= this->unk218) && (this->unk220 > 0)) || ((this->unk21C <= 0) && (this->unk220 < 0))) {
            temp_v1 = this->unk224 + this->unk218;
            if (((this->unk224->x == temp_v1->x) && (this->unk224->y == temp_v1->y)) &&
                (this->unk224->z == temp_v1->z)) {
                this->unk21C = 0;
                this->unk220 = 1;
            } else {
                phi_a1 = 0;
                this->actionFunc = func_80AB2268;
            }
        }
        if (phi_a1 != 0) {
            func_80AB1FA0(this, this->unk21C);
        }
    }
    Math_SmoothStepToS(&thisx->world.rot.y, Math_Vec3f_Yaw(&thisx->world.pos, &sp40) + 0x7FFF, 1, 0x7D0, 0);
    thisx->shape.rot.y = thisx->world.rot.y;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB2258.s")

void func_80AB2258(DmChar09* this, PlayState* play) {
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB2268.s")
/*
void func_80AB2268(DmChar09 *this, PlayState *play) {
    Path *path;
    //Path *temp_v1;
    Path *temp_v1_2;
    Path *temp_v1_3;
    f32 temp_ft1;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_v0;
    u16 action;
    u16 temp_a2;
    u16 temp_t5;
    u8 phi_v1;
    s32 phi_a3;
    s32 phi_a0;
    s32 phi_a0_2;
    Path *phi_v1_2;
    s32 i;
    s32 i2;

    phi_v1 = 0U;
    phi_a3 = 0;
    if ((this->actor.params & 0xF) == 0) {
        if (play->csCtx.currentCsIndex == 1) {
            phi_v1 = 1U;
        }
    } else if (play->csCtx.currentCsIndex == 0) {
        phi_v1 = 1;
    }
    if ((Cutscene_CheckActorAction(play, 0x1F7U) != 0) && (phi_v1 != 0)) {
        temp_v0 = Cutscene_GetActorActionIndex(play, 0x1F7U);
        //action = play->csCtx.actorActions[temp_v0]->action;
        //temp_a0 = play + (temp_v0 * 4);
        //temp_t0 = temp_v0;
        //temp_a1 = play->csCtx.actorActions[temp_v0]->action;
        if (this->unk22F != play->csCtx.actorActions[temp_v0]->action) {
            this->unk22F = (u8) play->csCtx.actorActions[temp_v0]->action;
            //temp_a2 = *temp_a0->unk1F4C;
            //temp_a2 = action;
            switch (play->csCtx.actorActions[temp_v0]->action) {                   
            case 3:
                phi_a3 = 1;
                break;
            case 4:
                phi_a3 = 2;
                break;
            case 5:
                phi_a3 = 3;
                break;
            }
        //case 2:
            if ((s32) play->csCtx.actorActions[temp_v0]->action > 2) {
                //path = &play->setupPathList[((s16) this->actor.params >> 4) & 0xF];
                //temp_v1 = &path[((s16) this->actor.params >> 4) & 0xF];
                //phi_a0 = 0;
                //phi_a0_2 = 0;
                //phi_v1_2 = temp_v1;
                //phi_v1_3 = temp_v1;
                //phi_v1_4 = temp_v1;
                if (phi_a3 > 0) {
                    //temp_v0_2 = phi_a3 & 3;
                    if (phi_a3 & 3 != 0) {
                        i = 0;
                        //for (i = 0; i < phi_a3; i++)
                        do 
                        {
                            //temp_a0_2 = phi_a0 + 1;
                            temp_v1_2 = &play->setupPathList[((s16) this->actor.params >> 4) & 0xF];
                            i++;
                            //phi_a0 = temp_a0_2;
                            //phi_a0_2 = temp_a0_2;
                            //phi_v1_2 = temp_v1_2;
                            //phi_v1_3 = temp_v1_2;
                            //phi_v1_4 = temp_v1_2;
                        } while (phi_a3 & 3 != i);
                        //if (temp_a0_2 != phi_a3) {
                       // }
                    } else {
                        for (i = 0; i < phi_a3;i++)
                        //do 
                        {
                            //temp_a0_3 = phi_a0_2 + 4;
                            temp_v1_3 = &play->setupPathList[((s16) this->actor.params >> 4) & 0xF];
                            //phi_a0_2 = temp_a0_3;
                            //phi_v1_2 = temp_v1_3;
                            //phi_v1_4 = temp_v1_3;
                        } //while (temp_a0_3 != phi_a3);
                    }
                }
                this->unk224 = Lib_SegmentedToVirtual(phi_v1_2->points);
                this->unk21C = 0;
                this->unk214 = (s32) phi_v1_2->count;
                this->unk220 = 1;
                this->unk218 = phi_v1_2->count - 1;
                this->unk22E = 1;
                temp_t5 = (u16) play->csCtx.actorActions[temp_v0]->rot.z;
                temp_ft1 = (f32) temp_t5;
                //phi_ft1 = temp_ft1;

                //if ((s32) temp_t5 < 0) {
                  //  phi_ft1 = temp_ft1 + 4294967296.0f;
                //}
                this->speed = temp_ft1 * 0.00390625f;
                this->actionFunc = func_80AB1FDC;
                return;
            }
            this->unk22E = 0;
            this->actionFunc = func_80AB2258;
        }
    } else {
        this->unk22F = 0x63;
    }
}
*/
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB24BC.s")

void func_80AB24BC(DmChar09* this, PlayState* play) {
    this->unk228 += 0xBB8;
    this->unk22A += 0x1388;
    this->unk204 = Math_SinS(this->unk228) * 150.0f;
    this->unk208 = Math_SinS(this->unk22A) * 150.0f;
    this->unk20C = Math_SinS(this->unk228) * 150.0f;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Update.s")

void DmChar09_Update(Actor* thisx, PlayState* play) {
    DmChar09* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    this->actionFunc(this, play);
    func_80AB2268(this, play);
    func_80AB24BC(this, play);
    if ((play->csCtx.state != 0) && (this->unk22E != 0) && (this->actor.params & 0x100)) {
        Actor_PlaySfxAtPos(&this->actor, 0x304A);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/func_80AB25D8.s")

s32 func_80AB25D8(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    DmChar09* this = THIS;

    Matrix_Translate(this->unk204, this->unk208, this->unk20C, MTXMODE_APPLY);
    return 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Char09/DmChar09_Draw.s")

void DmChar09_Draw(Actor* thisx, PlayState* play) {
    DmChar09* this = THIS;

    if ((play->csCtx.state != 0) && (this->unk22E != 0)) {
        func_8012C28C(play->state.gfxCtx);
        func_8012C2DC(play->state.gfxCtx);
        SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, func_80AB25D8, NULL,
                          &this->actor);
    }
}