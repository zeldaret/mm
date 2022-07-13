/*
 * File: z_eff_change.c
 * Overlay: ovl_Eff_Change
 * Description: Elegy of Emptiness - Beam of Light When Creating Statue
 */

#include "z_eff_change.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EffChange*)thisx)

void EffChange_Init(Actor* thisx, PlayState* play);
void EffChange_Destroy(Actor* thisx, PlayState* play);
void EffChange_Update(Actor* thisx, PlayState* play);

void func_80A4C578(EffChange* this, s32 arg1);        /* static */
void func_80A4C5CC(EffChange* this, PlayState* play); /* static */
void func_80A4C7B0(Actor* thisx, PlayState* play);

#if 0
const ActorInit Eff_Change_InitVars = {
    ACTOR_EFF_CHANGE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EffChange),
    (ActorFunc)EffChange_Init,
    (ActorFunc)EffChange_Destroy,
    (ActorFunc)EffChange_Update,
    (ActorFunc)NULL,
};
static struct _struct_D_80A4C920_0x6 D_80A4C920[8] = {
    { 0xFF, 0xFF, 0xAA, 0, 0x64, 0 },
    { 0xFF, 0xFF, 0xAA, 0xC8, 0, 0 },
    { 0xAA, 0xFF, 0xFF, 0, 0x64, 0xFF },
    { 0xFF, 0xFF, 0xAA, 0xC8, 0x96, 0 },
    { 0xFF, 0xFF, 0xAA, 0, 0x64, 0 },
    { 0xFF, 0xFF, 0xAA, 0, 0x64, 0 },
    { 0xFF, 0xFF, 0xAA, 0, 0x64, 0 },
    { 0xFF, 0xFF, 0xAA, 0, 0x64, 0 },
};
#endif

extern UNK_TYPE D_040281DC;
extern UNK_TYPE D_04028FEC;
extern SkeletonInfo* D_0402900C;
extern UNK_TYPE D_80A4C920[];
extern f32 D_80A4C950;
extern f32 D_80A4C954;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Change/EffChange_Init.s")

void EffChange_Init(Actor* thisx, PlayState* play) {
    EffChange* this = THIS;

    this->actionFunc = func_80A4C5CC;
    this->actor.draw = func_80A4C7B0;
    func_80A4C578(this, this->actor.params & 7);
    Actor_SetScale(&this->actor, 0.075f);
    this->unk1BE[3] = 0;
    func_80183430(&this->skeletonInfo, &D_0402900C, &D_040281DC, &this->unk174, &this->unk198, NULL);
    func_801834A8(&this->skeletonInfo, &D_040281DC);
    this->unk1BC = 0;
    this->actor.shape.rot.y = 0;
    this->skeletonInfo.frameCtrl.unk_C = 0.6666667;
    ActorCutscene_SetIntentToPlay(0x7B);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Change/EffChange_Destroy.s")

void EffChange_Destroy(Actor* thisx, PlayState* play) {
    EffChange* this = THIS;

    func_8018349C(&this->skeletonInfo);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Change/func_80A4C578.s")

void func_80A4C578(EffChange* this, s32 arg1) {
    u8* temp_v0;
    arg1 *= 6;
    temp_v0 = &(((u8*)D_80A4C920)[arg1]);
    this->unk1BE[0] = temp_v0[0];
    this->unk1BE[1] = temp_v0[1];
    this->unk1BE[2] = temp_v0[2];
    this->unk1C2[0] = temp_v0[3];
    this->unk1C2[1] = temp_v0[4];
    this->unk1C2[2] = temp_v0[5];
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Change/func_80A4C5CC.s")

void func_80A4C5CC(EffChange* this, PlayState* play) {
    f32 phi_fv0;

    if (func_80183DE0(&this->skeletonInfo) != 0) {
        Actor_MarkForDeath(&this->actor);
        ActorCutscene_Stop(0x7B);
        func_800FD2B4(play, 0.0f, 850.0f, 0.2f, 0.0f);
    } else {
        this->unk1BC++;
        if (this->skeletonInfo.frameCtrl.unk_10 < 20.0f) {
            if ((this->unk1BE[3]) < 0xF2) {
                this->unk1BE[3] += 0xD;
            } else {
                this->unk1BE[3] = 0xFF;
            }
        } else if (this->skeletonInfo.frameCtrl.unk_10 > 70.0f) {
            if (((s32)this->unk1BE[3]) >= 0xE) {
                this->unk1BE[3] -= 0xD;
            } else {
                this->unk1BE[3] = 0;
            }
        } else {
            this->unk1BE[3] = 0xFF;
        }

        phi_fv0 = this->unk1BE[3] * 0.003921569f;
        if (phi_fv0 > 1.0f) {
            phi_fv0 = 1.0f;
        } else if (phi_fv0 < 0.0f) {
            phi_fv0 = 0.0f;
        }
        func_800FD2B4(play, phi_fv0, 850.0f, 0.2f, 0.0f);
        if (ActorCutscene_GetCurrentIndex() != 0x7B) {
            if (ActorCutscene_GetCanPlayNext(0x7B) != 0) {
                ActorCutscene_Start(0x7B, &this->actor);
            } else {
                ActorCutscene_SetIntentToPlay(0x7B);
            }
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Change/EffChange_Update.s")

void EffChange_Update(Actor* thisx, PlayState* play) {
    EffChange* this = THIS;

    this->actionFunc(this, play);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Change/func_80A4C7B0.s")

void func_80A4C7B0(Actor* thisx, PlayState* play) {
    s32 pad;
    Mtx* mtx;
    EffChange* this = THIS;

    AnimatedMat_DrawStepXlu(play, Lib_SegmentedToVirtual(&D_04028FEC), (u32)this->unk1BC);
    mtx = GRAPH_ALLOC(play->state.gfxCtx, ALIGN16(this->skeletonInfo.unk_18->unk_1 * sizeof(Mtx)));

    if (mtx != NULL) {
        func_8012C2DC(play->state.gfxCtx);
        Matrix_RotateYS((Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000), MTXMODE_APPLY);

        OPEN_DISPS(play->state.gfxCtx);

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, this->unk1BE[0], this->unk1BE[1], this->unk1BE[2], this->unk1BE[3]);
        gDPSetEnvColor(POLY_XLU_DISP++, this->unk1C2[0], this->unk1C2[1], this->unk1C2[2], 0xFF);
        func_8018450C(play, &this->skeletonInfo, mtx, NULL, NULL, &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
