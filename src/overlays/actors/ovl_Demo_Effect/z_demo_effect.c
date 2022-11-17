/*
 * File: z_demo_effect.c
 * Overlay: ovl_Demo_Effect
 * Description: Various cutscene effects (blue warp in, Great Fairy vanish, etc.)
 */

#include "z_demo_effect.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_efc_tw/object_efc_tw.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((DemoEffect*)thisx)

void DemoEffect_Init(Actor* thisx, PlayState* play);
void DemoEffect_Destroy(Actor* thisx, PlayState* play);
void DemoEffect_Update(Actor* thisx, PlayState* play);

void func_808CD940(DemoEffect* this, PlayState* play);
void func_808CD998(DemoEffect* this, PlayState* play);
void func_808CDBDC(DemoEffect* this, PlayState* play);
void func_808CDCEC(DemoEffect* this, PlayState* play);
void func_808CDD70(DemoEffect* this, PlayState* play);
void func_808CDDE0(DemoEffect* this, PlayState* play);
void func_808CDFF8(Actor* thisx, PlayState* play);
void func_808CE078(Actor* thisx, PlayState* play2);

ActorInit Demo_Effect_InitVars = {
    /**/    ACTOR_DEMO_EFFECT,
    /**/    ACTORCAT_BG,
    /**/    FLAGS,
    /**/    GAMEPLAY_KEEP,
    /**/    sizeof(DemoEffect),
    /**/    DemoEffect_Init,
    /**/    DemoEffect_Destroy,
    /**/    DemoEffect_Update,
    /**/    NULL,
};

void DemoEffect_Init(Actor* thisx, PlayState* play) {
    static s16 sEffectTypeObjects[] = {
        OBJECT_EFC_TW, OBJECT_EFC_TW, OBJECT_EFC_TW, OBJECT_EFC_TW, GAMEPLAY_KEEP,
        GAMEPLAY_KEEP, GAMEPLAY_KEEP, GAMEPLAY_KEEP, GAMEPLAY_KEEP,
    };
    s32 pad;
    DemoEffect* this = THIS;
    s32 type = DEMO_EFFECT_GET_TYPE(&this->actor);
    s32 objectIndex;
    s32 pad2;
    Color_RGB8 colors[] = {
        { 200, 200, 0 }, { 255, 40, 100 }, { 50, 255, 0 }, { 0, 0, 255 }, { 255, 255, 80 },
    };

    if (sEffectTypeObjects[type] == GAMEPLAY_KEEP) {
        objectIndex = 0;
    } else {
        objectIndex = Object_GetIndex(&play->objectCtx, sEffectTypeObjects[type]);
    }

    if (objectIndex < 0) {
        // assert on debug
    } else {
        this->initObjectIndex = objectIndex;
    }

    Actor_SetScale(&this->actor, 0.2f);

    switch (type) {
        case DEMO_EFFECT_TYPE_0:
        case DEMO_EFFECT_TYPE_1:
            this->actor.flags |= ACTOR_FLAG_2000000;

        case DEMO_EFFECT_TYPE_2:
        case DEMO_EFFECT_TYPE_3:
            this->initDrawFunc = func_808CDFF8;
            this->initActionFunc = func_808CD998;
            this->envXluColor[0] = 0;
            this->envXluColor[1] = 100;
            this->envXluColor[2] = 255;
            SkelCurve_Clear(&this->skelCurve);
            this->timer = 0;
            break;

        case DEMO_EFFECT_TYPE_4:
        case DEMO_EFFECT_TYPE_5:
        case DEMO_EFFECT_TYPE_6:
        case DEMO_EFFECT_TYPE_7:
        case DEMO_EFFECT_TYPE_8:
            this->envXluColor[0] = colors[type - 4].r;
            this->envXluColor[1] = colors[type - 4].g;
            this->envXluColor[2] = colors[type - 4].b;
            Actor_SetScale(&this->actor, 0.0f);
            this->initDrawFunc = func_808CE078;
            this->initActionFunc = func_808CDDE0;
            this->timer = 0;
            break;

        default:
            break;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    this->actionFunc = func_808CD940;
}

void DemoEffect_Destroy(Actor* thisx, PlayState* play) {
    DemoEffect* this = THIS;

    switch (DEMO_EFFECT_GET_TYPE(&this->actor)) {
        case DEMO_EFFECT_TYPE_0:
        case DEMO_EFFECT_TYPE_1:
        case DEMO_EFFECT_TYPE_2:
        case DEMO_EFFECT_TYPE_3:
            SkelCurve_Destroy(play, &this->skelCurve);
            break;

        default:
            break;
    }
}

void func_808CD940(DemoEffect* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->initObjectIndex)) {
        this->actor.objBankIndex = this->initObjectIndex;
        this->actor.draw = this->initDrawFunc;
        this->actionFunc = this->initActionFunc;
    }
}

void func_808CD998(DemoEffect* this, PlayState* play) {
    s32 type = DEMO_EFFECT_GET_TYPE(&this->actor);

    if (SkelCurve_Init(play, &this->skelCurve, &object_efc_tw_Skel_0012E8, &object_efc_tw_CurveAnim_000050)) {}

    SkelCurve_SetAnim(&this->skelCurve, &object_efc_tw_CurveAnim_000050, 1.0f, 59.0f, 1.0f, 1.7f);
    SkelCurve_Update(play, &this->skelCurve);
    this->actionFunc = func_808CDCEC;

    switch (type) {
        case DEMO_EFFECT_TYPE_0:
            Actor_SetScale(&this->actor, 0.16800001f);
            break;

        case DEMO_EFFECT_TYPE_1:
            Actor_SetScale(&this->actor, 0.08400001f);
            break;

        case DEMO_EFFECT_TYPE_2:
            Actor_SetScale(&this->actor, 0.16800001f);
            break;

        case DEMO_EFFECT_TYPE_3:
            Actor_SetScale(&this->actor, 0.28f);
            break;

        default:
            Actor_SetScale(&this->actor, 0.014f);
            break;
    }
}

void func_808CDAD0(f32 alphaScale) {
    static u8 sAlphaTypes[] = { 1, 1, 2, 0, 1, 1, 2, 0, 1, 2, 0, 2, 1, 0, 1, 0, 2, 0, 2, 2, 0 };
    Vtx* vtx = Lib_SegmentedToVirtual(object_efc_tw_Vtx_000060);
    s32 i;
    u8 alphas[3];

    alphas[0] = 0;
    alphas[1] = (s32)(202.0f * alphaScale);
    alphas[2] = (s32)(255.0f * alphaScale);

    for (i = 0; i < ARRAY_COUNT(sAlphaTypes); i++) {
        if (sAlphaTypes[i] != 0) {
            vtx[i].v.cn[3] = alphas[sAlphaTypes[i]];
        }
    }
}

void func_808CDBDC(DemoEffect* this, PlayState* play) {
    s32 type = DEMO_EFFECT_GET_TYPE(&this->actor);
    f32 scale;
    f32 alphaScale;

    this->timer++;
    if (this->timer <= 100) {
        alphaScale = (100 - this->timer) * 0.01f;
        scale = alphaScale * 0.14f;

        switch (type) {
            case DEMO_EFFECT_TYPE_0:
                scale *= 1.2f;
                break;

            case DEMO_EFFECT_TYPE_1:
                scale *= 0.6f;
                break;

            case DEMO_EFFECT_TYPE_2:
                scale *= 1.2f;
                break;

            case DEMO_EFFECT_TYPE_3:
                scale *= 2.0f;
                break;

            default:
                break;
        }

        this->actor.scale.x = scale;
        this->actor.scale.z = scale;
        func_808CDAD0(alphaScale);
        func_800B8FE8(&this->actor, NA_SE_EV_TIMETRIP_LIGHT - SFX_FLAG);
    } else {
        func_808CDAD0(1.0f);
        Actor_Kill(&this->actor);
    }
}

void func_808CDCEC(DemoEffect* this, PlayState* play) {
    func_800B8FE8(&this->actor, NA_SE_EV_TIMETRIP_LIGHT - SFX_FLAG);

    if (SkelCurve_Update(play, &this->skelCurve)) {
        SkelCurve_SetAnim(&this->skelCurve, &object_efc_tw_CurveAnim_000050, 1.0f, 60.0f, 59.0f, 0.0f);
        this->actionFunc = func_808CDBDC;
        this->timer = 0;
    }
}

void func_808CDD70(DemoEffect* this, PlayState* play) {
    Actor_SetScale(&this->actor, this->actor.scale.x - 0.02f);

    this->timer++;
    if (this->actor.scale.x < 0.02f) {
        Actor_Kill(&this->actor);
    }
}

void func_808CDDE0(DemoEffect* this, PlayState* play) {
    Actor_SetScale(&this->actor, (this->actor.scale.x * 0.5f) + 0.2f);

    this->timer++;
    if (this->timer >= 3) {
        this->actionFunc = func_808CDD70;
    }
}

void DemoEffect_Update(Actor* thisx, PlayState* play) {
    DemoEffect* this = THIS;

    this->actionFunc(this, play);
}

s32 func_808CDE78(PlayState* play, SkelCurve* skelCurve, s32 limbIndex, Actor* thisx) {
    s32 pad;
    DemoEffect* this = THIS;
    u32 frames = play->gameplayFrames;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, this->envXluColor[0], this->envXluColor[1], this->envXluColor[2], 255);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, (frames * 6) % 1024, 255 - ((frames * 16) % 256), 0x100, 0x40, 1,
                                (frames * 4) % 512, 127 - ((frames * 12) % 128), 0x80, 0x20));

    CLOSE_DISPS(play->state.gfxCtx);

    if (limbIndex == 0) {
        s16* transform = skelCurve->jointTable[0];

        transform[2] = transform[0] = 1024;
        transform[1] = 1024;
    }

    return true;
}

void func_808CDFF8(Actor* thisx, PlayState* play) {
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    DemoEffect* this = THIS;

    OPEN_DISPS(gfxCtx);

    POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 25);

    Matrix_Scale(2.0f, 2.0f, 2.0f, MTXMODE_APPLY);
    SkelCurve_Draw(&this->actor, play, &this->skelCurve, func_808CDE78, NULL, 1, &this->actor);

    CLOSE_DISPS(gfxCtx);
}

void func_808CE078(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    DemoEffect* this = THIS;
    s16 zRot = (this->timer * 0x400) & 0xFFFF;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C2DC(play->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 255, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, this->envXluColor[0], this->envXluColor[1], this->envXluColor[2], 255);

    Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
    Matrix_Push();
    Matrix_RotateZS(zRot, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gEffFlash2DL);

    Matrix_Pop();
    Matrix_RotateZS(-zRot, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gEffFlash2DL);

    CLOSE_DISPS(play->state.gfxCtx);

    D_801F4E32 = 1;
    D_801F4E38.x = thisx->world.pos.x;
    D_801F4E38.y = thisx->world.pos.y;
    D_801F4E38.z = thisx->world.pos.z;

    D_801F4E44 = thisx->scale.x * 60.0f;
    D_801F4E48 = thisx->scale.x * 50.0f;
    D_801F4E4C = thisx->scale.x * 250.0f;
}
