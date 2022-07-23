/*
 * File: z_en_test6.c
 * Overlay: ovl_En_Test6
 * Description: Song of Time effects (Return to DotFD, invert, skip forward)
 */

#include "z_en_test6.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_200000 | ACTOR_FLAG_2000000)

#define THIS ((EnTest6*)thisx)

void EnTest6_Init(Actor* thisx, PlayState* play);
void EnTest6_Destroy(Actor* thisx, PlayState* play);
void EnTest6_Update(Actor* thisx, PlayState* play);
void EnTest6_Draw(Actor* thisx, PlayState* play);

struct EnTest6Struct;

typedef void (*EnTest6StructFunc)(EnTest6*, PlayState*, struct EnTest6Struct*);

typedef struct EnTest6Struct {
    /* 0x00 */ s32 unk_00;
    /* 0x04 */ f32 unk_04;
    /* 0x08 */ f32 unk_08;
    /* 0x0C */ f32 unk_0C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ EnTest6StructFunc unk_14;
} EnTest6Struct; // size = 0x18

void func_80A90D34(EnTest6* this, PlayState* play, EnTest6Struct* ptr);
void func_80A90FC0(EnTest6* this, PlayState* play, EnTest6Struct* ptr);
void EnTest6_SetupAction(EnTest6* this, EnTest6ActionFunc actionFunc);
void func_80A9156C(EnTest6* this, PlayState* play);
void func_80A91690(EnTest6* this, PlayState* play);
void func_80A91760(EnTest6* this, PlayState* play);
void func_80A920C8(EnTest6* this, PlayState* play);
void func_80A92188(EnTest6* this, PlayState* play);
void func_80A92950(EnTest6* this, PlayState* play);

EnTest6Struct D_80A94910[12];

const ActorInit En_Test6_InitVars = {
    ACTOR_EN_TEST6,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest6),
    (ActorFunc)EnTest6_Init,
    (ActorFunc)EnTest6_Destroy,
    (ActorFunc)EnTest6_Update,
    (ActorFunc)EnTest6_Draw,
};

u8 D_80A93E80[] = {
    0x00, 0x0D, 0x01, 0xA8, 0x00, 0x00, 0x00, 0x64, 0x04, 0x64, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x15, 0xFF, 0xED, 0x00,
    0x00, 0x04, 0x64, 0x00, 0x12, 0x00, 0x00, 0x00, 0x15, 0xFF, 0xED, 0x00, 0x00, 0x04, 0x64, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x15, 0xFF, 0xED, 0x00, 0x00, 0x04, 0x64, 0x00, 0x11, 0xFF, 0xE6, 0xFF, 0xFB, 0xFF, 0xE0, 0x00, 0x00, 0x04,
    0x64, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x12, 0xFF, 0xE0, 0x00, 0x00, 0x04, 0x64, 0x00, 0x0E, 0x00, 0x01, 0x00, 0x16,
    0xFF, 0xE5, 0x00, 0x00, 0x04, 0x64, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xFB, 0x00, 0x00, 0x04, 0x64, 0x00,
    0x07, 0x00, 0x10, 0x00, 0x1D, 0xFF, 0xB3, 0x00, 0x00, 0x04, 0x64, 0x00, 0x03, 0x00, 0x01, 0x00, 0x13, 0x00, 0x6F,
    0x00, 0x00, 0x04, 0x64, 0x00, 0x03, 0xFF, 0xC5, 0x00, 0x15, 0x00, 0x5B, 0x00, 0x00, 0x04, 0x64, 0x00, 0x03, 0xFF,
    0xED, 0x00, 0x3B, 0x00, 0x54, 0x00, 0x00, 0x04, 0x64, 0x00, 0x88, 0xFF, 0xED, 0x00, 0x3B, 0x00, 0x54, 0x00, 0x00,
    0x04, 0x64, 0x00, 0x6C, 0xFF, 0xEF, 0x00, 0x39, 0x00, 0x52, 0x00, 0x00, 0x04, 0x64, 0x00, 0x0D, 0x00, 0x00, 0x00,
    0x32, 0x02, 0xA9, 0x00, 0x00, 0x04, 0x64, 0x00, 0x12, 0x00, 0x00, 0x00, 0x32, 0x02, 0xA9, 0x00, 0x00, 0x04, 0x64,
    0x00, 0x10, 0x00, 0x00, 0x00, 0x32, 0x02, 0xA9, 0x00, 0x00, 0x04, 0x64, 0x00, 0x11, 0xFF, 0x98, 0x01, 0x77, 0x01,
    0x59, 0x00, 0x00, 0x04, 0x64, 0x00, 0x0F, 0x00, 0x00, 0xFF, 0xC2, 0x01, 0x21, 0x00, 0x00, 0x04, 0x64, 0x00, 0x0E,
    0xFF, 0xD1, 0x00, 0x7D, 0x00, 0xCD, 0x00, 0x00, 0x04, 0x64, 0x00, 0x0C, 0xFF, 0xC6, 0xFF, 0xEF, 0x00, 0xC7, 0x00,
    0x00, 0x04, 0x64, 0x00, 0x07, 0x00, 0x10, 0x00, 0x35, 0x00, 0xD3, 0x00, 0x00, 0x04, 0x64, 0x00, 0x03, 0xFF, 0xE1,
    0x00, 0x3F, 0x02, 0x6F, 0x00, 0x00, 0x04, 0x64, 0x00, 0x03, 0xFE, 0xAB, 0x01, 0xD0, 0x02, 0x1E, 0x00, 0x00, 0x04,
    0x64, 0x00, 0x03, 0xFE, 0xAB, 0x01, 0xD0, 0x02, 0x1E, 0x00, 0x00, 0x04, 0x64, 0x00, 0x88, 0xFE, 0xAB, 0x01, 0xD0,
    0x02, 0x1E, 0x00, 0x00, 0x04, 0x64, 0x00, 0x6C, 0xFE, 0xAD, 0x01, 0xCE, 0x02, 0x1C, 0x00, 0x00, 0x00, 0x0F, 0x00,
    0x0A, 0x00, 0x46, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x0A, 0x00, 0x46, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x0A, 0x00, 0x46,
    0x00, 0x00, 0x00, 0x0A, 0x00, 0x02, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x0A, 0xFF, 0xEC, 0x00, 0x37, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x06, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x05, 0xFF, 0xFB,
    0x00, 0x32, 0x00, 0x00, 0x00, 0x02, 0xFF, 0xDC, 0x00, 0x6C, 0x00, 0x00, 0x00, 0x02, 0xFF, 0xD8, 0x00, 0x78, 0x00,
    0x00, 0x00, 0x02, 0xFF, 0xC4, 0x00, 0x78, 0x00, 0x00, 0x00, 0x02, 0xFF, 0xBA, 0x00, 0x82, 0x00, 0x00, 0x00, 0x02,
    0xFF, 0xB0, 0x00, 0x8C, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x04,
};

TexturePtr D_80A9402C[] = {
    NULL,
    gameplay_keep_Tex_05B6F0,
    gameplay_keep_Tex_05CEF0,
    gameplay_keep_Tex_0607C0,
    gameplay_keep_Tex_060FC0,
    gameplay_keep_Tex_061FC0,
    gameplay_keep_Tex_061FE0,
};

Color_RGB8 D_80A94048 = { 230, 230, 220 };
Color_RGB8 D_80A9404C = { 120, 120, 100 };
Color_RGB8 D_80A94050 = { 0, 0, 0 };

s16 D_80A94054 = 500;
s16 D_80A94058 = 1500;

static Vec3f sSubCamUp = { 0.0f, 1.0f, 0.0f };

Color_RGB8 D_80A94068 = { 225, 230, 225 };
Color_RGB8 D_80A9406C = { 120, 120, 100 };
Color_RGB8 D_80A94070 = { 0, 0, 0 };

s16 D_80A94074 = 940;
s16 D_80A94078 = 2000;

void func_80A90730(EnTest6* this, PlayState* play) {
    s32 i;
    Player* player = GET_PLAYER(play);
    s32 phi_s0;
    f32 phi_f24;

    this->actor.home.pos = player->actor.world.pos;
    this->actor.home.rot = player->actor.shape.rot;

    switch (ENTEST6_GET(&this->actor)) {
        case ENTEST6_24:
        case ENTEST6_25:
            func_80A91690(this, play);
            ActorCutscene_SetIntentToPlay(play->playerActorCsIds[8]);
            return;

        case ENTEST6_26:
            func_80A920C8(this, play);
            ActorCutscene_SetIntentToPlay(play->playerActorCsIds[8]);
            return;
    }

    phi_s0 = 0;
    phi_f24 = -900.0f;

    if (gSaveContext.eventInf[7] & 1) {
        for (i = 0; i < 6; i++) {
            D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 5;
        }
        D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 5;
        D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 6;
        phi_s0 |= 1;
    }

    if (gSaveContext.eventInf[7] & 0x10) {
        D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 1;
        D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 1;
        if (!(phi_s0 & 1)) {
            D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 1;
            D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 1;
        }
        phi_s0 |= 0x10;
    }

    if (gSaveContext.eventInf[7] & 2) {
        D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 2;
        D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 2;
        if (!(phi_s0 & 1)) {
            D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 2;
            D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 2;
        }
        phi_s0 |= 2;
    }

    if (gSaveContext.eventInf[7] & 4) {
        D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 3;
        if (!(phi_s0 & (0x10 | 0x2 | 0x1))) {
            D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 3;
        }
        phi_s0 |= 4;
    }

    if (gSaveContext.eventInf[7] & 8) {
        D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 4;
        if (!(phi_s0 & (0x10 | 0x2 | 0x1))) {
            D_80A94910[(s32)(Rand_ZeroOne() * ARRAY_COUNT(D_80A94910))].unk_00 = 4;
        }
    }

    for (i = 0; i < ARRAY_COUNT(D_80A94910); i++) {
        D_80A94910[i].unk_08 = ((2.0f * Rand_ZeroOne()) - 1.0f) * 80.0f;
        D_80A94910[i].unk_10 = ((2.0f * Rand_ZeroOne()) - 1.0f) * 80.0f;
        D_80A94910[i].unk_0C = (((2.0f * Rand_ZeroOne()) - 1.0f) * 40.0f) + phi_f24;
        D_80A94910[i].unk_04 = -10.0f;
        if (D_80A94910[i].unk_00 < 5) {
            D_80A94910[i].unk_14 = func_80A90D34;
        } else {
            D_80A94910[i].unk_14 = func_80A90FC0;
        }
        phi_f24 += 50.0f;
    }
}

void func_80A90C08(s16 arg0) {
    func_8016566C(arg0);
}

void func_80A90C34(void) {
    func_80165690();
}

void func_80A90C54(PlayState* play, f32 arg1) {
    play->envCtx.fillScreen = 1;
    play->envCtx.screenFillColor[0] = 250;
    play->envCtx.screenFillColor[1] = 250;
    play->envCtx.screenFillColor[2] = 250;
    play->envCtx.screenFillColor[3] = 255.0f * arg1;
}

void func_80A90D20(PlayState* play) {
    play->envCtx.fillScreen = 0;
}

void func_80A90D34(EnTest6* this, PlayState* play, EnTest6Struct* ptr) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    if (ptr->unk_00 != 0) {
        Matrix_Translate(ptr->unk_08 * ptr->unk_04, ptr->unk_0C, ptr->unk_10 * ptr->unk_04, MTXMODE_NEW);
        Matrix_Scale(ptr->unk_04 * 0.02f, ptr->unk_04 * 0.02f, ptr->unk_04 * 0.02f, MTXMODE_APPLY);
        POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
        POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A9402C[ptr->unk_00]));
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_05F6F0);
    }

    Matrix_Translate(ptr->unk_08 * ptr->unk_04, ptr->unk_0C, ptr->unk_10 * ptr->unk_04, MTXMODE_NEW);
    Matrix_Scale(2.0f * ptr->unk_04, 2.0f * ptr->unk_04, 2.0f * ptr->unk_04, MTXMODE_APPLY);
    Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
    Matrix_RotateZS(play->state.frames * 512, MTXMODE_APPLY);
    Matrix_Translate(0.0f, 0.0f, 2.0f, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    func_8012C2DC(play->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 210, 210, 230, 128);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, 0);
    gSPClearGeometryMode(POLY_XLU_DISP++, G_FOG | G_LIGHTING);
    gSPDisplayList(POLY_XLU_DISP++, gEffSparklesDL);
    gSPSetGeometryMode(POLY_XLU_DISP++, G_FOG | G_LIGHTING);

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80A90FC0(EnTest6* this, PlayState* play, EnTest6Struct* ptr) {
    s32 pad;
    Gfx* gfx = GRAPH_ALLOC(play->state.gfxCtx, sizeof(Gfx) * 2);
    Gfx* gfx2 = gfx;
    Hilite* sp70;
    Vec3f sp64;

    sp64.x = ptr->unk_08 * ptr->unk_04;
    sp64.y = ptr->unk_0C;
    sp64.z = ptr->unk_10 * ptr->unk_04;

    sp70 = func_800BCBF4(&sp64, play);

    OPEN_DISPS(play->state.gfxCtx);

    if (gfx != NULL) {
        func_8012C28C(play->state.gfxCtx);

        gDPSetTileSize(gfx++, 1, sp70->h.x1 & 0xFFFF, sp70->h.y1 & 0xFFFF, (sp70->h.x1 + 60) & 0xFFFF,
                       (sp70->h.y1 + 60) & 0xFFFF);
        gSPEndDisplayList(gfx);

        gSPSegment(POLY_OPA_DISP++, 0x07, gfx2);

        Matrix_Translate(sp64.x, sp64.y, sp64.z, MTXMODE_NEW);
        Matrix_Scale(ptr->unk_04 * 0.018f, ptr->unk_04 * 0.018f, ptr->unk_04 * 0.018f, MTXMODE_APPLY);
        Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(D_80A9402C[ptr->unk_00]));
        gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_0622C0);
    }

    Matrix_Translate(ptr->unk_08 * ptr->unk_04, ptr->unk_0C, ptr->unk_10 * ptr->unk_04, MTXMODE_NEW);
    Matrix_Scale(ptr->unk_04 * 2.5f, ptr->unk_04 * 2.5f, ptr->unk_04 * 2.5f, MTXMODE_APPLY);
    Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
    Matrix_RotateZS(play->state.frames * 256, MTXMODE_APPLY);
    Matrix_Translate(0.0f, 0.0f, 4.0f, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    func_8012C2DC(play->state.gfxCtx);

    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 220, 220, 230, 192);
    gDPSetEnvColor(POLY_XLU_DISP++, 128, 128, 128, 0);
    gSPClearGeometryMode(POLY_XLU_DISP++, G_FOG | G_LIGHTING);
    gSPDisplayList(POLY_XLU_DISP++, gEffSparklesDL);
    gSPSetGeometryMode(POLY_XLU_DISP++, G_FOG | G_LIGHTING);

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnTest6_SetupAction(EnTest6* this, EnTest6ActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnTest6_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnTest6* this = THIS;
    s32 i;

    if (((ENTEST6_GET(&this->actor) == ENTEST6_24) || (ENTEST6_GET(&this->actor) == ENTEST6_25) ||
         (ENTEST6_GET(&this->actor) == ENTEST6_26)) &&
        (play->playerActorCsIds[8] == -1)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    for (i = 0; i < ARRAY_COUNT(this->lights); i++) {
        Lights_PointNoGlowSetInfo(&this->lights[i].info, this->actor.world.pos.x, (s32)this->actor.world.pos.y - 20,
                                  this->actor.world.pos.z, 255, 255, 180, -1);
        this->lights[i].node = LightContext_InsertLight(play, &play->lightCtx, &this->lights[i].info);
    }

    this->unk_286 = 0;
    this->unk_274 = 0;
    this->unk_278 = 0;
    this->unk_276 = 99;
    func_80A90730(this, play);
    EnTest6_SetupAction(this, func_80A9156C);
}

void EnTest6_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnTest6* this = THIS;
    s32 i;

    play->envCtx.lightSettings.ambientColor[0] = 0;
    play->envCtx.lightSettings.ambientColor[1] = 0;
    play->envCtx.lightSettings.ambientColor[2] = 0;
    play->envCtx.lightSettings.diffuseColor1[0] = 0;
    play->envCtx.lightSettings.diffuseColor1[1] = 0;
    play->envCtx.lightSettings.diffuseColor1[2] = 0;
    play->envCtx.lightSettings.diffuseColor2[0] = 0;
    play->envCtx.lightSettings.diffuseColor2[1] = 0;
    play->envCtx.lightSettings.diffuseColor2[2] = 0;
    play->envCtx.lightSettings.fogColor[0] = 0;
    play->envCtx.lightSettings.fogColor[1] = 0;
    play->envCtx.lightSettings.fogColor[2] = 0;
    play->envCtx.lightSettings.fogNear = 0;
    play->envCtx.lightSettings.fogFar = 0;
    play->envCtx.fillScreen = 0;

    for (i = 0; i < ARRAY_COUNT(this->lights); i++) {
        LightContext_RemoveLight(play, &play->lightCtx, this->lights[i].node);
    }
}

void func_80A9156C(EnTest6* this, PlayState* play) {
    switch (ENTEST6_GET(&this->actor)) {
        case ENTEST6_24:
        case ENTEST6_25:
            if (!ActorCutscene_GetCanPlayNext(play->playerActorCsIds[8])) {
                ActorCutscene_SetIntentToPlay(play->playerActorCsIds[8]);
            } else {
                ActorCutscene_Start(play->playerActorCsIds[8], NULL);
                this->subCamId = ActorCutscene_GetCurrentSubCamId(play->playerActorCsIds[8]);
                EnTest6_SetupAction(this, func_80A91760);
            }
            break;

        case ENTEST6_26:
            if (!ActorCutscene_GetCanPlayNext(play->playerActorCsIds[8])) {
                ActorCutscene_SetIntentToPlay(play->playerActorCsIds[8]);
            } else {
                ActorCutscene_Start(play->playerActorCsIds[8], NULL);
                this->subCamId = ActorCutscene_GetCurrentSubCamId(play->playerActorCsIds[8]);
                EnTest6_SetupAction(this, func_80A92188);
            }
            break;

        default:
            gSaveContext.save.daysElapsed = 0;
            gSaveContext.save.day = false;
            gSaveContext.save.time = CLOCK_TIME(6, 0) - 1;
            EnTest6_SetupAction(this, func_80A92950);
            break;
    }
}

void func_80A91690(EnTest6* this, PlayState* play) {
    this->unk_274 = 90;
    this->unk_27A = 100;
    this->unk_286 = 0;
    if (ENTEST6_GET(&this->actor) == ENTEST6_25) {
        play_sound(NA_SE_SY_TIME_CONTROL_SLOW);
    } else if (ENTEST6_GET(&this->actor) == ENTEST6_24) {
        play_sound(NA_SE_SY_TIME_CONTROL_NORMAL);
    }
}

void func_80A916F0(EnTest6* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->actor.freezeTimer = 0;
    play->unk_18844 = 0;
    ActorCutscene_Stop(play->playerActorCsIds[8]);
    func_800B7298(play, NULL, 6);
    func_80A90C34();
    Distortion_ClearType(0x20);
    Actor_MarkForDeath(&this->actor);
}

void func_80A91760(EnTest6* this, PlayState* play) {
    Input* input = CONTROLLER1(&play->state);
    s16 temp_s0;
    Player* player = GET_PLAYER(play);
    Camera* mainCam;
    Vec3f subCamAt;
    Vec3f subCamEye;
    Vec3f sp54;
    s32 i;
    f32 sp4C;
    Camera* subCam = Play_GetCamera(play, this->subCamId);

    mainCam = Play_GetCamera(play, CAM_ID_MAIN);

    switch (this->unk_274) {
        case 90:
            this->unk_276 = 2;
            this->unk_15C = 0.0f;
            this->unk_14C = 0.1f;
            this->unk_282 = 0;
            this->unk_278 = 0;
            this->unk_274 = 91;
            break;

        case 91:
            this->unk_15C += this->unk_14C;
            func_800FD59C(play, &D_80A9404C, this->unk_15C);
            func_800FD5E0(play, &D_80A94050, this->unk_15C);
            func_800FD654(play, &D_80A94048, this->unk_15C);
            func_800FD698(play, D_80A94054, D_80A94058, this->unk_15C);

            if (this->unk_27A == 90) {
                this->unk_282 = 0;
                if (ENTEST6_GET(&this->actor) == ENTEST6_24) {
                    this->unk_27C = 0x200;
                    this->unk_150 = 0.0f;
                    sp4C = -100.0f;
                } else {
                    this->unk_27C = 0x570;
                    this->unk_150 = 110.0f;
                    sp4C = 100.0f;
                }
                this->unk_14C = 1.0f;

                for (i = 0; i < ARRAY_COUNT(this->unk_20C); i++) {
                    this->unk_20C[i].x = player->actor.world.pos.x;
                    this->unk_20C[i].y = player->actor.world.pos.y;
                    this->unk_20C[i].z = player->actor.world.pos.z;
                }

                this->unk_254 = ZeldaArena_Malloc(sizeof(Vec3f) * 64);
                if (this->unk_254 != NULL) {
                    for (i = 0; i < ARRAY_COUNT(this->unk_254[0]); i++) {
                        (*this->unk_254)[i].x = (((2.0f * Rand_ZeroOne()) - 1.0f) * 40.0f) + subCam->eye.x +
                                                ((subCam->at.x - subCam->eye.x) * 0.2f);
                        (*this->unk_254)[i].y = (((2.0f * Rand_ZeroOne()) - 1.0f) * 120.0f) + subCam->eye.y +
                                                ((subCam->at.y - subCam->eye.y) * 0.2f) + sp4C;
                        (*this->unk_254)[i].z = (((2.0f * Rand_ZeroOne()) - 1.0f) * 40.0f) + subCam->eye.z +
                                                ((subCam->at.z - subCam->eye.z) * 0.2f);
                    }
                }
                func_80A90C08(0x78);
                Distortion_SetType(0x20);
                Distortion_SetCountdown(80);
                play->unk_18844 = 1;
                this->unk_274 = 95;
            }
            break;

        case 95:
            if (this->unk_27A > 80) {
                this->unk_282 += 25;
            }

            if (this->unk_27A < 20) {
                this->unk_282 -= 25;
            }

            func_800FD59C(play, &D_80A9404C, this->unk_15C);
            func_800FD5E0(play, &D_80A94050, this->unk_15C);
            func_800FD654(play, &D_80A94048, this->unk_15C);
            func_800FD698(play, D_80A94054 + this->unk_282, D_80A94058 + this->unk_282, this->unk_15C);

            this->unk_278 -= this->unk_27C;
            temp_s0 = this->unk_278;
            if (ENTEST6_GET(&this->actor) == ENTEST6_24) {
                this->unk_27C += 8;
                this->unk_150 += this->unk_14C;
            } else {
                this->unk_27C -= 8;
                this->unk_150 -= this->unk_14C;
            }

            for (i = 0; i < ARRAY_COUNT(this->unk_20C); i++) {
                temp_s0 += 0x10000 / ARRAY_COUNT(this->unk_20C);
                if (player) {}
                this->unk_20C[i].x = (Math_SinS(temp_s0) * this->unk_150) + player->actor.world.pos.x;
                this->unk_20C[i].y = player->actor.world.pos.y;
                this->unk_20C[i].z = (Math_CosS(temp_s0) * this->unk_150) + player->actor.world.pos.z;
            }

            if (this->unk_254 != NULL) {
                for (i = 0; i < ARRAY_COUNT(this->unk_254[0]); i++) {
                    (*this->unk_254)[i].x += 2.0f * ((2.0f * Rand_ZeroOne()) - 1.0f);
                    if (ENTEST6_GET(&this->actor) == ENTEST6_24) {
                        (*this->unk_254)[i].y += 1.0f;
                    } else {
                        if (1) {}
                        (*this->unk_254)[i].y -= 1.0f;
                    }
                    (*this->unk_254)[i].z += 2.0f * ((2.0f * Rand_ZeroOne()) - 1.0f);
                }
            }

            if (this->unk_27A == 10) {
                this->unk_14C = 0.1f;
                func_80A90C34();
                Distortion_ClearType(0x20);
                play->unk_18844 = 0;
                if (this->unk_254 != NULL) {
                    ZeldaArena_Free(this->unk_254);
                }
                this->unk_274 = 99;
            }
            break;

        case 99:
            this->unk_15C -= this->unk_14C;
            func_800FD59C(play, &D_80A9404C, this->unk_15C);
            func_800FD5E0(play, &D_80A94050, this->unk_15C);
            func_800FD654(play, &D_80A94048, this->unk_15C);
            func_800FD698(play, D_80A94054, D_80A94058, this->unk_15C);
            break;
    }

    if (this->unk_286 != 0) {
        func_800B7298(play, NULL, 7);
    } else {
        if (this->unk_27A == 90) {
            func_800B7298(play, NULL, 0x42);
        }

        if (this->unk_27A == 70) {
            func_800B7298(play, NULL, 0x52);
        }

        if (this->unk_27A == 30) {
            func_800B7298(play, NULL, 0x51);
        }

        if (this->unk_27A == 5) {
            func_800B7298(play, NULL, 0x4A);
        }
    }

    if (this->unk_27A > 80) {
        subCam->fov += (90.0f - subCam->fov) / (this->unk_27A - 80);
    } else if (this->unk_27A > 60) {
        sp4C = 1.0f / (this->unk_27A - 60);

        subCamAt.x = subCam->at.x + ((player->actor.world.pos.x - subCam->at.x) * sp4C);
        subCamAt.y = subCam->at.y + (((player->actor.focus.pos.y - subCam->at.y) - 20.0f) * sp4C);
        subCamAt.z = subCam->at.z + ((player->actor.world.pos.z - subCam->at.z) * sp4C);

        sp54.x = (Math_SinS(player->actor.world.rot.y) * 80.0f) + subCamAt.x;
        sp54.y = subCamAt.y + 20.0f;
        sp54.z = (Math_CosS(player->actor.world.rot.y) * 80.0f) + subCamAt.z;
        sp4C *= 0.75f;

        VEC3F_LERPIMPDST(&subCamEye, &subCam->eye, &sp54, sp4C);

        Play_CameraSetAtEye(play, this->subCamId, &subCamAt, &subCamEye);
    } else if ((this->unk_27A < 11) && (this->unk_27A > 0)) {
        subCam->fov += (mainCam->fov - subCam->fov) / this->unk_27A;
    }

    if (this->unk_286 != 0) {
        func_80A90C54(play, this->unk_286 * 0.05f);
        subCam->fov += (mainCam->fov - subCam->fov) * 0.05f;
        this->unk_286++;
        if (this->unk_286 >= 20) {
            this->unk_27A = 1;
        }
    } else if ((this->unk_27A <= 60) && (this->unk_27A > 40) &&
               (CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_B))) {
        this->unk_286 = 1;
        if (ENTEST6_GET(&this->actor) == ENTEST6_25) {
            func_801A75E8(NA_SE_SY_TIME_CONTROL_SLOW);
        } else if (ENTEST6_GET(&this->actor) == ENTEST6_24) {
            func_801A75E8(NA_SE_SY_TIME_CONTROL_NORMAL);
        }
    }

    if (DECR(this->unk_27A) == 0) {
        func_80A916F0(this, play);
        play->msgCtx.ocarinaMode = 4;
    }
}

void func_80A920C8(EnTest6* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->unk_27A = 120;
    this->unk_286 = 0;
    this->unk_160 = 0.0f;
    this->actor.home.pos = player->actor.world.pos;
    this->actor.home.rot = player->actor.shape.rot;
}

void func_80A92118(EnTest6* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    player->actor.freezeTimer = 0;
    play->unk_18844 = 0;
    ActorCutscene_Stop(play->playerActorCsIds[8]);
    func_800B7298(play, NULL, 6);
    func_80A90C34();
    Distortion_ClearType(0x20);
    Actor_MarkForDeath(&this->actor);
}

void func_80A92188(EnTest6* this, PlayState* play) {
    Input* input = CONTROLLER1(&play->state);
    Player* player = GET_PLAYER(play);
    Camera* subCam;
    s32 pad;
    s16 subCamId;
    s16 pad2;

    if (this->unk_27A > 115) {
        this->unk_160 += 0.2f;
        func_80A90C54(play, this->unk_160);
    } else if (this->unk_27A > 90) {
        this->unk_160 -= 0.05f;
        func_80A90C54(play, this->unk_160);
    } else if (this->unk_27A == 90) {
        this->unk_160 = 0.0f;
        func_80A90D20(play);
    }

    if (this->unk_27A == 1) {
        this->unk_160 = 0.0f;
        func_80A90D20(play);
    } else if (this->unk_27A < 17) {
        this->unk_160 -= 0.06666666f;
        func_80A90C54(play, this->unk_160);
    } else if (this->unk_27A < 22) {
        this->unk_160 += 0.2f;
        func_80A90C54(play, this->unk_160);
    }

    if (this->unk_27A == 115) {
        func_800FD59C(play, &D_80A9406C, 1.0f);
        func_800FD5E0(play, &D_80A94070, 1.0f);
        func_800FD654(play, &D_80A94068, 1.0f);
        func_800FD698(play, D_80A94074, D_80A94078, 1.0f);
        play->unk_18844 = 1;
    }

    if (this->unk_27A == 15) {
        func_800FD59C(play, &D_80A9406C, 0.0f);
        func_800FD5E0(play, &D_80A94070, 0.0f);
        func_800FD654(play, &D_80A94068, 0.0f);
        func_800FD698(play, D_80A94074, D_80A94078, 0.0f);
        play->unk_18844 = 0;
    }

    if (this->unk_286 >= 20) {
        func_800FD59C(play, &D_80A9406C, this->unk_160);
        func_800FD5E0(play, &D_80A94070, this->unk_160);
        func_800FD654(play, &D_80A94068, this->unk_160);
        func_800FD698(play, D_80A94074, D_80A94078, this->unk_160);
        play->unk_18844 = 0;
    }

    func_800B8F98(&player->actor, NA_SE_PL_FLYING_AIR - SFX_FLAG);

    switch (this->unk_27A) {
        case 119:
            func_80A90C08(0x32);
            break;

        case 115:
            func_80A90C08(0x14);
            Distortion_SetType(0x20);
            Distortion_SetCountdown(90);
            this->unk_274 = 2;
            break;

        case 110:
            func_801A3098(0x4A);
            break;

        case 38:
        case 114:
            this->unk_274 = 1;
            break;

        case 76:
            this->unk_274 = 3;
            break;

        case 61:
            func_80A90C08(0x96);
            this->unk_274 = 4;
            break;

        case 51:
            func_80A90C08(0xB4);
            this->unk_274 = 5;
            break;

        case 14:
        case 15:
            func_80A90C08(0x32);
            Distortion_ClearType(0x20);
            this->unk_274 = 0;
            break;

        case 1:
            func_80A90C34();
            if (gSaveContext.eventInf[5] & 4) {
                this->unk_274 = 9;
            }
            break;
    }

    func_80A92950(this, play);

    if (this->unk_27A == 115) {
        subCamId = ActorCutscene_GetCurrentSubCamId(play->playerActorCsIds[8]);
        subCam = Play_GetCamera(play, subCamId);

        this->subCamAt = subCam->at;
        this->subCamEye = subCam->eye;
        this->subCamFov = subCam->fov;
        func_8016119C(subCam, &this->unk_18C);
    }

    if ((this->unk_27A <= 115) && (this->unk_27A >= 16)) {
        func_80161998(D_80A93E80, &this->unk_18C);
    } else if (this->unk_27A < 16) {
        subCamId = ActorCutscene_GetCurrentSubCamId(play->playerActorCsIds[8]);

        Play_CameraSetAtEyeUp(play, subCamId, &this->subCamAt, &this->subCamEye, &sSubCamUp);
        Play_CameraSetFov(play, subCamId, this->subCamFov);
        Play_CameraSetRoll(play, subCamId, 0);
    }

    switch (this->unk_27A) {
        case 116:
            player->actor.freezeTimer = 2;
            player->actor.shape.rot.x = 0;
            player->actor.shape.rot.y = 0;
            player->actor.world.pos.x = 0.0f;
            player->actor.world.pos.y = 0.0f;
            player->actor.world.pos.z = 0.0f;
            player->actor.home.pos.x = 0.0f;
            player->actor.home.pos.y = 0.0f;
            player->actor.home.pos.z = 0.0f;
            break;

        case 98:
            func_800B7298(play, NULL, 0x40);
            break;

        case 68:
            func_800B7298(play, NULL, 0x41);
            break;

        case 52:
            func_800B7298(play, NULL, 0x58);
            break;

        case 43:
            func_800B7298(play, NULL, 0x72);
            break;

        case 38:
            func_800B7298(play, NULL, 7);
            break;

        case 14:
            player->actor.freezeTimer = 5;
            player->actor.world.pos = player->actor.home.pos = this->actor.home.pos;
            player->actor.shape.rot = this->actor.home.rot;
            player->actor.focus.rot.y = player->actor.shape.rot.y;
            player->currentYaw = player->actor.shape.rot.y;
            player->unk_ABC = 0.0f;
            player->unk_AC0 = 0.0f;
            player->actor.shape.yOffset = 0.0f;
            break;
    }

    if ((this->unk_286 > 0) && (this->unk_286 < 20)) {
        func_80A90C54(play, this->unk_286 * 0.05f);
        this->unk_286++;
        if (this->unk_286 >= 20) {
            this->unk_27A = 15;
            this->unk_160 = 0.9333333f;
        }
    } else if ((this->unk_27A < 96) && (this->unk_27A > 50) &&
               (CHECK_BTN_ALL(input->press.button, BTN_A) || CHECK_BTN_ALL(input->press.button, BTN_B))) {
        this->unk_286 = 1;
        this->unk_27A = 39;
        Audio_QueueSeqCmd(0x111400FF);
    }

    if (DECR(this->unk_27A) == 0) {
        func_80A92118(this, play);
    }
}

void EnTest6_Update(Actor* thisx, PlayState* play) {
    EnTest6* this = THIS;

    this->actionFunc(this, play);
}

void func_80A92950(EnTest6* this, PlayState* play) {
    s32 pad[2];
    Player* player = GET_PLAYER(play);
    f32 temp_f0;
    s32 i;
    s32 temp_v0;

    if (Cutscene_CheckActorAction(play, 0x1F9)) {
        temp_v0 = Cutscene_GetActorActionIndex(play, 0x1F9);
        this->unk_274 = play->csCtx.actorActions[temp_v0]->action;

        switch (this->unk_274) {
            case 1:
                break;

            case 2:
                this->unk_276 = 0;
                this->unk_278 = 0;
                this->unk_27C = 0;
                player->actor.shape.shadowDraw = NULL;

                if (play->csCtx.actorActions[temp_v0]->startPos.x != 0) {
                    this->unk_154 = (u32)play->csCtx.actorActions[temp_v0]->startPos.x;
                } else {
                    this->unk_154 = 150.0f;
                }

                if (play->csCtx.actorActions[temp_v0]->startPos.y != 0) {
                    this->unk_280 = play->csCtx.actorActions[temp_v0]->startPos.y;
                } else {
                    this->unk_280 = 38;
                }

                if (play->csCtx.actorActions[temp_v0]->startPos.z != 0) {
                    this->unk_150 = (u32)play->csCtx.actorActions[temp_v0]->startPos.z;
                } else {
                    this->unk_150 = 480.0f;
                }
                break;

            case 3:
                if (play->csCtx.actorActions[temp_v0]->startPos.x != 0) {
                    this->unk_154 += (u32)play->csCtx.actorActions[temp_v0]->startPos.x;
                }

                if (play->csCtx.actorActions[temp_v0]->startPos.y != 0) {
                    this->unk_280 += (s16)play->csCtx.actorActions[temp_v0]->startPos.y;

                } else {
                    this->unk_280 += 6;
                }

                if (play->csCtx.actorActions[temp_v0]->startPos.z != 0) {
                    this->unk_158 = (u32)play->csCtx.actorActions[temp_v0]->startPos.z;
                } else {
                    this->unk_158 = -32.0f;
                }
                this->unk_150 += this->unk_158;
                break;

            case 4:
                if (play->csCtx.actorActions[temp_v0]->startPos.x != 0) {
                    this->unk_154 += (u32)play->csCtx.actorActions[temp_v0]->startPos.x;
                }

                if (play->csCtx.actorActions[temp_v0]->startPos.y != 0) {
                    this->unk_280 += (s16)play->csCtx.actorActions[temp_v0]->startPos.y;
                } else {
                    this->unk_280 -= 4;
                }
                break;

            case 5:
                if (play->csCtx.actorActions[temp_v0]->startPos.x != 0) {
                    this->unk_154 += (u32)play->csCtx.actorActions[temp_v0]->startPos.x;
                }

                if (play->csCtx.actorActions[temp_v0]->startPos.y != 0) {
                    this->unk_280 += (s16)play->csCtx.actorActions[temp_v0]->startPos.y;
                } else {
                    this->unk_280 -= 8;
                }

                if (play->csCtx.actorActions[temp_v0]->startPos.z != 0) {
                    this->unk_158 += (u32)play->csCtx.actorActions[temp_v0]->startPos.z;
                } else {
                    this->unk_158 += 20.0f;
                }

                this->unk_150 += this->unk_158;
                if (this->unk_150 > 3500.0f) {
                    this->unk_150 = 3500.0f;
                    this->unk_274 = 0;
                }
                break;

            case 6:
                this->unk_276 = 1;
                this->unk_278 = 0;
                this->unk_27C = 0;
                player->actor.shape.shadowDraw = NULL;

                if (play->csCtx.actorActions[temp_v0]->startPos.x != 0) {
                    this->unk_154 = (u32)play->csCtx.actorActions[temp_v0]->startPos.x;
                } else {
                    this->unk_154 = 100.0f;
                }

                if (play->csCtx.actorActions[temp_v0]->startPos.y != 0) {
                    this->unk_14C = (u32)play->csCtx.actorActions[temp_v0]->startPos.y;
                } else {
                    this->unk_14C = 20.0f;
                }

                if (play->csCtx.actorActions[temp_v0]->startPos.z != 0) {
                    this->unk_150 = (u32)play->csCtx.actorActions[temp_v0]->startPos.z;
                } else {
                    this->unk_150 = 300.0f;
                }
                this->unk_158 = 0.0f;
                break;

            case 7:
                if (play->csCtx.actorActions[temp_v0]->startPos.x != 0) {
                    this->unk_158 = (u32)play->csCtx.actorActions[temp_v0]->startPos.x;
                } else {
                    this->unk_158 = -5.0f;
                }
                this->unk_154 += this->unk_158;
                break;

            case 8:
                if (play->csCtx.actorActions[temp_v0]->startPos.x != 0) {
                    this->unk_158 += (u32)play->csCtx.actorActions[temp_v0]->startPos.x;
                } else {
                    this->unk_158 += 2.0f;
                }

                this->unk_154 += this->unk_158;
                if (this->unk_154 > 10000.0f) {
                    this->unk_154 = 10000.0f;
                    this->unk_274 = 0;
                }
                break;

            case 0:
            default:
                this->unk_276 = 99;
                return;

            case 9:
                Play_SetRespawnData(&play->state, 1, ((void)0, gSaveContext.save.entranceIndex & 0xFFFF),
                                    player->unk_3CE, 0xBFF, &player->unk_3C0, player->unk_3CC);
                this->unk_276 = 99;
                play->transitionTrigger = TRANS_TRIGGER_START;
                play->nextEntranceIndex = gSaveContext.respawn[RESPAWN_MODE_RETURN].entranceIndex;
                play->transitionType = TRANS_TYPE_02;
                if ((gSaveContext.save.time > CLOCK_TIME(18, 0)) || (gSaveContext.save.time < CLOCK_TIME(6, 0))) {
                    gSaveContext.respawnFlag = -0x63;
                    gSaveContext.eventInf[2] |= 0x80;
                } else {
                    gSaveContext.respawnFlag = 2;
                }
                play->msgCtx.ocarinaMode = 4;
                return;
        }
    } else {
        switch (this->unk_274) {
            case 2:
                this->unk_276 = 0;
                this->unk_278 = 0;
                this->unk_27C = 0;
                player->actor.shape.shadowDraw = NULL;
                this->unk_280 = 38;
                this->unk_154 = 150.0f;
                this->unk_150 = 480.0f;

            case 1:
                break;

            case 3:
                this->unk_158 = -32.0f;
                this->unk_280 += 6;
                this->unk_150 += -32.0f;
                break;

            case 4:
                this->unk_280 -= 4;
                break;

            case 5:
                this->unk_280 -= 8;
                this->unk_158 += 20.0f;
                this->unk_150 += this->unk_158;
                if (this->unk_150 > 3500.0f) {
                    this->unk_150 = 3500.0f;
                    this->unk_274 = 0;
                }
                break;

            case 6:
                this->unk_276 = 1;
                this->unk_278 = 0;
                this->unk_27C = 0;
                player->actor.shape.shadowDraw = NULL;
                this->unk_154 = 100.0f;
                this->unk_14C = 20.0f;
                this->unk_150 = 300.0f;
                this->unk_158 = 0.0f;
                break;

            case 7:
                this->unk_158 = -5.0f;
                this->unk_154 += -5.0f;
                break;

            case 8:
                this->unk_158 += 2.0f;
                this->unk_154 += this->unk_158;
                if (this->unk_154 > 10000.0f) {
                    this->unk_154 = 10000.0f;
                    this->unk_274 = 0;
                }
                break;

            case 0:
            default:
                this->unk_276 = 99;
                return;

            case 9:
                if (gSaveContext.save.time > CLOCK_TIME(12, 0)) {
                    Play_SetRespawnData(&play->state, 1, ((void)0, gSaveContext.save.entranceIndex & 0xFFFF),
                                        player->unk_3CE, 0xBFF, &player->unk_3C0, player->unk_3CC);
                    this->unk_276 = 99;
                    play->transitionTrigger = TRANS_TRIGGER_START;
                    play->nextEntranceIndex = gSaveContext.respawn[RESPAWN_MODE_RETURN].entranceIndex;
                    play->transitionType = TRANS_TYPE_02;
                    gSaveContext.respawnFlag = 2;
                    play->msgCtx.ocarinaMode = 4;
                }
                return;
        }
    }

    if (this->unk_276 == 1) {
        for (i = 0; i < ARRAY_COUNT(D_80A94910); i++) {
            D_80A94910[i].unk_08 += 2.0f * ((2.0f * Rand_ZeroOne()) - 1.0f);
            D_80A94910[i].unk_10 += 2.0f * ((2.0f * Rand_ZeroOne()) - 1.0f);
            D_80A94910[i].unk_0C += 3.0f;

            if (player->actor.world.pos.y < D_80A94910[i].unk_0C) {
                temp_f0 = D_80A94910[i].unk_0C - player->actor.world.pos.y;
                if (temp_f0 > 550.0f) {
                    temp_f0 = 1.0f;
                } else {
                    temp_f0 = temp_f0 / 550.0f;
                }
                D_80A94910[i].unk_04 = SQ(temp_f0);
            } else {
                D_80A94910[i].unk_04 = -10.0f;
            }
        }
    }
    this->unk_278++;
}

void func_80A93298(EnTest6* this, PlayState* play) {
    s16 temp_s3;
    s16 temp_s4;
    f32 phi_f24;
    s16 phi_s2;
    s32 i;
    f32 cos;
    f32 sin;

    OPEN_DISPS(play->state.gfxCtx);

    this->unk_148 = POLY_OPA_DISP;
    phi_f24 = 0.0f;

    temp_s3 = this->unk_27C;
    temp_s4 = (s32)(Math_SinS(play->state.frames) * 12000.0f) + temp_s3 + 0x4E20;
    phi_s2 = (play->state.frames & 0x3C) * 1024;
    phi_s2 *= (this->unk_154 / 200.0f);
    this->unk_27C += (s16)this->unk_154;
    this->unk_27E = (s16)((this->unk_154 / 200.0f) * 256.0f);

    for (i = 0; i < ARRAY_COUNT(this->unk_254[0]); i++) {
        temp_s3 += 0x1000;
        cos = Math_CosS(temp_s3) * this->unk_150;
        sin = Math_SinS(temp_s3) * this->unk_150;
        Matrix_Translate(cos, phi_f24, sin, MTXMODE_NEW);
        Matrix_RotateXS(0x4000, MTXMODE_APPLY);
        Matrix_Scale(0.8f, 0.8f, 0.8f, MTXMODE_APPLY);
        Matrix_RotateZS(phi_s2, MTXMODE_APPLY);

        gSPMatrix(this->unk_148++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(this->unk_148++, 0, 0xFF, 28, 28, 28, 255);
        gDPSetEnvColor(this->unk_148++, 255, 255, 255, 255);
        gDPSetRenderMode(this->unk_148++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(this->unk_148++, gameplay_keep_DL_07AFB0);

        temp_s4 += 0x1000;
        cos = Math_CosS(temp_s4) * this->unk_150;
        sin = Math_SinS(temp_s4) * this->unk_150;
        Matrix_Translate(cos, phi_f24, sin, MTXMODE_NEW);
        Matrix_RotateXS(0x4000, MTXMODE_APPLY);
        Matrix_Scale(0.8f, 0.8f, 0.8f, MTXMODE_APPLY);
        Matrix_RotateZS(-phi_s2, MTXMODE_APPLY);

        gSPMatrix(this->unk_148++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(this->unk_148++, 0, 0xFF, 28, 28, 28, 255);
        gDPSetEnvColor(this->unk_148++, 255, 255, 255, 255);
        gDPSetRenderMode(this->unk_148++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(this->unk_148++, gameplay_keep_DL_07AFB0);

        phi_f24 -= this->unk_14C;
        phi_s2 += this->unk_27E;
    }

    POLY_OPA_DISP = this->unk_148;

    for (i = 0; i < ARRAY_COUNT(D_80A94910); i++) {
        if (D_80A94910[i].unk_04 > 0.0f) {
            D_80A94910[i].unk_14(this, play, &D_80A94910[i]);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80A9369C(Actor* thisx, PlayState* play2) {
    EnTest6* this = THIS;
    PlayState* play = play2;
    f32 temp_f20;
    f32 temp_f22;
    f32 phi_f26;
    s16 phi_s2;
    s16 sp78;
    s32 i;
    Player* player = GET_PLAYER(play);
    s32 pad;

    if (this) {}
    OPEN_DISPS(play->state.gfxCtx);

    this->unk_148 = POLY_OPA_DISP;
    this->unk_27C += (s16)this->unk_154;
    this->unk_27E = this->unk_27C * 2;
    sp78 = (play->state.frames & 0x3C) * 1024;
    phi_s2 = this->unk_27C + 0x4000;

    switch (player->transformation) {
        default:
            phi_f26 = player->actor.world.pos.y + 40.0f;
            break;

        case PLAYER_FORM_DEKU:
            phi_f26 = player->actor.world.pos.y + 40.0f;
            break;

        case PLAYER_FORM_GORON:
            phi_f26 = player->actor.world.pos.y + 40.0f;
            break;

        case PLAYER_FORM_ZORA:
            phi_f26 = player->actor.world.pos.y + 40.0f;
            break;

        case PLAYER_FORM_FIERCE_DEITY:
            phi_f26 = player->actor.world.pos.y + 40.0f;
            break;
    }

    for (i = 0; i < 51; i++) {
        temp_f20 = Math_CosS(phi_s2) * this->unk_150;
        temp_f22 = Math_SinS(phi_s2) * this->unk_150;
        Matrix_RotateZS(this->unk_27E, MTXMODE_NEW);
        Matrix_Translate(phi_f26, temp_f20, temp_f22, MTXMODE_APPLY);
        Matrix_Scale(0.85f, 0.85f, 0.85f, MTXMODE_APPLY);
        Matrix_RotateXS(phi_s2, MTXMODE_APPLY);
        Matrix_RotateZS(sp78, MTXMODE_APPLY);

        gSPMatrix(this->unk_148++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(this->unk_148++, 0, 0xFF, this->unk_280, this->unk_280, this->unk_280, 255);
        gDPSetEnvColor(this->unk_148++, 235, 238, 235, 255);
        gDPSetRenderMode(this->unk_148++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2);
        gSPDisplayList(this->unk_148++, gameplay_keep_DL_07AFB0);

        phi_s2 += 0x505;
    }

    Lights_PointSetPosition(&this->lights[0].info, player->actor.world.pos.x, player->actor.world.pos.y - 10.0f,
                            player->actor.world.pos.z);
    Lights_PointSetColorAndRadius(&this->lights[0].info, 100, 250, 100, 200);

    POLY_OPA_DISP = this->unk_148;

    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80A939E8(EnTest6* this, PlayState* play2) {
    PlayState* play = play2;
    Player* player = GET_PLAYER(play);
    f32 temp_f20;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    switch (this->unk_274) {
        case 91:
        case 93:
            Lights_PointSetPosition(&this->lights[0].info, player->actor.world.pos.x, player->actor.world.pos.y - 10.0f,
                                    player->actor.world.pos.z);
            Lights_PointSetColorAndRadius(&this->lights[0].info, 245, 245, 200, this->unk_282);
            break;

        case 95:
            this->unk_148 = POLY_XLU_DISP;

            for (i = 0; i < ARRAY_COUNT(this->unk_20C); i++) {
                Matrix_Translate(this->unk_20C[i].x, this->unk_20C[i].y, this->unk_20C[i].z, MTXMODE_NEW);
                Matrix_Scale(0.3f, 0.3f, 0.3f, MTXMODE_APPLY);
                Matrix_RotateXS(-0x4000, MTXMODE_APPLY);
                Matrix_RotateZS(this->unk_278, MTXMODE_APPLY);

                gSPMatrix(this->unk_148++, Matrix_NewMtx(play->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gDPSetPrimColor(this->unk_148++, 0, 0xFF, 28, 28, 28, 255);
                gDPSetEnvColor(this->unk_148++, 245, 245, 200, this->unk_282);
                gDPSetRenderMode(this->unk_148++, G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_SURF2);
                gSPDisplayList(this->unk_148++, gameplay_keep_DL_07AFB0);

                POLY_XLU_DISP = this->unk_148;
            }

            if (this->unk_254 != NULL) {
                for (i = 0; i < ARRAY_COUNT(this->unk_254[0]); i++) {
                    temp_f20 = Rand_ZeroOne() * 0.0025f;
                    Matrix_Translate((*this->unk_254)[i].x, (*this->unk_254)[i].y, (*this->unk_254)[i].z, MTXMODE_NEW);
                    Matrix_Scale(temp_f20, temp_f20, temp_f20, MTXMODE_APPLY);

                    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 128, 128, 128, this->unk_282 >> 1);
                    gDPSetEnvColor(POLY_XLU_DISP++, 230, 230, 180, this->unk_282);

                    func_8012C2DC(play->state.gfxCtx);
                    Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);
                    Matrix_RotateZS(this->unk_278 + (i << 2), MTXMODE_APPLY);

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(POLY_XLU_DISP++, gOwlStatueWhiteFlashDL);
                }
            }
            Lights_PointSetPosition(&this->lights[0].info, player->actor.world.pos.x, player->actor.world.pos.y - 10.0f,
                                    player->actor.world.pos.z);
            Lights_PointSetColorAndRadius(&this->lights[0].info, 250, 250, 100, this->unk_282);
            break;

        case 90:
        case 92:
        case 94:
        case 96:
        case 97:
        case 98:
        case 99:
            break;
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnTest6_Draw(Actor* thisx, PlayState* play) {
    EnTest6* this = THIS;

    if (this->unk_274 != 0) {
        switch (this->unk_276) {
            case 1:
                func_80A93298(this, play);
                break;

            case 0:
                func_80A9369C(thisx, play);
                break;

            case 2:
                func_80A939E8(this, play);
                break;
        }
    }
}
