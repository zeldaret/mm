/*
 * File: z_title.c
 * Overlay: ovl_title
 * Description: Nintendo 64 logo shown on startup
 */

#include "z_title.h"
#include "z64shrink_window.h"
#include "z64view.h"
#include "CIC6105.h"
#include "overlays/gamestates/ovl_opening/z_opening.h"
#include "misc/nintendo_rogo_static/nintendo_rogo_static.h"

void ConsoleLogo_UpdateCounters(ConsoleLogoState* this) {
    if ((this->coverAlpha == 0) && (this->visibleDuration != 0)) {
        this->timer--;
        this->visibleDuration--;

        if (this->timer == 0) {
            this->timer = 400;
        }
    } else {
        this->coverAlpha += this->addAlpha;

        if (this->coverAlpha <= 0) {
            this->coverAlpha = 0;
            this->addAlpha = 12;
        } else if (this->coverAlpha >= 255) {
            this->coverAlpha = 255;
            this->exit = true;
        }
    }

    this->uls = this->ult & 0x7F;
    this->ult++;
}

void ConsoleLogo_RenderView(ConsoleLogoState* this, f32 x, f32 y, f32 z) {
    View* view = &this->view;
    Vec3f eye;
    Vec3f at;
    Vec3f up;

    eye.x = x;
    eye.y = y;
    eye.z = z;
    up.x = up.z = 0.0f;
    at.x = at.y = at.z = 0.0f;
    up.y = 1.0f;
    View_SetPerspective(view, 30.0f, 10.0f, 12800.0f);
    View_LookAt(view, &eye, &at, &up);
    View_Apply(view, VIEW_ALL);
}

void ConsoleLogo_Draw(GameState* thisx) {
    static s16 sTitleRotation = 0;
    static Lights1 sTitleLights = gdSPDefLights1(100, 100, 100, 255, 255, 255, 69, 69, 69);
    ConsoleLogoState* this = (ConsoleLogoState*)thisx;
    u16 y;
    u16 idx;
    Vec3f lightDir;
    Vec3f object;
    Vec3f eye;
    s32 pad[2];

    OPEN_DISPS(this->state.gfxCtx);

    lightDir.x = 69.0f;
    lightDir.y = 69.0f;
    lightDir.z = 69.0f;

    object.x = 0.0f;
    object.y = 0.0f;
    object.z = 0.0f;

    eye.x = -4949.148f;
    eye.y = 4002.5417f;
    eye.z = 1119.0837f;

    Hilite_DrawOpa(&object, &eye, &lightDir, this->state.gfxCtx);

    gSPSetLights1(POLY_OPA_DISP++, sTitleLights);

    ConsoleLogo_RenderView(this, 0.0f, 150.0f, 300.0f);
    Gfx_SetupDL25_Opa(this->state.gfxCtx);
    Matrix_Translate(-53.0f, -5.0f, 0.0f, MTXMODE_NEW);
    Matrix_Scale(1.0f, 1.0f, 1.0f, MTXMODE_APPLY);
    Matrix_RotateZYX(0, sTitleRotation, 0, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx), G_MTX_LOAD);
    gSPDisplayList(POLY_OPA_DISP++, gNintendo64LogoNDL);

    Gfx_SetupDL39_Opa(this->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetCycleType(POLY_OPA_DISP++, G_CYC_2CYCLE);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_PASS, G_RM_CLD_SURF2);
    gDPSetCombineLERP(POLY_OPA_DISP++, TEXEL1, PRIMITIVE, ENV_ALPHA, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT,
                      COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 170, 255, 255, 255);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 255, 128);
    gDPLoadMultiBlock(POLY_OPA_DISP++, gNintendo64LogoTextShineTex, 0x100, 1, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0,
                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 2, 11);

    for (idx = 0, y = 94; idx < 16; idx++, y += 2) {
        gDPLoadTextureBlock(POLY_OPA_DISP++, &((u8*)gNintendo64LogoTextTex)[0x180 * idx], G_IM_FMT_I, G_IM_SIZ_8b, 192,
                            2, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                            G_TX_NOLOD, G_TX_NOLOD);

        gDPSetTileSize(POLY_OPA_DISP++, 1, this->uls, (this->ult & 0x7F) - idx * 4, 0, 0);
        gSPTextureRectangle(POLY_OPA_DISP++, 97 << 2, y << 2, (97 + 192) << 2, (y + 2) << 2, G_TX_RENDERTILE, 0, 0,
                            1 << 10, 1 << 10);
    }

    Environment_FillScreen(this->state.gfxCtx, 0, 0, 0, this->coverAlpha, FILL_SCREEN_XLU);

    sTitleRotation += 300;

    CLOSE_DISPS(this->state.gfxCtx);
}

void ConsoleLogo_Main(GameState* thisx) {
    ConsoleLogoState* this = (ConsoleLogoState*)thisx;

    func_8012CF0C(this->state.gfxCtx, true, true, 0, 0, 0);

    OPEN_DISPS(this->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x01, this->staticSegment);

    ConsoleLogo_UpdateCounters(this);
    ConsoleLogo_Draw(&this->state);
    if (this->exit) {
        gSaveContext.seqId = (u8)NA_BGM_DISABLED;
        gSaveContext.ambienceId = AMBIENCE_ID_DISABLED;
        gSaveContext.gameMode = GAMEMODE_TITLE_SCREEN;

        STOP_GAMESTATE(&this->state);
        SET_NEXT_GAMESTATE(&this->state, TitleSetup_Init, sizeof(TitleSetupState));
    }

    CLOSE_DISPS(this->state.gfxCtx);
}

void ConsoleLogo_Destroy(GameState* thisx) {
    ConsoleLogoState* this = (ConsoleLogoState*)thisx;

    Sram_InitSram(&this->state, &this->sramCtx);
    ShrinkWindow_Destroy();
    CIC6105_Noop2();
}

void ConsoleLogo_Init(GameState* thisx) {
    ConsoleLogoState* this = (ConsoleLogoState*)thisx;
    uintptr_t segmentSize = SEGMENT_ROM_SIZE(nintendo_rogo_static);

    this->staticSegment = THA_AllocTailAlign16(&this->state.tha, segmentSize);
    DmaMgr_SendRequest0(this->staticSegment, SEGMENT_ROM_START(nintendo_rogo_static), segmentSize);

    GameState_SetFramerateDivisor(&this->state, 1);
    Matrix_Init(&this->state);
    ShrinkWindow_Init();
    View_Init(&this->view, this->state.gfxCtx);

    this->state.main = ConsoleLogo_Main;
    this->state.destroy = ConsoleLogo_Destroy;
    this->exit = false;

    if (!(PadMgr_GetValidControllersMask() & 1)) {
        gSaveContext.fileNum = 0xFEDC;
    } else {
        gSaveContext.fileNum = 0xFF;
    }

    gSaveContext.flashSaveAvailable = true;
    Sram_Alloc(thisx, &this->sramCtx);
    this->ult = 0;
    this->timer = 20;
    this->coverAlpha = 255;
    this->addAlpha = -12;
    this->visibleDuration = 60;
}
