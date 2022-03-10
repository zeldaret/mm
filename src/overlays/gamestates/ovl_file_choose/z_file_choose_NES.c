/*
 * File: z_file_choose_NES.c
 * Overlay: ovl_file_choose
 * Description:
 */

#include "z_file_choose.h"

extern UNK_TYPE D_01002800;
extern UNK_TYPE D_01007980;
extern UNK_TYPE D_0102A6B0;
extern UNK_TYPE D_0102B170;
extern UNK_TYPE D_010310F0;
extern UNK_TYPE D_010311F0;

// there are uses of D_0E000000.fillRect (appearing as D_0E0002E0) in this file
extern GfxMasterList D_0E000000;

extern s16 fileChooseSkyboxRotation;

void func_801A3238(u8 playerIdx, u16 seqId, u8 fadeTimer, s8 arg3, s8 arg4); /* extern */

void func_8080BC20(FileChooseContext* this) {
    this->unk_24486++;
}

void FileChoose_nop8080bc44(void) {
}

void FileChoose_nop8080BC4C(FileChooseContext* this) {
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080BC58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080BDAC.s")

void FileChoose_RenderView(FileChooseContext* this, f32 eyeX, f32 eyeY, f32 eyeZ) {
    Vec3f eye;
    Vec3f lookAt;
    Vec3f up;

    eye.x = eyeX;
    eye.y = eyeY;
    eye.z = eyeZ;

    lookAt.x = 
    lookAt.y = 
    lookAt.z = 
    0.0f;

    up.x = 
    up.z = 0.0f;
    up.y = 1.0f;

    View_SetViewOrientation(&this->view, &eye, &lookAt, &up);
    View_RenderView(&this->view, 0x7F);
}

// FileChoose_QuadTextureIA8
Gfx* func_8080BE60(Gfx* gfx, void* texture, s16 width, s16 height, s16 point) {
    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, width, height, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSP1Quadrangle(gfx++, point, point + 2, point + 3, point + 1, 0);

    return gfx;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080C040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080C228.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080C29C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080C324.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080C3A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D1BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D2EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D3D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D40C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D6D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080F25C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_808108DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80811CB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812840.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812980.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812A6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812D44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812D94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812E94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812ED0.s")

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/FileChoose_UpdateAndDrawSkybox.s")
void FileChoose_UpdateAndDrawSkybox(FileChooseContext* this) {
    GraphicsContext* gfxCtx; // TODO: check if this temp is needed, or if it recasts thisx instead
    f32 eyeX;
    f32 eyeY;
    f32 eyeZ;

    gfxCtx = this->state.gfxCtx;
    OPEN_DISPS(gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    eyeX = 1000.0f * Math_CosS(fileChooseSkyboxRotation) - 1000.0f * Math_SinS(fileChooseSkyboxRotation);
    eyeY = -700.0f;
    eyeZ =  1000.0f * Math_SinS(fileChooseSkyboxRotation) + 1000.0f * Math_CosS(fileChooseSkyboxRotation);

    FileChoose_RenderView(this, eyeX, eyeY, eyeZ);
    SkyboxDraw_Draw(&this->skyboxCtx, this->state.gfxCtx, 1, this->envCtx.unk_13, eyeX, -700.0f, eyeZ);

    gDPSetTextureLUT(POLY_OPA_DISP++, G_TT_NONE);

    fileChooseSkyboxRotation += -0xA;

    CLOSE_DISPS(gfxCtx);
}

void FileChoose_Main(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/FileChoose_Main.s")

// FileChoose_InitContext
void func_80813908(GameState* thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;
    EnvironmentContext* envCtx = &this->envCtx;

    Sram_Alloc(&this->state, &this->sramCtx);
    func_801457CC(&this->state, &this->sramCtx);

    // this->menuMode = FS_MENU_MODE_INIT;
    this->unk_24484 = 0;

    this->unk_24480 = 
    this->unk_2448C = 
    this->unk_2448E = 
    this->unk_244A6 = 
    this->unk_24482 = 0;

    this->unk_244F6[0] = 2;
    this->unk_244F6[1] = 3;
    this->unk_244AC = 0;
    this->unk_244AE = 1;

    this->unk_2450A = 255;
    this->unk_244F2 = 1;
    this->unk_244F4 = 0xC;
    this->unk_244EA[0] = 155;
    this->unk_244EA[1] = 255;
    this->unk_244EA[2] = 255;
    this->unk_244EA[3] = 70;
    this->unk_24486 = 0;
    this->unk_2450C = 0.0f;

    this->unk_244FE = 
    this->unk_244FA = 0;

    this->unk_24500 = 
    this->unk_244FC = 0;

    this->unk_24518 = 
    this->unk_2451A = 
    this->unk_24516 = 0;

    // this->kbdButton = FS_KBD_BTN_NONE;
    this->unk_24510 = 99;

    // windowColor
    this->unk_244B0[0] = 100;
    this->unk_244B0[1] = 150;
    this->unk_244B0[2] = 255;

    this->unk_244BA    = 
    this->unk_244B6[0] = 
    this->unk_244B6[1] = 
    this->unk_244BC[0] = 
    this->unk_244BC[1] = 
    this->unk_244BC[2] = 
    this->unk_244C2[0] = 
    this->unk_244C2[1] = 
    this->unk_244C2[2] = 
    this->unk_244C8[0] = 
    this->unk_244C8[1] = 
    this->unk_244C8[2] = 
    this->unk_244CE[0] = 
    this->unk_244CE[1] = 
    this->unk_244CE[2] = 
    this->unk_244D4[0] = 
    this->unk_244D4[1] = 
    this->unk_244D4[2] = 
    this->unk_244DA[0] = 
    this->unk_244DA[1] = 
    this->unk_244DA[2] = 
    this->unk_244DA[3] = 
    this->unk_244E2    = 
    this->unk_244E4    = 
    this->unk_244E6    = 
    this->unk_244E8 = 0;

    this->unk_24508 = 6;
    this->unk_24498 = 4;
    this->unk_244A8 = -1;

    this->unk_244AA    =
    this->unk_2449A[0] =
    this->unk_2449A[1] =
    this->unk_2449A[2] =
    this->unk_2449A[3] =
    this->unk_2449A[4] =
    this->unk_2449A[5] =
    this->unk_24492[0] =
    this->unk_24492[1] =
    this->unk_24492[2] = 0;

    this->unk_2451E[0] = 0;
    this->unk_2451E[1] = 3;
    this->unk_2451E[2] = 6;
    this->unk_2451E[3] = 8;
    this->unk_2451E[4] = 10;
    this->unk_24528 = 20;

    ShrinkWindow_SetLetterboxTarget(0);
    gSaveContext.environmentTime = 0;
    gSaveContext.time = 0;

    // Skybox_Init
    func_801434E4(&this->state, &this->skyboxCtx, 1);
    R_ENV_TIME_INCREMENT = 10;

    // TODO: copy some variable names from OoT
    envCtx->unk_19 = 0;
    envCtx->unk_1A = 0;
    envCtx->unk_21 = 0;
    envCtx->unk_22 = 0;
    envCtx->unk_44 = 0;
    envCtx->unk_10 = 99;
    envCtx->unk_11 = 99;
    envCtx->unk_1F = 0;
    envCtx->unk_20 = 0;
    envCtx->unk_C1 = 0;
    envCtx->unk_17 = 2;
    envCtx->skyboxDisabled = 0;
    envCtx->unk_13 = 0;
    envCtx->unk_84 = 0.0f;
    envCtx->unk_88 = 0.0f;

    gSaveContext.buttonStatus[0] = 0;
    gSaveContext.buttonStatus[1] = 0;
    gSaveContext.buttonStatus[2] = 0;
    gSaveContext.buttonStatus[3] = 0;
    gSaveContext.buttonStatus[4] = 0;
}

void FileChoose_Destroy(GameState* this) {
    ShrinkWindow_Destroy();
}

void FileChoose_Init(GameState* thisx) {
    s32 pad;
    FileChooseContext* this = (FileChooseContext*)thisx;
    size_t size;

    Game_SetFramerateDivisor(&this->state, 1);
    Matrix_StateAlloc(&this->state);
    ShrinkWindow_Init();
    View_Init(&this->view, this->state.gfxCtx);
    this->state.main = FileChoose_Main;
    this->state.destroy = FileChoose_Destroy;
    func_80813908(&this->state);
    Font_LoadOrderedFont(&this->font);

    size = SEGMENT_ROM_SIZE(title_static);
    this->staticSegment = THA_AllocEndAlign16(&this->state.heap, size);
    DmaMgr_SendRequest0(this->staticSegment, SEGMENT_ROM_START(title_static), size);

    size = SEGMENT_ROM_SIZE(parameter_static);
    this->parameterSegment = THA_AllocEndAlign16(&this->state.heap, size);
    DmaMgr_SendRequest0(this->parameterSegment, SEGMENT_ROM_START(parameter_static), size);

    size = objectFileTable[OBJECT_MAG].vromEnd - objectFileTable[OBJECT_MAG].vromStart;
    this->titleSegment = THA_AllocEndAlign16(&this->state.heap, size);
    DmaMgr_SendRequest0(this->titleSegment, objectFileTable[OBJECT_MAG].vromStart, size);

    audio_setBGM(0xA);
    func_801A3238(SEQ_PLAYER_BGM_MAIN, NA_BGM_FILE_SELECT, 0, 7, 1);
}
