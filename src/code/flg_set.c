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

static FlagSetEntry sFlagEntries[] = {
    { &gSaveContext.save.weekEventReg[0], "week_event_reg[0]" },
    { &gSaveContext.save.weekEventReg[1], "week_event_reg[1]" },
    { &gSaveContext.save.weekEventReg[2], "week_event_reg[2]" },
    { &gSaveContext.save.weekEventReg[3], "week_event_reg[3]" },
    { &gSaveContext.save.weekEventReg[4], "week_event_reg[4]" },
    { &gSaveContext.save.weekEventReg[5], "week_event_reg[5]" },
    { &gSaveContext.save.weekEventReg[6], "week_event_reg[6]" },
    { &gSaveContext.save.weekEventReg[7], "week_event_reg[7]" },
    { &gSaveContext.save.weekEventReg[8], "week_event_reg[8]" },
    { &gSaveContext.save.weekEventReg[9], "week_event_reg[9]" },
    { &gSaveContext.save.weekEventReg[10], "week_event_reg[10]" },
    { &gSaveContext.save.weekEventReg[11], "week_event_reg[11]" },
    { &gSaveContext.save.weekEventReg[12], "week_event_reg[12]" },
    { &gSaveContext.save.weekEventReg[13], "week_event_reg[13]" },
    { &gSaveContext.save.weekEventReg[14], "week_event_reg[14]" },
    { &gSaveContext.save.weekEventReg[15], "week_event_reg[15]" },
    { &gSaveContext.save.weekEventReg[16], "week_event_reg[16]" },
    { &gSaveContext.save.weekEventReg[17], "week_event_reg[17]" },
    { &gSaveContext.save.weekEventReg[18], "week_event_reg[18]" },
    { &gSaveContext.save.weekEventReg[19], "week_event_reg[19]" },
    { &gSaveContext.save.weekEventReg[20], "week_event_reg[20]" },
    { &gSaveContext.save.weekEventReg[21], "week_event_reg[21]" },
    { &gSaveContext.save.weekEventReg[22], "week_event_reg[22]" },
    { &gSaveContext.save.weekEventReg[23], "week_event_reg[23]" },
    { &gSaveContext.save.weekEventReg[24], "week_event_reg[24]" },
    { &gSaveContext.save.weekEventReg[25], "week_event_reg[25]" },
    { &gSaveContext.save.weekEventReg[26], "week_event_reg[26]" },
    { &gSaveContext.save.weekEventReg[27], "week_event_reg[27]" },
    { &gSaveContext.save.weekEventReg[28], "week_event_reg[28]" },
    { &gSaveContext.save.weekEventReg[29], "week_event_reg[29]" },
    { &gSaveContext.save.weekEventReg[30], "week_event_reg[30]" },
    { &gSaveContext.save.weekEventReg[31], "week_event_reg[31]" },
    { &gSaveContext.save.weekEventReg[32], "week_event_reg[32]" },
    { &gSaveContext.save.weekEventReg[33], "week_event_reg[33]" },
    { &gSaveContext.save.weekEventReg[34], "week_event_reg[34]" },
    { &gSaveContext.save.weekEventReg[35], "week_event_reg[35]" },
    { &gSaveContext.save.weekEventReg[36], "week_event_reg[36]" },
    { &gSaveContext.save.weekEventReg[37], "week_event_reg[37]" },
    { &gSaveContext.save.weekEventReg[38], "week_event_reg[38]" },
    { &gSaveContext.save.weekEventReg[39], "week_event_reg[39]" },
    { &gSaveContext.save.weekEventReg[40], "week_event_reg[40]" },
    { &gSaveContext.save.weekEventReg[41], "week_event_reg[41]" },
    { &gSaveContext.save.weekEventReg[42], "week_event_reg[42]" },
    { &gSaveContext.save.weekEventReg[43], "week_event_reg[43]" },
    { &gSaveContext.save.weekEventReg[44], "week_event_reg[44]" },
    { &gSaveContext.save.weekEventReg[45], "week_event_reg[45]" },
    { &gSaveContext.save.weekEventReg[46], "week_event_reg[46]" },
    { &gSaveContext.save.weekEventReg[47], "week_event_reg[47]" },
    { &gSaveContext.save.weekEventReg[48], "week_event_reg[48]" },
    { &gSaveContext.save.weekEventReg[49], "week_event_reg[49]" },
    { &gSaveContext.save.weekEventReg[50], "week_event_reg[50]" },
    { &gSaveContext.save.weekEventReg[51], "week_event_reg[51]" },
    { &gSaveContext.save.weekEventReg[52], "week_event_reg[52]" },
    { &gSaveContext.save.weekEventReg[53], "week_event_reg[53]" },
    { &gSaveContext.save.weekEventReg[54], "week_event_reg[54]" },
    { &gSaveContext.save.weekEventReg[55], "week_event_reg[55]" },
    { &gSaveContext.save.weekEventReg[56], "week_event_reg[56]" },
    { &gSaveContext.save.weekEventReg[57], "week_event_reg[57]" },
    { &gSaveContext.save.weekEventReg[58], "week_event_reg[58]" },
    { &gSaveContext.save.weekEventReg[59], "week_event_reg[59]" },
    { &gSaveContext.save.weekEventReg[60], "week_event_reg[60]" },
    { &gSaveContext.save.weekEventReg[61], "week_event_reg[61]" },
    { &gSaveContext.save.weekEventReg[62], "week_event_reg[62]" },
    { &gSaveContext.save.weekEventReg[63], "week_event_reg[63]" },
    { &gSaveContext.save.weekEventReg[64], "week_event_reg[64]" },
    { &gSaveContext.save.weekEventReg[65], "week_event_reg[65]" },
    { &gSaveContext.save.weekEventReg[66], "week_event_reg[66]" },
    { &gSaveContext.save.weekEventReg[67], "week_event_reg[67]" },
    { &gSaveContext.save.weekEventReg[68], "week_event_reg[68]" },
    { &gSaveContext.save.weekEventReg[69], "week_event_reg[69]" },
    { &gSaveContext.save.weekEventReg[70], "week_event_reg[70]" },
    { &gSaveContext.save.weekEventReg[71], "week_event_reg[71]" },
    { &gSaveContext.save.weekEventReg[72], "week_event_reg[72]" },
    { &gSaveContext.save.weekEventReg[73], "week_event_reg[73]" },
    { &gSaveContext.save.weekEventReg[74], "week_event_reg[74]" },
    { &gSaveContext.save.weekEventReg[75], "week_event_reg[75]" },
    { &gSaveContext.save.weekEventReg[76], "week_event_reg[76]" },
    { &gSaveContext.save.weekEventReg[77], "week_event_reg[77]" },
    { &gSaveContext.save.weekEventReg[78], "week_event_reg[78]" },
    { &gSaveContext.save.weekEventReg[79], "week_event_reg[79]" },
    { &gSaveContext.save.weekEventReg[80], "week_event_reg[80]" },
    { &gSaveContext.save.weekEventReg[81], "week_event_reg[81]" },
    { &gSaveContext.save.weekEventReg[82], "week_event_reg[82]" },
    { &gSaveContext.save.weekEventReg[83], "week_event_reg[83]" },
    { &gSaveContext.save.weekEventReg[84], "week_event_reg[84]" },
    { &gSaveContext.save.weekEventReg[85], "week_event_reg[85]" },
    { &gSaveContext.save.weekEventReg[86], "week_event_reg[86]" },
    { &gSaveContext.save.weekEventReg[87], "week_event_reg[87]" },
    { &gSaveContext.save.weekEventReg[88], "week_event_reg[88]" },
    { &gSaveContext.save.weekEventReg[89], "week_event_reg[89]" },
    { &gSaveContext.save.weekEventReg[90], "week_event_reg[90]" },
    { &gSaveContext.save.weekEventReg[91], "week_event_reg[91]" },
    { &gSaveContext.save.weekEventReg[92], "week_event_reg[92]" },
    { &gSaveContext.save.weekEventReg[93], "week_event_reg[93]" },
    { &gSaveContext.save.weekEventReg[94], "week_event_reg[94]" },
    { &gSaveContext.save.weekEventReg[95], "week_event_reg[95]" },
    { &gSaveContext.save.weekEventReg[96], "week_event_reg[96]" },
    { &gSaveContext.save.weekEventReg[97], "week_event_reg[97]" },
    { &gSaveContext.save.weekEventReg[98], "week_event_reg[98]" },
    { &gSaveContext.save.weekEventReg[99], "week_event_reg[99]" },

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

    { NULL, NULL }, // used in the code to detect array end
};

static s32 sEntryIndex = 0;
static u32 sCurrentBit = 0;
static s32 sTimer = 0;

void FlagSet_Update(GameState* gameState) {
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    Input* input = CONTROLLER1(globalCtx);

    /* Intra-byte navigation */

    if (CHECK_BTN_ALL(input->press.button, BTN_DLEFT)) {
        sCurrentBit++;
        sTimer = 10;
    }

    if (CHECK_BTN_ALL(input->press.button, BTN_DRIGHT)) {
        sCurrentBit--;
        sTimer = 10;
    }

    if (sTimer == 0) {
        if (CHECK_BTN_ALL(input->cur.button, BTN_DLEFT)) {
            sCurrentBit++;
            sTimer = 2;
        }
        if (CHECK_BTN_ALL(input->cur.button, BTN_DRIGHT)) {
            sCurrentBit--;
            sTimer = 2;
        }
    }

    // Wrap cursor position at beginning/end of line
    sCurrentBit %= 8;

    /* Navigation between bytes */

    // + Up/Down scroll 1 at a time
    if (CHECK_BTN_ALL(input->press.button, BTN_DUP)) {
        sEntryIndex--;
        if (sEntryIndex < 0) {
            sEntryIndex = 0;
        }
        sTimer = 10;
    }

    if (CHECK_BTN_ALL(input->press.button, BTN_DDOWN)) {
        sEntryIndex++;
        if (sFlagEntries[sEntryIndex].value == NULL) { // End of array
            sEntryIndex--;
        }
        sTimer = 10;
    }

    // C Up/Down scroll 10 at a time
    if (CHECK_BTN_ALL(input->press.button, BTN_CUP)) {
        sEntryIndex -= 10;
        if (sEntryIndex < 0) {
            sEntryIndex = 0;
        }
        sTimer = 10;
    }

    if (CHECK_BTN_ALL(input->press.button, BTN_CDOWN)) {
        sEntryIndex += 10;
        if (sEntryIndex > 100) {
            sEntryIndex = 100;
        }
        sTimer = 10;
    }

    if (sTimer == 0) {
        if (CHECK_BTN_ALL(input->cur.button, BTN_DUP)) {
            sEntryIndex--;
            if (sEntryIndex < 0) {
                sEntryIndex = 0;
            }
            sTimer = 2;

        } else if (CHECK_BTN_ALL(input->cur.button, BTN_DDOWN)) {
            sEntryIndex++;
            if (sFlagEntries[sEntryIndex].value == NULL) { // End of array
                sEntryIndex--;
            }
            sTimer = 2;

        } else if (CHECK_BTN_ALL(input->cur.button, BTN_CUP)) {
            sEntryIndex -= 10;
            if (sEntryIndex < 0) {
                sEntryIndex = 0;
            }
            sTimer = 2;

        } else if (CHECK_BTN_ALL(input->cur.button, BTN_CDOWN)) {
            sEntryIndex += 10;
            if (sEntryIndex > 100) {
                sEntryIndex = 100;
            }
            sTimer = 2;
        }
    }

    /* Other controls */

    // A toggles the selected flag
    if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
        *sFlagEntries[sEntryIndex].value ^= (1 << sCurrentBit);
    }

    if (sTimer != 0) {
        sTimer--;
    }

    // Hold Start and press B will reset the first two flag arrays
    if (CHECK_BTN_ALL(input->cur.button, BTN_START)) {
        if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
            s16 i;
            for (i = 0; i < ARRAY_COUNT(gSaveContext.save.weekEventReg); i++) {
                gSaveContext.save.weekEventReg[i] = 0;
            }
            for (i = 0; i < ARRAY_COUNT(gSaveContext.eventInf); i++) {
                gSaveContext.eventInf[i] = 0;
            }
        }

        // Pressing B will exit
    } else if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
        globalCtx->pauseCtx.debugState = 0;
    }
}

extern s32 D_801ED890;

void FlagSet_Draw(GameState* gameState) {
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
    GfxPrint_Printf(&printer, sFlagEntries[sEntryIndex].name);
    GfxPrint_SetPos(&printer, 12, 15);

    // Print the flag bits in the current byte, largest to smallest
    for (D_801ED890 = 7; D_801ED890 >= 0; D_801ED890--) {
        // Highlight current flag bit in white, rest in grey
        if ((u32)D_801ED890 == sCurrentBit) {
            GfxPrint_SetColor(&printer, 200, 200, 200, 255);
        } else {
            GfxPrint_SetColor(&printer, 100, 100, 100, 255);
        }

        // Display 1 if flag set and 0 if not
        if (*sFlagEntries[sEntryIndex].value & (1 << D_801ED890)) {
            GfxPrint_Printf(&printer, "1");
        } else {
            GfxPrint_Printf(&printer, "0");
        }

        // Add a space after each group of 4
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
