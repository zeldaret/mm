#include "global.h"

s32 D_801AEC70 = 0;
u32 D_801AEC74 = 0;
s32 D_801AEC78 = 0;

#pragma GLOBAL_ASM("asm/non_matchings/code/flg_set/func_800B32D0.s")

//     FlagSetEntry D_801AE8F0[100] = { 0 };
// void func_800B32D0(GameState* gameState) {
//     GlobalContext* globalCtx = (GlobalContext*)gameState;
//     Input* input = &globalCtx->state.input[0];

//     if (CHECK_BTN_ALL(input->press.button, BTN_DLEFT)) {
//         D_801AEC74++;
//         D_801AEC78 = 10;
//     }

//     if (CHECK_BTN_ALL(input->press.button, BTN_DRIGHT)) {
//         D_801AEC78 = 10;
//         D_801AEC74--;
//     }

//     if (D_801AEC78 == 0) {
//         if (CHECK_BTN_ALL(input->cur.button, BTN_DLEFT)) {
//             D_801AEC78 = 2;
//             D_801AEC74++;
//         }
//         if (CHECK_BTN_ALL(input->cur.button, BTN_DRIGHT)) {
//             D_801AEC78 = 2;
//             D_801AEC74--;
//         }
//     }

//     D_801AEC74 %= 8;
//     if (CHECK_BTN_ALL(input->press.button, BTN_DUP)) {
//         D_801AEC70--;
//         if (D_801AEC70 < 0) {
//             D_801AEC70 = 0;
//         }
//         D_801AEC78 = 10;
//     }

//     if (CHECK_BTN_ALL(input->press.button, BTN_DDOWN)) {
//         D_801AEC78 = 10;
//         D_801AEC70++;
//         if (!D_801AE8F0[D_801AEC70].value) {
//             D_801AEC70--;
//         }
//     }

//     if (CHECK_BTN_ALL(input->press.button, BTN_CUP)) {
//         D_801AEC70 -= 10;
//         if (D_801AEC70 < 0) {
//             D_801AEC70 = 0;
//         }
//         D_801AEC78 = 10;
//     }

//     if (CHECK_BTN_ALL(input->press.button, BTN_CDOWN)) {
//         D_801AEC78 = 10;
//         D_801AEC70 += 10;
//         if (((D_801AEC70 <= 100) ^ 1)) {
//             D_801AEC70 = 100;
//         }
//     }

//     if (D_801AEC78 == 0) {
//         if (CHECK_BTN_ALL(input->cur.button, BTN_DUP)) {
//             D_801AEC78 = 2;
//             D_801AEC70--;
//             if (D_801AEC70 < 0) {
//                 D_801AEC70 = 0;
//             }
//         } else if (CHECK_BTN_ALL(input->cur.button, BTN_DDOWN)) {
//             D_801AEC78 = 2;
//             D_801AEC70++;
//             if (!D_801AE8F0[D_801AEC70].value) {
//                 D_801AEC70--;
//             }
//         } else if (CHECK_BTN_ALL(input->cur.button, BTN_CUP)) {
//             D_801AEC78 = 2;
//             D_801AEC70 -= 10;
//             if (D_801AEC70 < 0) {
//                 D_801AEC70 = 0;
//             }
//         } else if (CHECK_BTN_ALL(input->cur.button, BTN_CDOWN)) {
//             D_801AEC78 = 2;
//             D_801AEC70 += 10;
//             if (((D_801AEC70 <= 100) ^ 1)) {
//                 D_801AEC70 = 100;
//             }
//         }
//     }
//     if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
//         *D_801AE8F0[D_801AEC70].value ^= (1 << D_801AEC74);
//     }

//     if (D_801AEC78 != 0) {
//         D_801AEC78--;
//     }

//     if (CHECK_BTN_ALL(input->cur.button, BTN_START)) {
//         if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
//             s16 phi_v0;
//             for (phi_v0 = 0; phi_v0 < 100; phi_v0++) {
//                 gSaveContext.weekEventReg[phi_v0] = 0;
//             }
//             for (phi_v0 = 0; phi_v0 < 8; phi_v0++) {
//                 gSaveContext.eventInf[phi_v0] = 0;
//             }
//         }
//     } else if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
//         globalCtx->pauseCtx.debugState = 0;
//     }
// }

#pragma GLOBAL_ASM("asm/non_matchings/code/flg_set/D_801DC120.s")

// void func_800B3644(GameState* gameState);
extern s32 D_801ED890;

void func_800B3644(GameState* gameState) {
    GraphicsContext* gfxCtx = gameState->gfxCtx;
    Gfx* gfx;
    Gfx* polyOpa;

    OPEN_DISPS(gfxCtx);
    GfxPrint printer;
    s32 pad;

    polyOpa = POLY_OPA_DISP;
    gfx = Graph_GfxPlusOne(polyOpa);
    gSPDisplayList(OVERLAY_DISP++, gfx);

    GfxPrint_Init(&printer);
    GfxPrint_Open(&printer, gfx);
    GfxPrint_SetColor(&printer, 250, 50, 50, 255);
    GfxPrint_SetPos(&printer, 8, 13);
    GfxPrint_Printf(&printer, D_801AE8F0[D_801AEC70].name);
    GfxPrint_SetPos(&printer, 12, 15);

    for (D_801ED890 = 7; D_801ED890 >= 0; D_801ED890--) {
        if ((u32)D_801ED890 == D_801AEC74) {
            GfxPrint_SetColor(&printer, 200, 200, 200, 255);
        } else {
            GfxPrint_SetColor(&printer, 100, 100, 100, 255);
        }
        if (*D_801AE8F0[D_801AEC70].value & (1 << D_801ED890)) {
            GfxPrint_Printf(&printer, "1");
        } else {
            GfxPrint_Printf(&printer, "0");
        }

        if ((D_801ED890 % 4) == 0) {
            GfxPrint_Printf(&printer, " ");
        }
    }

    gfx = GfxPrint_Close(&printer);
    GfxPrint_Destroy(&printer);

    gSPEndDisplayList(gfx++);
    Graph_BranchDlist(polyOpa, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/flg_set/D_801DC9B8.s")
