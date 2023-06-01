/*
 * File: z_eff_stk.c
 * Overlay: ovl_Eff_Stk
 * Description: Skullkid Effects (calling down moon / cursing Link)
 */

#include "z_eff_stk.h"
#include "objects/object_stk2/object_stk2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EffStk*)thisx)

void EffStk_Init(Actor* thisx, PlayState* play);
void EffStk_Destroy(Actor* thisx, PlayState* play);
void EffStk_Update(Actor* thisx, PlayState* play);
void EffStk_Draw(Actor* thisx, PlayState* play);

ActorInit Eff_Stk_InitVars = {
    ACTOR_EFF_STK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_STK2,
    sizeof(EffStk),
    (ActorFunc)EffStk_Init,
    (ActorFunc)EffStk_Destroy,
    (ActorFunc)EffStk_Update,
    (ActorFunc)EffStk_Draw,
};

void func_80BF0DE0(EffStk* arg0, PlayState* arg1);

void EffStk_Init(Actor* thisx, PlayState* play) {
    EffStk* this = (EffStk*)thisx;
    Actor_SetScale(&this->actor, 0.2f);
    this->actionFunc = func_80BF0DE0;
}

void EffStk_Destroy(Actor* thisx, PlayState* play) {
    EffStk* this = (EffStk*)thisx;
}

void func_80BF0DE0(EffStk* arg0, PlayState* arg1) {
    s16 temp_v0;
    s16 temp_v0_2;
    u16 temp_v1;

    if (Cutscene_IsCueInChannel(arg1, 0x200U) != 0) {
        temp_v1 = arg1->csCtx.actorCues[Cutscene_GetCueChannel(arg1, 0x200U)]->id;
        switch (temp_v1) {
            case 2:
                temp_v0_2 = arg0->unk146;
                arg0->actor.draw = EffStk_Draw;
                if (temp_v0_2 < 0x3C00) {
                    arg0->unk146 = temp_v0_2 + 0x400;
                    arg0->unk148 = Math_SinS(arg0->unk146) * -630.0f;
                }
                arg0->unk144 += 1;
                break;
            case 3:
                temp_v0 = arg0->unk146;
                arg0->actor.draw = EffStk_Draw;
                if (temp_v0 < 0x3C00) {
                    arg0->unk146 = temp_v0 + 0x400;
                    arg0->unk148 = Math_SinS(arg0->unk146) * -630.0f;
                }
                arg0->unk144 -= 1;
                break;
            default:
                arg0->actor.draw = NULL;
                arg0->unk146 = 0;
                arg0->unk148 = 0.0f;
                break;
        }
    }
}

void EffStk_Update(Actor* thisx, PlayState* play) {
    EffStk* this = (EffStk*)thisx;
    this->actionFunc(this, play);
}

extern s32 D_06008920;
extern s32 D_06008A38;

void EffStk_Draw(Actor* thisx, PlayState* play) {
    EffStk* this = (EffStk*)thisx;
    s32 pad;
    Camera* camera;
    Vec3f eye;
    Vec3f quakeOffset;

    camera = play->cameraPtrs[play->activeCamId];
    eye = camera->eye;

    Camera_GetQuakeOffset(&quakeOffset, camera);

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    Matrix_Translate(eye.x + quakeOffset.x, eye.y + quakeOffset.y, eye.z + quakeOffset.z, MTXMODE_NEW);
    Matrix_Scale(0.2f, 0.2f, 0.2f, MTXMODE_APPLY);
    Matrix_ReplaceRotation(&play->billboardMtxF);
    Matrix_Translate(0.0f, 0.0f, this->unk148, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    AnimatedMat_DrawAlphaStep(play, Lib_SegmentedToVirtual(object_stk2_Matanimheader_009F60), 1.0f, (u32)this->unk144);
    gDPSetColorDither(POLY_XLU_DISP++, G_CD_NOISE);
    gDPSetAlphaDither(POLY_XLU_DISP++, G_AD_NOISE);
    gSPDisplayList(POLY_XLU_DISP++, &D_06008920);
    gSPDisplayList(POLY_XLU_DISP++, &D_06008A38);

    CLOSE_DISPS(play->state.gfxCtx);
}
