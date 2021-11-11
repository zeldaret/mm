#include "global.h"

u16 func_800F05C0(GlobalContext* globalCtx) {
    if (INV_CONTENT(ITEM_OCARINA) == ITEM_OCARINA) {
        return 0;
    }
    if (CURRENT_DAY <= 0) {
        return 0;
    }
    if (gSaveContext.weekEventReg[0x58] & 0x20) {
        return 0;
    }
    if (gSaveContext.weekEventReg[0x4F] & 0x10) {
        if (gSaveContext.weekEventReg[8] & 0x40) {
            return 0;
        }
        return 0x224;
    }
    if (!(gSaveContext.weekEventReg[8] & 0x80)) {
        if (gSaveContext.weekEventReg[9] & 1) {
            return 0x21E;
        }
        if (globalCtx->sceneNum == SCENE_YOUSEI_IZUMI) {
            return 0;
        }
        return 0x21D;
    }
    if (gSaveContext.magicAcquired != true) {
        return 0x21F;
    }
    if (INV_CONTENT(ITEM_DEED_LAND) == ITEM_DEED_LAND) {
        if (globalCtx->sceneNum != SCENE_OKUJOU) {
            return 0x244;
        }
        return 0;
    }
    if (INV_CONTENT(ITEM_MOON_TEAR) == ITEM_MOON_TEAR) {
        if (gSaveContext.weekEventReg[0x56] & 4) {
            return 0x242;
        }
        return 0x243;
    }
    if (gSaveContext.weekEventReg[0x4A] & 0x20) {
        return 0x223;
    }
    if (gSaveContext.weekEventReg[0x49] & 0x80) {
        return 0x222;
    }
    if (gSaveContext.weekEventReg[0x49] & 0x20) {
        return 0x221;
    }
    if (gSaveContext.weekEventReg[0x4D] & 2) {
        if (gSaveContext.weekEventReg[0x49] & 0x10) {
            return 0x240;
        }
        return 0x241;
    }
    if ((gSaveContext.weekEventReg[0x56] & 2) || (gSaveContext.weekEventReg[0x49] & 0x40)) {
        return 0x23F;
    }
    return 0x220;
}
