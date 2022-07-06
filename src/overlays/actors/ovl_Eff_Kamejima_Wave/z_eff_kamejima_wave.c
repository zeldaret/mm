/*
 * File: z_eff_kamejima_wave.c
 * Overlay: ovl_Eff_Kamejima_Wave
 * Description: Wave Created by Turtle Awakening
 */

#include "z_eff_kamejima_wave.h"
#include "objects/object_kamejima/object_kamejima.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EffKamejimaWave*)thisx)

void EffKamejimaWave_Init(Actor* thisx, PlayState* play);
void EffKamejimaWave_Destroy(Actor* thisx, PlayState* play);
void EffKamejimaWave_Update(Actor* thisx, PlayState* play);

void func_80BCEC6C(EffKamejimaWave* this, PlayState* play);
void func_80BCEDE0(EffKamejimaWave* this, PlayState* play);
void func_80BCEBC0(EffKamejimaWave* this, PlayState* play);
void func_80BCEF0C(Actor* thisx, PlayState* play);
void func_80BCED34(EffKamejimaWave* this, PlayState* play);
void func_80BCEEBC(u8);

const ActorInit Eff_Kamejima_Wave_InitVars = {
    ACTOR_EFF_KAMEJIMA_WAVE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KAMEJIMA,
    sizeof(EffKamejimaWave),
    (ActorFunc)EffKamejimaWave_Init,
    (ActorFunc)EffKamejimaWave_Destroy,
    (ActorFunc)EffKamejimaWave_Update,
    (ActorFunc)NULL,
};

static Color_RGBA8 D_80BCF090[] = {
    { 255, 240, 255, 255 },
    { 255, 255, 255, 255 },
    { 255, 240, 230, 255 },
    { 140, 170, 220, 255 },
};
static Color_RGBA8 D_80BCF0A0[] = {
    { 130, 80, 90, 255 },
    { 90, 120, 130, 255 },
    { 130, 80, 70, 255 },
    { 40, 60, 110, 255 },
};

s16 D_80BCF1C0;
u8 D_80BCF1C1;
AnimatedMaterial* D_80BCF1C4;

void EffKamejimaWave_Init(Actor* thisx, PlayState* play) {
    EffKamejimaWave* this = THIS;

    Actor_SetScale(&this->actor, 0.2f);
    this->actor.scale.y = 0.0f;
    if ((this->actor.params & 0xF) == 1) {
        this->actionFunc = func_80BCEDE0;
        D_80BCF1C0 = 0xFF;
    } else {
        this->actionFunc = func_80BCEC6C;
        D_80BCF1C0 = 0xFF;
    }
    D_80BCF1C4 = Lib_SegmentedToVirtual(object_kamejima_Matanimheader_001AF0);
}

void EffKamejimaWave_Destroy(Actor* thisx, PlayState* play) {
}

void func_80BCEBC0(EffKamejimaWave* this, PlayState* play) {
    this->actor.scale.y += this->unk144;
    this->unk144 = this->unk144 - 0.003f;
    this->actor.shape.rot.x += 0x64;
    if (this->unk144 < 0.0f) {
        this->actor.scale.x += 0.003f;
    }
    if (this->unk144 < -0.01f) {
        this->unk144 = -0.01f;
    }
    if (this->actor.scale.y < 0.0f) {
        this->actor.scale.y = 0.0f;
        this->actor.scale.x = 0.2f;
        this->actionFunc = func_80BCEC6C;
        this->actor.draw = NULL;
    }
}

void func_80BCEC6C(EffKamejimaWave* this, PlayState* play) {
    if (Cutscene_CheckActorAction(play, 0x1E0U)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, 0x1E0));
        if (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x1E0U)]->action == 2) {
            this->unk144 = 0.05f;
            this->actionFunc = func_80BCEBC0;
            this->actor.draw = func_80BCEF0C;
            D_80BCF1C0 = 0xFF;
            this->actor.shape.rot.x = 0;
            Actor_PlaySfxAtPos(&this->actor, 0x28D7U);
        }
    } else {
        this->actor.draw = NULL;
    }
}

void func_80BCED34(EffKamejimaWave* this, PlayState* play) {
    this->actor.scale.y += this->unk144;
    this->unk144 = this->unk144 - 0.002f;
    this->actor.shape.rot.x += 0x8C;
    if (this->unk144 < 0.0f) {
        this->actor.scale.x += 0.002f;
    }
    if (this->unk144 < 0.0f) {
        this->unk144 = 0;
    }
    if (D_80BCF1C0 >= 4) {
        D_80BCF1C0 -= 4;
        return;
    }
    this->actor.scale.y = 0.0f;
    this->actionFunc = func_80BCEDE0;
    this->actor.draw = NULL;
}

void func_80BCEDE0(EffKamejimaWave* this, PlayState* play) {
    if (Cutscene_CheckActorAction(play, 0x1F6U)) {
        Cutscene_ActorTranslateAndYaw(&this->actor, play, Cutscene_GetActorActionIndex(play, 0x1F6));
        if (play->csCtx.actorActions[Cutscene_GetActorActionIndex(play, 0x1F6U)]->action == 2) {
            this->unk144 = 0.03f;
            this->actor.scale.x = 0.35f;
            this->actionFunc = func_80BCED34;
            this->actor.draw = func_80BCEF0C;
            this->actor.shape.rot.x = 0;
        }
    } else {
        this->actor.draw = NULL;
    }
}

void EffKamejimaWave_Update(Actor* thisx, PlayState* play) {
    EffKamejimaWave* this = THIS;

    this->actionFunc(this, play);
}

void func_80BCEEBC(u8 arg0) {
    Vtx* vtx = Lib_SegmentedToVirtual(&object_kamejima_Vtx);

    vtx[2].v.cn[3] = arg0;
    vtx[6].v.cn[3] = arg0;
    vtx[8].v.cn[3] = arg0;
    vtx[9].v.cn[3] = arg0;
    vtx[12].v.cn[3] = arg0;
    vtx[16].v.cn[3] = arg0;
    vtx[18].v.cn[3] = arg0;
    vtx[19].v.cn[3] = arg0;
}

void func_80BCEF0C(Actor* thisx, PlayState* play) {
    Color_RGBA8 primColor;
    Color_RGBA8 envColor;

    func_800FE7A8(D_80BCF090, &primColor);
    func_800FE7A8(D_80BCF0A0, &envColor);
    func_80BCEEBC(D_80BCF1C1);

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);
    Matrix_Scale(6.0f, 5.0f, 5.0f, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    AnimatedMat_Draw(play, D_80BCF1C4);
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, primColor.r, primColor.g, primColor.b, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, envColor.r, envColor.g, envColor.b, 255);
    gSPDisplayList(POLY_XLU_DISP++, object_kamejima_DL_000140);

    CLOSE_DISPS(play->state.gfxCtx);
}
