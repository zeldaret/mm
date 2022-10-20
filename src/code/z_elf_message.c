/**
 * @file z_elf_message.c
 *
 * This file provides quest hints through Tatl.
 *
 * In Ocarina of Time, this was a more elaborate system that determined
 * which hint to give based on a script.
 * That system has been replaced with a single function that hardcodes the checks.
 */
#include "global.h"

/**
 * Gets the relevant text ID for Tatl hints in first cycle.
 */
u16 QuestHint_GetTatlTextId(PlayState* play) {
    if (INV_CONTENT(ITEM_OCARINA) == ITEM_OCARINA) {
        return 0;
    }

    if (CURRENT_DAY <= 0) {
        return 0;
    }

    if (gSaveContext.save.weekEventReg[88] & 0x20) {
        return 0;
    }

    if (gSaveContext.save.weekEventReg[79] & 0x10) {
        if (gSaveContext.save.weekEventReg[8] & 0x40) {
            return 0;
        }

        return 0x224;
    }

    if (!(gSaveContext.save.weekEventReg[8] & 0x80)) {
        if (gSaveContext.save.weekEventReg[9] & 1) {
            return 0x21E;
        }

        if (play->sceneId == SCENE_YOUSEI_IZUMI) {
            return 0;
        }

        return 0x21D;
    }

    if (gSaveContext.save.playerData.isMagicAcquired != true) {
        return 0x21F;
    }

    if (INV_CONTENT(ITEM_DEED_LAND) == ITEM_DEED_LAND) {
        if (play->sceneId != SCENE_OKUJOU) {
            return 0x244;
        }

        return 0;
    }

    if (INV_CONTENT(ITEM_MOON_TEAR) == ITEM_MOON_TEAR) {
        if (gSaveContext.save.weekEventReg[86] & 4) {
            return 0x242;
        }

        return 0x243;
    }

    if (gSaveContext.save.weekEventReg[74] & 0x20) {
        return 0x223;
    }

    if (gSaveContext.save.weekEventReg[73] & 0x80) {
        return 0x222;
    }

    if (gSaveContext.save.weekEventReg[73] & 0x20) {
        return 0x221;
    }

    if (gSaveContext.save.weekEventReg[77] & 2) {
        if (gSaveContext.save.weekEventReg[73] & 0x10) {
            return 0x240;
        }

        return 0x241;
    }

    if ((gSaveContext.save.weekEventReg[86] & 2) || (gSaveContext.save.weekEventReg[73] & 0x40)) {
        return 0x23F;
    }

    return 0x220;
}
