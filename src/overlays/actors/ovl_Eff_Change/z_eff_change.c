/*
 * File: z_eff_change.c
 * Overlay: ovl_Eff_Change
 * Description: Elegy of Emptiness - Beam of Light When Creating Statue
 */

#include "z_eff_change.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EffChange*)thisx)

void EffChange_Init(Actor* thisx, PlayState* play);
void EffChange_Destroy(Actor* thisx, PlayState* play);
void EffChange_Update(Actor* thisx, PlayState* play);
void EffChange_Draw(Actor* thisx, PlayState* play);

void EffChange_SetColors(EffChange* this, s32 arg1);
void func_80A4C5CC(EffChange* this, PlayState* play);

ActorInit Eff_Change_InitVars = {
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

static u8 D_80A4C920[] = {
    // prim r g b   env r g b
    255, 255, 170, 0,   100, 0,   // COLOR_0
    255, 255, 170, 200, 0,   0,   // COLOR_1
    170, 255, 255, 0,   100, 255, // COLOR_2
    255, 255, 170, 200, 150, 0,   // COLOR_3
    255, 255, 170, 0,   100, 0,   // COLOR_4
    255, 255, 170, 0,   100, 0,   // COLOR_5
    255, 255, 170, 0,   100, 0,   // COLOR_6
    255, 255, 170, 0,   100, 0    // COLOR_7
};

void EffChange_Init(Actor* thisx, PlayState* play) {
    EffChange* this = THIS;

    this->actionFunc = func_80A4C5CC;
    this->actor.draw = EffChange_Draw;
    EffChange_SetColors(this, EFFCHANGE_GET_COLORS(thisx));
    Actor_SetScale(&this->actor, 0.075f);
    this->primColors[3] = 0;
    func_80183430(&this->skeletonInfo, gameplay_keep_Blob_02900C, gameplay_keep_Blob_0281DC, this->jointTable,
                  this->morphTable, NULL);
    func_801834A8(&this->skeletonInfo, gameplay_keep_Blob_0281DC);
    this->step = 0;
    this->actor.shape.rot.y = 0;
    this->skeletonInfo.frameCtrl.unk_C = (2.0f / 3.0f);
    CutsceneManager_Queue(CS_ID_GLOBAL_ELEGY);
}

void EffChange_Destroy(Actor* thisx, PlayState* play) {
    EffChange* this = THIS;

    func_8018349C(&this->skeletonInfo);
}

void EffChange_SetColors(EffChange* this, s32 arg1) {
    arg1 *= 6;
    this->primColors[0] = D_80A4C920[arg1];
    this->primColors[1] = D_80A4C920[arg1 + 1];
    this->primColors[2] = D_80A4C920[arg1 + 2];
    this->envColors[0] = D_80A4C920[arg1 + 3];
    this->envColors[1] = D_80A4C920[arg1 + 4];
    this->envColors[2] = D_80A4C920[arg1 + 5];
}

void func_80A4C5CC(EffChange* this, PlayState* play) {
    f32 phi_fv0;

    if (func_80183DE0(&this->skeletonInfo)) {
        Actor_Kill(&this->actor);
        CutsceneManager_Stop(CS_ID_GLOBAL_ELEGY);
        func_800FD2B4(play, 0.0f, 850.0f, 0.2f, 0.0f);
        return;
    }

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

    phi_fv0 = this->primColors[3] * (1.0f / 255.0f);
    if (phi_fv0 > 1.0f) {
        phi_fv0 = 1.0f;
    } else if (phi_fv0 < 0.0f) {
        phi_fv0 = 0.0f;
    }
    func_800FD2B4(play, phi_fv0, 850.0f, 0.2f, 0.0f);
    if (CutsceneManager_GetCurrentCsId() != CS_ID_GLOBAL_ELEGY) {
        if (CutsceneManager_IsNext(CS_ID_GLOBAL_ELEGY)) {
            CutsceneManager_Start(CS_ID_GLOBAL_ELEGY, &this->actor);
        } else {
            CutsceneManager_Queue(CS_ID_GLOBAL_ELEGY);
        }
    }
}

void EffChange_Update(Actor* thisx, PlayState* play) {
    EffChange* this = THIS;

    this->actionFunc(this, play);
}

void EffChange_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    Mtx* mtx;
    EffChange* this = THIS;

    AnimatedMat_DrawStepXlu(play, Lib_SegmentedToVirtual(&gameplay_keep_Matanimheader_028FEC), this->step);
    mtx = GRAPH_ALLOC(play->state.gfxCtx, this->skeletonInfo.unk_18->unk_1 * sizeof(Mtx));

    if (mtx != NULL) {
        Gfx_SetupDL25_Xlu(play->state.gfxCtx);
        Matrix_RotateYS((Camera_GetCamDirYaw(GET_ACTIVE_CAM(play)) + 0x8000), MTXMODE_APPLY);

        OPEN_DISPS(play->state.gfxCtx);

        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, this->primColors[0], this->primColors[1], this->primColors[2],
                        this->primColors[3]);
        gDPSetEnvColor(POLY_XLU_DISP++, this->envColors[0], this->envColors[1], this->envColors[2], 255);
        func_8018450C(play, &this->skeletonInfo, mtx, NULL, NULL, &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
