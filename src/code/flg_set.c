/**
 * File: flg_set.c
 * Description: Event Editor, used to view and edit weekEventReg, eventInf and maskMaskBit flags.
 * Controls:
 *  + Left and Right: select different flags/bits in array element
 *  + Up and Down: select array element (byte) 1 up/down
 *  C Up and Down: select array element (byte) 10 up/down
 *  A: toggle flag
 *  B: exit
 *  Hold Start and press B: clear all weekEventReg and eventInf flags
 */
#include "global.h"

FlagSetEntry D_801AE8F0[] = {
    { &gSaveContext.weekEventReg[0], "week_event_reg[0]" },
    { &gSaveContext.weekEventReg[1], "week_event_reg[1]" },
    { &gSaveContext.weekEventReg[2], "week_event_reg[2]" },
    { &gSaveContext.weekEventReg[3], "week_event_reg[3]" },
    { &gSaveContext.weekEventReg[4], "week_event_reg[4]" },
    { &gSaveContext.weekEventReg[5], "week_event_reg[5]" },
    { &gSaveContext.weekEventReg[6], "week_event_reg[6]" },
    { &gSaveContext.weekEventReg[7], "week_event_reg[7]" },
    { &gSaveContext.weekEventReg[8], "week_event_reg[8]" },
    { &gSaveContext.weekEventReg[9], "week_event_reg[9]" },
    { &gSaveContext.weekEventReg[10], "week_event_reg[10]" },
    { &gSaveContext.weekEventReg[11], "week_event_reg[11]" },
    { &gSaveContext.weekEventReg[12], "week_event_reg[12]" },
    { &gSaveContext.weekEventReg[13], "week_event_reg[13]" },
    { &gSaveContext.weekEventReg[14], "week_event_reg[14]" },
    { &gSaveContext.weekEventReg[15], "week_event_reg[15]" },
    { &gSaveContext.weekEventReg[16], "week_event_reg[16]" },
    { &gSaveContext.weekEventReg[17], "week_event_reg[17]" },
    { &gSaveContext.weekEventReg[18], "week_event_reg[18]" },
    { &gSaveContext.weekEventReg[19], "week_event_reg[19]" },
    { &gSaveContext.weekEventReg[20], "week_event_reg[20]" },
    { &gSaveContext.weekEventReg[21], "week_event_reg[21]" },
    { &gSaveContext.weekEventReg[22], "week_event_reg[22]" },
    { &gSaveContext.weekEventReg[23], "week_event_reg[23]" },
    { &gSaveContext.weekEventReg[24], "week_event_reg[24]" },
    { &gSaveContext.weekEventReg[25], "week_event_reg[25]" },
    { &gSaveContext.weekEventReg[26], "week_event_reg[26]" },
    { &gSaveContext.weekEventReg[27], "week_event_reg[27]" },
    { &gSaveContext.weekEventReg[28], "week_event_reg[28]" },
    { &gSaveContext.weekEventReg[29], "week_event_reg[29]" },
    { &gSaveContext.weekEventReg[30], "week_event_reg[30]" },
    { &gSaveContext.weekEventReg[31], "week_event_reg[31]" },
    { &gSaveContext.weekEventReg[32], "week_event_reg[32]" },
    { &gSaveContext.weekEventReg[33], "week_event_reg[33]" },
    { &gSaveContext.weekEventReg[34], "week_event_reg[34]" },
    { &gSaveContext.weekEventReg[35], "week_event_reg[35]" },
    { &gSaveContext.weekEventReg[36], "week_event_reg[36]" },
    { &gSaveContext.weekEventReg[37], "week_event_reg[37]" },
    { &gSaveContext.weekEventReg[38], "week_event_reg[38]" },
    { &gSaveContext.weekEventReg[39], "week_event_reg[39]" },
    { &gSaveContext.weekEventReg[40], "week_event_reg[40]" },
    { &gSaveContext.weekEventReg[41], "week_event_reg[41]" },
    { &gSaveContext.weekEventReg[42], "week_event_reg[42]" },
    { &gSaveContext.weekEventReg[43], "week_event_reg[43]" },
    { &gSaveContext.weekEventReg[44], "week_event_reg[44]" },
    { &gSaveContext.weekEventReg[45], "week_event_reg[45]" },
    { &gSaveContext.weekEventReg[46], "week_event_reg[46]" },
    { &gSaveContext.weekEventReg[47], "week_event_reg[47]" },
    { &gSaveContext.weekEventReg[48], "week_event_reg[48]" },
    { &gSaveContext.weekEventReg[49], "week_event_reg[49]" },
    { &gSaveContext.weekEventReg[50], "week_event_reg[50]" },
    { &gSaveContext.weekEventReg[51], "week_event_reg[51]" },
    { &gSaveContext.weekEventReg[52], "week_event_reg[52]" },
    { &gSaveContext.weekEventReg[53], "week_event_reg[53]" },
    { &gSaveContext.weekEventReg[54], "week_event_reg[54]" },
    { &gSaveContext.weekEventReg[55], "week_event_reg[55]" },
    { &gSaveContext.weekEventReg[56], "week_event_reg[56]" },
    { &gSaveContext.weekEventReg[57], "week_event_reg[57]" },
    { &gSaveContext.weekEventReg[58], "week_event_reg[58]" },
    { &gSaveContext.weekEventReg[59], "week_event_reg[59]" },
    { &gSaveContext.weekEventReg[60], "week_event_reg[60]" },
    { &gSaveContext.weekEventReg[61], "week_event_reg[61]" },
    { &gSaveContext.weekEventReg[62], "week_event_reg[62]" },
    { &gSaveContext.weekEventReg[63], "week_event_reg[63]" },
    { &gSaveContext.weekEventReg[64], "week_event_reg[64]" },
    { &gSaveContext.weekEventReg[65], "week_event_reg[65]" },
    { &gSaveContext.weekEventReg[66], "week_event_reg[66]" },
    { &gSaveContext.weekEventReg[67], "week_event_reg[67]" },
    { &gSaveContext.weekEventReg[68], "week_event_reg[68]" },
    { &gSaveContext.weekEventReg[69], "week_event_reg[69]" },
    { &gSaveContext.weekEventReg[70], "week_event_reg[70]" },
    { &gSaveContext.weekEventReg[71], "week_event_reg[71]" },
    { &gSaveContext.weekEventReg[72], "week_event_reg[72]" },
    { &gSaveContext.weekEventReg[73], "week_event_reg[73]" },
    { &gSaveContext.weekEventReg[74], "week_event_reg[74]" },
    { &gSaveContext.weekEventReg[75], "week_event_reg[75]" },
    { &gSaveContext.weekEventReg[76], "week_event_reg[76]" },
    { &gSaveContext.weekEventReg[77], "week_event_reg[77]" },
    { &gSaveContext.weekEventReg[78], "week_event_reg[78]" },
    { &gSaveContext.weekEventReg[79], "week_event_reg[79]" },
    { &gSaveContext.weekEventReg[80], "week_event_reg[80]" },
    { &gSaveContext.weekEventReg[81], "week_event_reg[81]" },
    { &gSaveContext.weekEventReg[82], "week_event_reg[82]" },
    { &gSaveContext.weekEventReg[83], "week_event_reg[83]" },
    { &gSaveContext.weekEventReg[84], "week_event_reg[84]" },
    { &gSaveContext.weekEventReg[85], "week_event_reg[85]" },
    { &gSaveContext.weekEventReg[86], "week_event_reg[86]" },
    { &gSaveContext.weekEventReg[87], "week_event_reg[87]" },
    { &gSaveContext.weekEventReg[88], "week_event_reg[88]" },
    { &gSaveContext.weekEventReg[89], "week_event_reg[89]" },
    { &gSaveContext.weekEventReg[90], "week_event_reg[90]" },
    { &gSaveContext.weekEventReg[91], "week_event_reg[91]" },
    { &gSaveContext.weekEventReg[92], "week_event_reg[92]" },
    { &gSaveContext.weekEventReg[93], "week_event_reg[93]" },
    { &gSaveContext.weekEventReg[94], "week_event_reg[94]" },
    { &gSaveContext.weekEventReg[95], "week_event_reg[95]" },
    { &gSaveContext.weekEventReg[96], "week_event_reg[96]" },
    { &gSaveContext.weekEventReg[97], "week_event_reg[97]" },
    { &gSaveContext.weekEventReg[98], "week_event_reg[98]" },
    { &gSaveContext.weekEventReg[99], "week_event_reg[99]" },
    { &gSaveContext.eventInf[0], "event_inf[0]" },
    { &gSaveContext.eventInf[1], "event_inf[1]" },
    { &gSaveContext.eventInf[2], "event_inf[2]" },
    { &gSaveContext.eventInf[3], "event_inf[3]" },
    { &gSaveContext.eventInf[4], "event_inf[4]" },
    { &gSaveContext.eventInf[5], "event_inf[5]" },
    { &gSaveContext.eventInf[6], "event_inf[6]" },
    { &gSaveContext.eventInf[7], "event_inf[7]" },
    { &gSaveContext.maskMaskBit[0], "mask_mask_bit[0]" },
    { &gSaveContext.maskMaskBit[1], "mask_mask_bit[1]" },
    { &gSaveContext.maskMaskBit[2], "mask_mask_bit[2]" },
    { NULL, 0 }, // used in the code
};

s32 D_801AEC70 = 0; // entryIdx
u32 D_801AEC74 = 0; // curBit
s32 D_801AEC78 = 0; // timer

void func_800B32D0(GameState* gameState) {

    GlobalContext* globalCtx = (GlobalContext*)gameState;
    Input* input = &globalCtx->state.input[0];

    if (CHECK_BTN_ALL(input->press.button, BTN_DLEFT)) {
        D_801AEC74++;
        D_801AEC78 = 10;
    }

    if (CHECK_BTN_ALL(input->press.button, BTN_DRIGHT)) {
        D_801AEC74--;
        D_801AEC78 = 10;
    }

    if (D_801AEC78 == 0) {
        if (CHECK_BTN_ALL(input->cur.button, BTN_DLEFT)) {
            D_801AEC74++;
            D_801AEC78 = 2;
        }
        if (CHECK_BTN_ALL(input->cur.button, BTN_DRIGHT)) {
            D_801AEC74--;
            D_801AEC78 = 2;
        }
    }

    D_801AEC74 %= 8;
    if (CHECK_BTN_ALL(input->press.button, BTN_DUP)) {
        D_801AEC70--;
        if (D_801AEC70 < 0) {
            D_801AEC70 = 0;
        }
        D_801AEC78 = 10;
    }

    if (CHECK_BTN_ALL(input->press.button, BTN_DDOWN)) {
        D_801AEC70++;
        if ((D_801AE8F0[D_801AEC70].value) == NULL) {
            D_801AEC70--;
        }
        D_801AEC78 = 10;
    }

    if (CHECK_BTN_ALL(input->press.button, BTN_CUP)) {
        D_801AEC70 -= 10;
        if (D_801AEC70 < 0) {
            D_801AEC70 = 0;
        }
        D_801AEC78 = 10;
    }

    if (CHECK_BTN_ALL(input->press.button, BTN_CDOWN)) {
        D_801AEC70 += 10;
        if (D_801AEC70 > 100) {
            D_801AEC70 = 100;
        }
        D_801AEC78 = 10;
    }

    if (D_801AEC78 == 0) {
        if (CHECK_BTN_ALL(input->cur.button, BTN_DUP)) {
            D_801AEC70--;
            if (D_801AEC70 < 0) {
                D_801AEC70 = 0;
            }
            D_801AEC78 = 2;
        } else if (CHECK_BTN_ALL(input->cur.button, BTN_DDOWN)) {
            D_801AEC70++;
            if ((D_801AE8F0[D_801AEC70].value) == NULL) {
                D_801AEC70--;
            }
            D_801AEC78 = 2;
        } else if (CHECK_BTN_ALL(input->cur.button, BTN_CUP)) {
            D_801AEC70 -= 10;
            if (D_801AEC70 < 0) {
                D_801AEC70 = 0;
            }
            D_801AEC78 = 2;
        } else if (CHECK_BTN_ALL(input->cur.button, BTN_CDOWN)) {
            D_801AEC70 += 10;
            if (D_801AEC70 > 100) {
                D_801AEC70 = 100;
            }
            D_801AEC78 = 2;
        }
    }

    // A toggles a value
    if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
        *D_801AE8F0[D_801AEC70].value ^= (1 << D_801AEC74);
    }

    if (D_801AEC78 != 0) {
        D_801AEC78--;
    }

    // Start + B will reset the first two flag arrays
    if (CHECK_BTN_ALL(input->cur.button, BTN_START)) {
        if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
            s16 i;
            for (i = 0; i < 100; i++) {
                gSaveContext.weekEventReg[i] = 0;
            }
            for (i = 0; i < 8; i++) {
                gSaveContext.eventInf[i] = 0;
            }
        }

        // Pressing B will exit
    } else if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
        globalCtx->pauseCtx.debugState = 0;
    }
}

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
