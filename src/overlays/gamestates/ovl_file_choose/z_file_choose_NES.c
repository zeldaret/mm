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

void func_8080BC58(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080BC58.s")

void func_8080BDAC(GameState* thisx);
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

void func_8080D2EC(FileChooseContext*);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D2EC.s")

void func_8080D3D0(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D3D0.s")

void func_8080D40C(FileChooseContext* this); // May be thisx
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D40C.s")

void func_8080D6D4(FileChooseContext* this); // May be thisx
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080D6D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_8080F25C.s")

void func_808108DC(FileChooseContext* this, u32); // May be thisx, probably a DList?
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_808108DC.s")

void func_80811CB8(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80811CB8.s")

void func_80812460(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812460.s")

void func_80812668(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812668.s")

void func_80812760(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812760.s")

void func_80812840(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812840.s")

void func_80812980(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812980.s")

void func_80812A6C(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812A6C.s")

void func_80812D44(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812D44.s")

void func_80812D94(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/func_80812D94.s")

// gSelectModeUpdateFuncs
extern void (*D_8081477C[])(GameState*);
// void (*D_8081477C[])(GameState*) = {
//     func_80812460,
//     func_80812668,
//     func_80812760,
//     func_80812840,
//     func_80812980,
//     func_80812A6C,
//     func_80812D44,
//     func_80812D94,
// };

// SelectModeUpdate
void func_80812E94(GameState* thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;

    // selectMode
    D_8081477C[this->unk_2448C](&this->state);
}

extern Gfx D_010311F0[];
extern Gfx D_01031408[];
extern Gfx D_01031618[];

// SelectModeDraw
void func_80812ED0(GameState* thisx) {
    FileChooseContext *this = (FileChooseContext*)thisx;

    OPEN_DISPS(this->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);

    func_8012C8AC(this->state.gfxCtx);
    FileChoose_RenderView(this, 0.0f, 0.0f, 64.0f);
    func_8080D40C(this);
    func_8080D6D4(this);

    gDPSetCombineMode(POLY_OPA_DISP++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, this->unk_244B0[0], this->unk_244B0[1], this->unk_244B0[2], this->unk_244BA);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    Matrix_InsertTranslation(0.0f, 0.0f, -93.6f, 0);
    Matrix_Scale(0.78f, 0.78f, 0.78f, 1);
    Matrix_RotateStateAroundXAxis(this->unk_2450C / 100.0f);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(this->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPVertex(POLY_OPA_DISP++, &this->unk_A4[0], 32, 0);
    gSPDisplayList(POLY_OPA_DISP++, D_010311F0);

    gSPVertex(POLY_OPA_DISP++, &this->unk_A4[32], 32, 0);
    gSPDisplayList(POLY_OPA_DISP++, D_01031408);

    gSPVertex(POLY_OPA_DISP++, &this->unk_A4[64], 16, 0);
    gSPDisplayList(POLY_OPA_DISP++, D_01031618);

    func_808108DC(this, 0x01020040);
    gDPPipeSync(POLY_OPA_DISP++);
    FileChoose_RenderView(this, 0.0f, 0.0f, 64.0f);

    CLOSE_DISPS(this->state.gfxCtx);
}

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

// sScreenFillSetupDL
extern Gfx D_80814510[];

// State update/draws
extern void (*D_8081479C[])(GameState*);
// void (*D_8081479C[])(GameState*) = {
//     func_8080BDAC,
//     func_80811CB8,
//     func_80812ED0,
// };
extern void (*D_808147A8[])(GameState*);
// void (*D_808147A8[])(GameState*) = {
//     func_8080BC58,
//     func_8080D3D0,
//     func_80812E94,
// };

extern void* D_808147B4[];
// Please wait, Decide/Cancel, Decide/Save
// void* D_808147B4[] = { 0x0100B2B0, 0x0100A030, 0x0100A930 };
extern s16 D_808147C0[];
// s16 D_808147C0[] = { 144, 144, 152 };
extern s16 D_808147C8[];
// s16 D_808147C8[] = { 90, 90, 86 };

void FileChoose_Main(GameState* thisx) {
    FileChooseContext* this = (FileChooseContext*)thisx;
    Input* input = &this->state.input[0];
    s32 texIndex;
    s32 pad;

    func_8012CF0C(this->state.gfxCtx, 0, 1, 0, 0, 0);

    OPEN_DISPS(this->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x01, this->staticSegment);
    gSPSegment(POLY_OPA_DISP++, 0x02, this->parameterSegment);
    gSPSegment(POLY_OPA_DISP++, 0x06, this->titleSegment);

    // stickRelX
    this->unk_24502 = input->rel.stick_x;
    // stickRelY
    this->unk_24504 = input->rel.stick_y;

    if (this->unk_24502 < -30) {
        // stickXDir
        if (this->unk_244FE == -1) {
            // inputTimerX
            this->unk_244FA--;
            if (this->unk_244FA < 0) {
                this->unk_244FA = 2;
            } else {
                this->unk_24502 = 0;
            }
        } else {
            this->unk_244FA = 10;
            this->unk_244FE = -1;
        }
    } else if (this->unk_24502 > 30) {
        if (this->unk_244FE == 1) {
            this->unk_244FA--;
            if (this->unk_244FA < 0) {
                this->unk_244FA = 2;
            } else {
                this->unk_24502 = 0;
            }
        } else {
            this->unk_244FA = 10;
            this->unk_244FE = 1;
        }
    } else {
        this->unk_244FE = 0;
    }

    if (this->unk_24504 < -30) {
        // stickYDir
        if (this->unk_24500 == -1) {
            // inputTimerY
            this->unk_244FC--;
            if (this->unk_244FC < 0) {
                this->unk_244FC = 2;
            } else {
                this->unk_24504 = 0;
            }
        } else {
            this->unk_244FC = 10;
            this->unk_24500 = -1;
        }
    } else if (this->unk_24504 > 30) {
        if (this->unk_24500 == 1) {
            this->unk_244FC--;
            if (this->unk_244FC < 0) {
                this->unk_244FC = 2;
            } else {
                this->unk_24504 = 0;
            }
        } else {
            this->unk_244FC = 10;
            this->unk_24500 = 1;
        }
    } else {
        this->unk_24500 = 0;
    }

    // emptyFileTextAlpha ?
    this->unk_244E8 = 0;

    func_8080D2EC(this);
    // menuMode
    D_808147A8[this->unk_24484](&this->state);
    FileChoose_UpdateAndDrawSkybox(this);
    D_8081479C[this->unk_24484](&this->state);

    func_8012C628(this->state.gfxCtx);

    gDPSetCombineLERP(POLY_OPA_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0,
                          PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 100, 255, 255, this->unk_244E6);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 0);

    if (this->sramCtx.status > 0) {
        texIndex = 0;
    } else if ((this->unk_24486 > 38) && (this->unk_24486 < 44)) {
        texIndex = 2;
    } else {
        texIndex = 1;
    }

    gDPLoadTextureBlock(POLY_OPA_DISP++, D_808147B4[texIndex], G_IM_FMT_IA, G_IM_SIZ_8b, D_808147C0[texIndex], 16, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

    gSPTextureRectangle(POLY_OPA_DISP++, D_808147C8[texIndex] << 2, 204 << 2, (D_808147C8[texIndex] + D_808147C0[texIndex]) << 2, 
                        (204 + 16) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPDisplayList(POLY_OPA_DISP++, D_80814510);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 0, 0, 0, this->unk_2450A);
    gSPDisplayList(POLY_OPA_DISP++, D_0E000000.fillRect);

    CLOSE_DISPS(this->state.gfxCtx);
}

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
