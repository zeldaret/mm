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

void EffChange_SetColors(EffChange* this, s32 arg1);  /* static */
void func_80A4C5CC(EffChange* this, PlayState* play); /* static */
void func_80A4C7B0(Actor* thisx, PlayState* play);

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
/*
static Color_RGBA8 D_80A4C920[] = {
    { 255, 255, 170, 0 },   { 100, 0, 255, 255 }, { 170, 200, 0, 0 },   { 170, 255, 255, 0 },
    { 100, 255, 255, 255 }, { 170, 200, 150, 0 }, { 255, 255, 170, 0 }, { 100, 0, 255, 255 },
    { 170, 0, 100, 0 },     { 255, 255, 170, 0 }, { 100, 0, 255, 255 }, { 170, 0, 100, 0 },
};
*/
static u8 D_80A4C920[] = { 255, 255, 170, 0,   100, 0,   255, 255, 170, 200, 0,   0,   170, 255, 255, 0,
                           100, 255, 255, 255, 170, 200, 150, 0,   255, 255, 170, 0,   100, 0,   255, 255,
                           170, 0,   100, 0,   255, 255, 170, 0,   100, 0,   255, 255, 170, 0,   100, 0 };

extern UNK_TYPE D_040281DC;
extern UNK_TYPE D_04028FEC;
extern SkeletonInfo* D_0402900C;

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Change/EffChange_Init.s")

void EffChange_Init(Actor* thisx, PlayState* play) {
    EffChange* this = THIS;

    this->actionFunc = func_80A4C5CC;
    this->actor.draw = func_80A4C7B0;
    EffChange_SetColors(this, EFFCHANGE_GET_COLORS(thisx));
    Actor_SetScale(&this->actor, 0.075f);
    this->primColors[3] = 0;
    func_80183430(&this->skeletonInfo, &D_0402900C, &D_040281DC, this->jointTable, this->morphTable, NULL);
    func_801834A8(&this->skeletonInfo, &D_040281DC);
    this->step = 0;
    this->actor.shape.rot.y = 0;
    this->skeletonInfo.frameCtrl.unk_C = 0.6666667;
    ActorCutscene_SetIntentToPlay(0x7B);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Change/EffChange_Destroy.s")

void EffChange_Destroy(Actor* thisx, PlayState* play) {
    EffChange* this = THIS;

    func_8018349C(&this->skeletonInfo);
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Change/EffChange_SetColors.s")

void EffChange_SetColors(EffChange* this, s32 arg1) {
    arg1 *= 6;
    this->primColors[0] = D_80A4C920[arg1];
    this->primColors[1] = D_80A4C920[arg1 + 1];
    this->primColors[2] = D_80A4C920[arg1 + 2];
    this->envColors[0] = D_80A4C920[arg1 + 3];
    this->envColors[1] = D_80A4C920[arg1 + 4];
    this->envColors[2] = D_80A4C920[arg1 + 5];
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Change/func_80A4C5CC.s")

void func_80A4C5CC(EffChange* this, PlayState* play) {
    f32 phi_fv0;

    if (func_80183DE0(&this->skeletonInfo) != 0) {
        Actor_MarkForDeath(&this->actor);
        ActorCutscene_Stop(0x7B);
        func_800FD2B4(play, 0.0f, 850.0f, 0.2f, 0.0f);
    } else {
        this->step++;
        if (this->skeletonInfo.frameCtrl.unk_10 < 20.0f) {
            if ((this->primColors[3]) < 242) {
                this->primColors[3] += 13;
            } else {
                this->primColors[3] = 255;
            }
        } else if (this->skeletonInfo.frameCtrl.unk_10 > 70.0f) {
            if ((this->primColors[3]) >= 14) {
                this->primColors[3] -= 13;
            } else {
                this->primColors[3] = 0;
            }
        } else {
            this->primColors[3] = 255;
        }

        phi_fv0 = this->primColors[3] * 0.003921569f;
        if (phi_fv0 > 1.0f) {
            phi_fv0 = 1.0f;
        } else if (phi_fv0 < 0.0f) {
            phi_fv0 = 0.0f;
        }
        func_800FD2B4(play, phi_fv0, 850.0f, 0.2f, 0.0f);
        if (ActorCutscene_GetCurrentIndex() != 0x7B) {
            if (ActorCutscene_GetCanPlayNext(0x7B)) {
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

    AnimatedMat_DrawStepXlu(play, Lib_SegmentedToVirtual(&gameplay_keep_Matanimheader_028FEC), this->step);
    mtx = GRAPH_ALLOC(play->state.gfxCtx, ALIGN16(this->skeletonInfo.unk_18->unk_1 * sizeof(Mtx)));

    if (mtx != NULL) {
        func_8012C2DC(play->state.gfxCtx);
        Matrix_RotateYS((Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000), MTXMODE_APPLY);

        OPEN_DISPS(play->state.gfxCtx);

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, this->primColors[0], this->primColors[1], this->primColors[2],
                        this->primColors[3]);
        gDPSetEnvColor(POLY_XLU_DISP++, this->envColors[0], this->envColors[1], this->envColors[2], 255);
        func_8018450C(play, &this->skeletonInfo, mtx, NULL, NULL, &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
