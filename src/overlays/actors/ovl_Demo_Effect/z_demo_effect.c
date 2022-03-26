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

void DemoEffect_Init(Actor* thisx, GlobalContext* globalCtx);
void DemoEffect_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DemoEffect_Update(Actor* thisx, GlobalContext* globalCtx);

void func_808CD940(DemoEffect* this, GlobalContext* globalCtx);
void func_808CD998(DemoEffect* this, GlobalContext* globalCtx);
void func_808CDBDC(DemoEffect* this, GlobalContext* globalCtx);
void func_808CDCEC(DemoEffect* this, GlobalContext* globalCtx);
void func_808CDD70(DemoEffect* this, GlobalContext* globalCtx);
void func_808CDDE0(DemoEffect* this, GlobalContext* globalCtx);
void func_808CDFF8(Actor* thisx, GlobalContext* globalCtx);
void func_808CE078(Actor* thisx, GlobalContext* globalCtx2);

const ActorInit Demo_Effect_InitVars = {
    ACTOR_DEMO_EFFECT,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DemoEffect),
    (ActorFunc)DemoEffect_Init,
    (ActorFunc)DemoEffect_Destroy,
    (ActorFunc)DemoEffect_Update,
    (ActorFunc)NULL,
};

void DemoEffect_Init(Actor* thisx, GlobalContext* globalCtx) {
    static s16 D_808CE2C0[] = {
        OBJECT_EFC_TW, OBJECT_EFC_TW, OBJECT_EFC_TW, OBJECT_EFC_TW, GAMEPLAY_KEEP,
        GAMEPLAY_KEEP, GAMEPLAY_KEEP, GAMEPLAY_KEEP, GAMEPLAY_KEEP,
    };
    s32 pad;
    DemoEffect* this = THIS;
    s32 sp3C = DEMOEFFECT_GET_FF(&this->actor);
    s32 phi_v1;
    s32 pad2;
    Color_RGB8 sp24[] = {
        { 200, 200, 0 }, { 255, 40, 100 }, { 50, 255, 0 }, { 0, 0, 255 }, { 255, 255, 80 },
    };

    if (D_808CE2C0[sp3C] == 1) {
        phi_v1 = 0;
    } else {
        phi_v1 = Object_GetIndex(&globalCtx->objectCtx, D_808CE2C0[sp3C]);
    }

    if (phi_v1 >= 0) {
        this->unk_164 = phi_v1;
    }

    Actor_SetScale(&this->actor, 0.2f);

    switch (sp3C) {
        case 0:
        case 1:
            this->actor.flags |= ACTOR_FLAG_2000000;

        case 2:
        case 3:
            this->unk_174 = func_808CDFF8;
            this->unk_170 = func_808CD998;
            this->unk_168[0] = 0;
            this->unk_168[1] = 100;
            this->unk_168[2] = 255;
            SkelCurve_Clear(&this->skelCurve);
            this->unk_16C = 0;
            break;

        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            this->unk_168[0] = sp24[sp3C - 4].r;
            this->unk_168[1] = sp24[sp3C - 4].g;
            this->unk_168[2] = sp24[sp3C - 4].b;
            Actor_SetScale(&this->actor, 0.0f);
            this->unk_174 = func_808CE078;
            this->unk_170 = func_808CDDE0;
            this->unk_16C = 0;
            break;
    }

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    this->actionFunc = func_808CD940;
}

u8 D_808CE2D4[] = {
    1, 1, 2, 0, 1, 1, 2, 0, 1, 2, 0, 2, 1, 0, 1, 0, 2, 0, 2, 2, 0,
};

void DemoEffect_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    DemoEffect* this = THIS;

    switch (DEMOEFFECT_GET_FF(&this->actor)) {
        case 0:
        case 1:
        case 2:
        case 3:
            SkelCurve_Destroy(globalCtx, &this->skelCurve);
            break;
    }
}

void func_808CD940(DemoEffect* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->unk_164)) {
        this->actor.objBankIndex = this->unk_164;
        this->actor.draw = this->unk_174;
        this->actionFunc = this->unk_170;
    }
}

void func_808CD998(DemoEffect* this, GlobalContext* globalCtx) {
    s32 sp34 = DEMOEFFECT_GET_FF(&this->actor);

    if (SkelCurve_Init(globalCtx, &this->skelCurve, &object_efc_tw_Skel_0012E8, &object_efc_tw_CurveAnim_000050)) {}

    SkelCurve_SetAnim(&this->skelCurve, &object_efc_tw_CurveAnim_000050, 1.0f, 59.0f, 1.0f, 1.7f);
    SkelCurve_Update(globalCtx, &this->skelCurve);
    this->actionFunc = func_808CDCEC;

    switch (sp34) {
        case 0:
            Actor_SetScale(&this->actor, 0.16800001f);
            break;

        case 1:
            Actor_SetScale(&this->actor, 0.08400001f);
            break;

        case 2:
            Actor_SetScale(&this->actor, 0.16800001f);
            break;

        case 3:
            Actor_SetScale(&this->actor, 0.28f);
            break;

        default:
            Actor_SetScale(&this->actor, 0.014f);
            break;
    }
}

void func_808CDAD0(f32 arg0) {
    s32 i;
    Vtx* temp_v0 = Lib_SegmentedToVirtual(object_efc_tw_Vtx_000060);
    u8 sp24[3];

    sp24[0] = 0;
    sp24[1] = (s8)(202.0f * arg0);
    sp24[2] = (s8)(255.0f * arg0);

    for (i = 0; i < ARRAY_COUNT(D_808CE2D4); i++) {
        if (D_808CE2D4[i] != 0) {
            temp_v0[i].v.cn[3] = sp24[D_808CE2D4[i]];
        }
    }
}

void func_808CDBDC(DemoEffect* this, GlobalContext* globalCtx) {
    s32 params = DEMOEFFECT_GET_FF(&this->actor);
    f32 temp_f0;
    f32 temp_f12;

    this->unk_16C++;
    if (this->unk_16C <= 100) {
        temp_f12 = (100 - this->unk_16C) * 0.01f;
        temp_f0 = temp_f12 * 0.14f;

        switch (params) {
            case 0:
                temp_f0 *= 1.2f;
                break;

            case 1:
                temp_f0 *= 0.6f;
                break;

            case 2:
                temp_f0 *= 1.2f;
                break;

            case 3:
                temp_f0 *= 2.0f;
                break;
        }

        this->actor.scale.x = temp_f0;
        this->actor.scale.z = temp_f0;
        func_808CDAD0(temp_f12);
        func_800B8FE8(&this->actor, NA_SE_EV_TIMETRIP_LIGHT - SFX_FLAG);
    } else {
        func_808CDAD0(1.0f);
        Actor_MarkForDeath(&this->actor);
    }
}

void func_808CDCEC(DemoEffect* this, GlobalContext* globalCtx) {
    func_800B8FE8(&this->actor, NA_SE_EV_TIMETRIP_LIGHT - SFX_FLAG);

    if (SkelCurve_Update(globalCtx, &this->skelCurve)) {
        SkelCurve_SetAnim(&this->skelCurve, &object_efc_tw_CurveAnim_000050, 1.0f, 60.0f, 59.0f, 0.0f);
        this->actionFunc = func_808CDBDC;
        this->unk_16C = 0;
    }
}

void func_808CDD70(DemoEffect* this, GlobalContext* globalCtx) {
    Actor_SetScale(&this->actor, this->actor.scale.x - 0.02f);

    this->unk_16C++;
    if (this->actor.scale.x < 0.02f) {
        Actor_MarkForDeath(&this->actor);
    }
}

void func_808CDDE0(DemoEffect* this, GlobalContext* globalCtx) {
    Actor_SetScale(&this->actor, (this->actor.scale.x * 0.5f) + 0.2f);

    this->unk_16C++;
    if (this->unk_16C >= 3) {
        this->actionFunc = func_808CDD70;
    }
}

void DemoEffect_Update(Actor* thisx, GlobalContext* globalCtx) {
    DemoEffect* this = THIS;

    this->actionFunc(this, globalCtx);
}

s32 func_808CDE78(GlobalContext* globalCtx, SkelAnimeCurve* skelCuve, s32 limbIndex, Actor* thisx) {
    s32 pad;
    DemoEffect* this = THIS;
    u32 sp4C = globalCtx->gameplayFrames;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 170, 255, 255, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, this->unk_168[0], this->unk_168[1], this->unk_168[2], 255);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, (sp4C * 6) % 1024, 255 - ((sp4C * 16) % 256), 0x100, 0x40,
                                1, (sp4C * 4) % 512, 127 - ((sp4C * 12) % 128), 0x80, 0x20));

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if (limbIndex == 0) {
        LimbTransform* transform = skelCuve->transforms;

        transform->scale.x = 0x400;
        transform->scale.y = 0x400;
        transform->scale.z = transform->scale.x;
    }

    return true;
}

void func_808CDFF8(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    POLY_XLU_DISP = Gfx_CallSetupDL(POLY_XLU_DISP, 25);

    Matrix_Scale(2.0f, 2.0f, 2.0f, MTXMODE_APPLY);
    SkelCurve_Draw(thisx, globalCtx, &THIS->skelCurve, func_808CDE78, NULL, 1, thisx);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_808CE078(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    DemoEffect* this = THIS;
    s16 sp46 = (this->unk_16C * 0x400) & 0xFFFF;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 255, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, this->unk_168[0], this->unk_168[1], this->unk_168[2], 255);

    Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);
    Matrix_StatePush();
    Matrix_InsertZRotation_s(sp46, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_023288);

    Matrix_StatePop();
    Matrix_InsertZRotation_s(sp46 * -1, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_023288);

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    D_801F4E32 = 1;
    D_801F4E38.x = thisx->world.pos.x;
    D_801F4E38.y = thisx->world.pos.y;
    D_801F4E38.z = thisx->world.pos.z;

    D_801F4E44 = thisx->scale.x * 60.0f;
    D_801F4E48 = thisx->scale.x * 50.0f;
    D_801F4E4C = thisx->scale.x * 250.0f;
}
