#include "global.h"

static s16 sHeartsPrimColors[3][3] = { { 0x00FF, 0x0046, 0x0032 }, { 0x00FF, 0x00BE, 0x0000 }, { 0x0064, 0x0064, 0x00FF } };
static s16 sHeartsEnvColors[3][3] = { { 0x0032, 0x0028, 0x003C }, { 0x00FF, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x00FF } };
static s16 sHeartsPrimFactors[3][3] = { { 0x0000, 0x0000, 0x0000 }, { 0x0000, 0x0078, 0xFFCE }, { 0xFF65, 0x001E, 0x00CD } };
static s16 sHeartsEnvFactors[3][3] = { { 0x0000, 0x0000, 0x0000 }, { 0x00CD, 0xFFD8, 0xFFC4 }, { 0xFFCE, 0xFFD8, 0x00C3 } };
static s16 sHeartsDDPrimColors[3][3] = { { 0x00FF, 0x00FF, 0x00FF }, { 0x00FF, 0x00BE, 0x0000 }, { 0x0064, 0x0064, 0x00FF } };

static s16 sHeartsDDEnvColors[3][3] = { { 0x00C8, 0x0000, 0x0000 }, { 0x00FF, 0x0000, 0x0000 }, { 0x0000, 0x0000, 0x00FF } };

static s16 sHeartsDDPrimFactors[3][3] = {
    { 0x0000, 0x0000, 0x0000 },
    { 0x0000, 0xFFBF, 0xFF01 },
    { 0xFF65, 0xFF65, 0x0000 },
};
static s16 sHeartsDDEnvFactors[3][3] = { { 0x0000, 0x0000, 0x0000 }, { 0x0037, 0x0000, 0x0000 }, { 0xFF38, 0x0000, 0x00FF } };

s16 sBeatingHeartsDDPrim[3];
s16 sBeatingHeartsDDEnv[3];
s16 sHeartsDDPrim[2][3];
s16 sHeartsDDEnv[2][3];

void LifeMeter_Init(GlobalContext* globalCtx) {
    InterfaceContext* interfaceCtx = &globalCtx->interfaceCtx;

    interfaceCtx->unk_250 = 0x140;

    interfaceCtx->unk_24E = gSaveContext.health;

    interfaceCtx->lifeColorChange = 0;
    interfaceCtx->lifeColorChangeDirection = 0;

    interfaceCtx->lifeSizeChange = interfaceCtx->lifeColorChange;
    interfaceCtx->lifeSizeChangeDirection = interfaceCtx->lifeColorChangeDirection;

    interfaceCtx->heartsPrimR[0] = 0xFF;
    interfaceCtx->heartsPrimG[0] = 0x46;
    interfaceCtx->heartsPrimB[0] = 0x32;

    interfaceCtx->heartsEnvR[0] = 0x32;
    interfaceCtx->heartsEnvG[0] = 0x28;
    interfaceCtx->heartsEnvB[0] = 0x3C;

    interfaceCtx->heartsPrimR[1] = 0xFF;
    interfaceCtx->heartsPrimG[1] = 0x46;
    interfaceCtx->heartsPrimB[1] = 0x32;

    interfaceCtx->heartsEnvR[1] = 0x32;
    interfaceCtx->heartsEnvG[1] = 0x28;
    interfaceCtx->heartsEnvB[1] = 0x3C;

    sHeartsDDPrim[0][0] = sHeartsDDPrim[1][0] = 0xFF;
    sHeartsDDPrim[0][1] = sHeartsDDPrim[1][1] = 0xFF;
    sHeartsDDPrim[0][2] = sHeartsDDPrim[1][2] = 0xFF;

    sHeartsDDEnv[0][0] = sHeartsDDEnv[1][0] = 0xC8;
    sHeartsDDEnv[0][1] = sHeartsDDEnv[1][1] = 0;
    sHeartsDDEnv[0][2] = sHeartsDDEnv[1][2] = 0;
}

void LifeMeter_UpdateColors(GlobalContext* globalCtx) {
    InterfaceContext* interfaceCtx = &globalCtx->interfaceCtx;
    f32 factorBeating = interfaceCtx->lifeColorChange * 0.1f;
    f32 ddFactor;
    s32 type = 0;
    s32 ddType;
    s16 rFactor;
    s16 gFactor;
    s16 bFactor;

    if (interfaceCtx) {}

    if (interfaceCtx->lifeColorChangeDirection != 0) {
        interfaceCtx->lifeColorChange--;
        if (interfaceCtx->lifeColorChange <= 0) {
            interfaceCtx->lifeColorChange = 0;
            interfaceCtx->lifeColorChangeDirection = 0;
        }
    } else {
        interfaceCtx->lifeColorChange++;
        if (interfaceCtx->lifeColorChange >= 10) {
            interfaceCtx->lifeColorChange = 10;
            interfaceCtx->lifeColorChangeDirection = 1;
        }
    }

    ddFactor = factorBeating;

    interfaceCtx->heartsPrimR[0] = 0xFF;
    interfaceCtx->heartsPrimG[0] = 0x46;
    interfaceCtx->heartsPrimB[0] = 0x32;

    interfaceCtx->heartsEnvR[0] = 0x32;
    interfaceCtx->heartsEnvG[0] = 0x28;
    interfaceCtx->heartsEnvB[0] = 0x3C;

    interfaceCtx->heartsPrimR[1] = sHeartsPrimColors[type][0];
    interfaceCtx->heartsPrimG[1] = sHeartsPrimColors[type][1];
    interfaceCtx->heartsPrimB[1] = sHeartsPrimColors[type][2];

    interfaceCtx->heartsEnvR[1] = sHeartsEnvColors[type][0];
    interfaceCtx->heartsEnvG[1] = sHeartsEnvColors[type][1];
    interfaceCtx->heartsEnvB[1] = sHeartsEnvColors[type][2];

    rFactor = sHeartsPrimFactors[0][0] * factorBeating;
    gFactor = sHeartsPrimFactors[0][1] * factorBeating;
    bFactor = sHeartsPrimFactors[0][2] * factorBeating;

    interfaceCtx->beatingHeartPrim[0] = (u8)(rFactor + 0xFF) & 0xFF;
    interfaceCtx->beatingHeartPrim[1] = (u8)(gFactor + 0x46) & 0xFF;
    interfaceCtx->beatingHeartPrim[2] = (u8)(bFactor + 0x32) & 0xFF;

    rFactor = sHeartsEnvFactors[0][0] * factorBeating;
    gFactor = sHeartsEnvFactors[0][1] * factorBeating;
    bFactor = sHeartsEnvFactors[0][2] * factorBeating;

    if (1) {}
    ddType = type;

    interfaceCtx->beatingHeartEnv[0] = (u8)(rFactor + 0x32) & 0xFF;
    interfaceCtx->beatingHeartEnv[1] = (u8)(gFactor + 0x28) & 0xFF;
    interfaceCtx->beatingHeartEnv[2] = (u8)(bFactor + 0x3C) & 0xFF;

    sHeartsDDPrim[0][0] = 0xFF;
    sHeartsDDPrim[0][1] = 0xFF;
    sHeartsDDPrim[0][2] = 0xFF;

    sHeartsDDEnv[0][0] = 0xC8;
    sHeartsDDEnv[0][1] = 0x00;
    sHeartsDDEnv[0][2] = 0x00;

    sHeartsDDPrim[1][0] = sHeartsDDPrimColors[ddType][0];
    sHeartsDDPrim[1][1] = sHeartsDDPrimColors[ddType][1];
    sHeartsDDPrim[1][2] = sHeartsDDPrimColors[ddType][2];

    sHeartsDDEnv[1][0] = sHeartsDDEnvColors[ddType][0];
    sHeartsDDEnv[1][1] = sHeartsDDEnvColors[ddType][1];
    sHeartsDDEnv[1][2] = sHeartsDDEnvColors[ddType][2];

    rFactor = sHeartsDDPrimFactors[ddType][0] * ddFactor;
    gFactor = sHeartsDDPrimFactors[ddType][1] * ddFactor;
    bFactor = sHeartsDDPrimFactors[ddType][2] * ddFactor;

    sBeatingHeartsDDPrim[0] = (u8)(rFactor + 0xFF) & 0xFF;
    sBeatingHeartsDDPrim[1] = (u8)(gFactor + 0xFF) & 0xFF;
    sBeatingHeartsDDPrim[2] = (u8)(bFactor + 0xFF) & 0xFF;

    rFactor = sHeartsDDEnvFactors[ddType][0] * ddFactor;
    gFactor = sHeartsDDEnvFactors[ddType][1] * ddFactor;
    bFactor = sHeartsDDEnvFactors[ddType][2] * ddFactor;

    sBeatingHeartsDDEnv[0] = (u8)(rFactor + 0xC8) & 0xFF;
    sBeatingHeartsDDEnv[1] = (u8)(gFactor + 0x00) & 0xFF;
    sBeatingHeartsDDEnv[2] = (u8)(bFactor + 0x00) & 0xFF;
}

s32 func_80100A80(GlobalContext* globalCtx) {
    gSaveContext.health = (s16)globalCtx->interfaceCtx.unk_24E;
    return 1;
}

s32 func_80100AA0(GlobalContext* globalCtx) {
    InterfaceContext* interfaceCtx = &globalCtx->interfaceCtx;
    interfaceCtx->unk_250 = 0x140;
    interfaceCtx->unk_24E = interfaceCtx->unk_24E + 0x10;
    if (globalCtx->interfaceCtx.unk_24E >= gSaveContext.health) {
        globalCtx->interfaceCtx.unk_24E = gSaveContext.health;
        return 1;
    }
    return 0;
}

s32 func_80100AF0(GlobalContext* globalCtx) {
    InterfaceContext* interfaceCtx = &globalCtx->interfaceCtx;
    s32 health;
    if (interfaceCtx->unk_250 != 0) {
        interfaceCtx->unk_250 -= 1;
    } else {
        interfaceCtx->unk_250 = 0x140;
        interfaceCtx->unk_24E -= 0x10;
        if (interfaceCtx->unk_24E <= 0) {
            interfaceCtx->unk_24E = 0;
            globalCtx->damagePlayer(globalCtx, -((health = gSaveContext.health) + 1));
            return 1;
        }
    }
    return 0;
}

extern TexturePtr D_02000000; // Empty heart texture
extern TexturePtr D_02000100; // Quarter Heart texture
extern TexturePtr D_02000200; // Half Heart texture
extern TexturePtr D_02000300; // Three Quarter Heart texture
extern TexturePtr D_02000400; // Full heart texture
extern TexturePtr D_02000500; // Empty Double Defense Heart texture
extern TexturePtr D_02000600; // Quarter Double Defense Heart texture
extern TexturePtr D_02000700; // Half Double Defense Heart texture
extern TexturePtr D_02000800; // Three Quarter Double Defense Heart texture
extern TexturePtr D_02000900; // Full Double Defense Heart texture

TexturePtr HeartTextures[] = {
    &D_02000400,                                                 // Full
    &D_02000100, &D_02000100, &D_02000100, &D_02000100, &D_02000100, // Quarter
    &D_02000200, &D_02000200, &D_02000200, &D_02000200, &D_02000200, // Half
    &D_02000300, &D_02000300, &D_02000300, &D_02000300, &D_02000300  // Three Quarter
};

TexturePtr HeartDDTextures[] = {
    &D_02000900,                                                 // Full
    &D_02000600, &D_02000600, &D_02000600, &D_02000600, &D_02000600, // Quarter
    &D_02000700, &D_02000700, &D_02000700, &D_02000700, &D_02000700, // Half
    &D_02000800, &D_02000800, &D_02000800, &D_02000800, &D_02000800  // Three Quarter
};



void LifeMeter_Draw(GlobalContext* globalCtx) {
    s32 pad[5];
    UNK_PTR heartTex;
    s32 curColorSet;
    f32 offsetX;
    f32 offsetY;
    s32 i;
    f32 posY;
    f32 posX;
    f32 halfTexSize;
    f32 temp_f4;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    InterfaceContext* interfaceCtx = &globalCtx->interfaceCtx;
    Vtx* beatingHeartVtx = interfaceCtx->beatingHeartVtx;
    s32 fractionHeartCount = gSaveContext.health % 0x10;
    s16 healthCapacity = gSaveContext.healthCapacity / 0x10;
    s16 fullHeartCount = gSaveContext.health / 0x10;
    s32 pad2;
    f32 lifesize = interfaceCtx->lifeSizeChange * 0.1f;
    u32 curCombineModeSet = 0;
    UNK_PTR temp = NULL;
    s32 ddCount = gSaveContext.inventory.dungeonKeys[9] - 1;

    OPEN_DISPS(gfxCtx);

    if (!(gSaveContext.health % 0x10))
        fullHeartCount--;
    offsetY = 0.0f;
    offsetX = 0.0f;
    curColorSet = -1;

    for (i = 0; i < healthCapacity; i++) {
        if ((ddCount < 0) || (ddCount < i)) {
            if (i < fullHeartCount) {
                if (curColorSet != 0) {
                    curColorSet = 0;
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, interfaceCtx->heartsPrimR[0], interfaceCtx->heartsPrimG[0],
                                    interfaceCtx->heartsPrimB[0], interfaceCtx->healthAlpha);
                    gDPSetEnvColor(OVERLAY_DISP++, interfaceCtx->heartsEnvR[0], interfaceCtx->heartsEnvG[0],
                                   interfaceCtx->heartsEnvB[0], 0xFF);
                }
            } else if (fullHeartCount == i) {
                if (curColorSet != 1) {
                    curColorSet = 1;
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, interfaceCtx->beatingHeartPrim[0],
                                    interfaceCtx->beatingHeartPrim[1], interfaceCtx->beatingHeartPrim[2],
                                    interfaceCtx->healthAlpha);
                    gDPSetEnvColor(OVERLAY_DISP++, interfaceCtx->beatingHeartEnv[0], interfaceCtx->beatingHeartEnv[1],
                                   interfaceCtx->beatingHeartEnv[2], 0xFF);
                }
            } else if (fullHeartCount < i) {
                if (curColorSet != 2) {
                    curColorSet = 2;
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, interfaceCtx->heartsPrimR[0], interfaceCtx->heartsPrimG[0],
                                    interfaceCtx->heartsPrimB[0], interfaceCtx->healthAlpha);
                    gDPSetEnvColor(OVERLAY_DISP++, interfaceCtx->heartsEnvR[0], interfaceCtx->heartsEnvG[0],
                                   interfaceCtx->heartsEnvB[0], 0xFF);
                }
            } else {
                if (curColorSet != 3) {
                    curColorSet = 3;
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, interfaceCtx->heartsPrimR[1], interfaceCtx->heartsPrimG[1],
                                    interfaceCtx->heartsPrimB[1], interfaceCtx->healthAlpha);
                    gDPSetEnvColor(OVERLAY_DISP++, interfaceCtx->heartsEnvR[1], interfaceCtx->heartsEnvG[1],
                                   interfaceCtx->heartsEnvB[1], 0xFF);
                }
            }

            if (i < fullHeartCount) {
                heartTex = D_02000400;
            } else if (fullHeartCount == i) {
                heartTex = HeartTextures[fractionHeartCount];
            } else {
                heartTex = D_02000000;
            }
        } else {
            if (i < fullHeartCount) {
                if (curColorSet != 4) {
                    curColorSet = 4;
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sHeartsDDPrim[0][0], sHeartsDDPrim[0][1], sHeartsDDPrim[0][2],
                                    interfaceCtx->healthAlpha);
                    gDPSetEnvColor(OVERLAY_DISP++, sHeartsDDEnv[0][0], sHeartsDDEnv[0][1], sHeartsDDEnv[0][2], 0xFF);
                }
            } else if (fullHeartCount == i) {
                if (curColorSet != 5) {
                    curColorSet = 5;
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sBeatingHeartsDDPrim[0], sBeatingHeartsDDPrim[1],
                                    sBeatingHeartsDDPrim[2], interfaceCtx->healthAlpha);
                    gDPSetEnvColor(OVERLAY_DISP++, sBeatingHeartsDDEnv[0], sBeatingHeartsDDEnv[1],
                                   sBeatingHeartsDDEnv[2], 0xFF);
                }
            } else if (i > fullHeartCount) {
                if (curColorSet != 6) {
                    curColorSet = 6;
                    gDPPipeSync(OVERLAY_DISP++);
                    gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sHeartsDDPrim[0][0], sHeartsDDPrim[0][1], sHeartsDDPrim[0][2],
                                    interfaceCtx->healthAlpha);
                    gDPSetEnvColor(OVERLAY_DISP++, sHeartsDDEnv[0][0], sHeartsDDEnv[0][1], sHeartsDDEnv[0][2], 0xFF);
                }
            } else if (curColorSet != 7) {
                curColorSet = 7;
                gDPPipeSync(OVERLAY_DISP++);
                gDPSetPrimColor(OVERLAY_DISP++, 0, 0, sHeartsDDPrim[1][0], sHeartsDDPrim[1][1], sHeartsDDPrim[1][2],
                                interfaceCtx->healthAlpha);
                gDPSetEnvColor(OVERLAY_DISP++, sHeartsDDEnv[1][0], sHeartsDDEnv[1][1], sHeartsDDEnv[1][2], 0xFF);
            }
            if (i < fullHeartCount) {
                heartTex = D_02000900;
            } else if (fullHeartCount == i) {
                heartTex = HeartDDTextures[fractionHeartCount];
            } else {
                heartTex = D_02000500;
            }
        }

        if (temp != heartTex) {
            temp = heartTex;
            gDPLoadTextureBlock(OVERLAY_DISP++, heartTex, G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, 0,
                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                G_TX_NOLOD, G_TX_NOLOD);
        }

        if (fullHeartCount != i) {
            if ((ddCount < 0) || (i > ddCount)) {
                if (curCombineModeSet != 1) {
                    curCombineModeSet = 1;
                    func_8012C654(gfxCtx);
                    gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE,
                                      0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                }
            } else {
                if (curCombineModeSet != 3) {
                    curCombineModeSet = 3;
                    func_8012C654(gfxCtx);
                    gDPSetCombineLERP(OVERLAY_DISP++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                                      0, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
                }
            }
            {
                posY = 26.0f + offsetY;
                posX = 30.0f + offsetX;
                temp_f4 = 1.0f;
                temp_f4 /= 0.68f;
                temp_f4 *= 1 << 10;
                halfTexSize = 8.0f;
                halfTexSize *= 0.68f;
                gSPTextureRectangle(OVERLAY_DISP++, (s32)((posX - halfTexSize) * 4), (s32)((posY - halfTexSize) * 4),
                                    (s32)((posX + halfTexSize) * 4), (s32)((posY + halfTexSize) * 4), G_TX_RENDERTILE,
                                    0, 0, (s32)temp_f4, (s32)temp_f4);
            }
        } else {
            if ((ddCount < 0) || (ddCount < i)) {
                if (curCombineModeSet != 2) {
                    curCombineModeSet = 2;
                    func_8012C8D4(gfxCtx);
                    gDPSetCombineLERP(OVERLAY_DISP++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE,
                                      0, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
                    gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
                }
            } else {
                if (curCombineModeSet != 4) {
                    curCombineModeSet = 4;
                    func_8012C8D4(gfxCtx);
                    gDPSetCombineLERP(OVERLAY_DISP++, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                                      0, ENVIRONMENT, PRIMITIVE, TEXEL0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
                    gDPSetAlphaCompare(OVERLAY_DISP++, G_AC_THRESHOLD);
                }
            }
            {
                Mtx* temp_a0 = GRAPH_ALLOC(gfxCtx, sizeof(Mtx));
                func_801780F0(temp_a0, 1.0f - (0.32f * lifesize), 1.0f - (0.32f * lifesize), 1.0f - (0.32f * lifesize),
                              -130.0f + offsetX, 94.5f - offsetY, 0.0f);
                gSPMatrix(OVERLAY_DISP++, temp_a0, G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPVertex(OVERLAY_DISP++, beatingHeartVtx, 4, 0);
                gSP1Quadrangle(OVERLAY_DISP++, 0, 2, 3, 1, 0);
            }
        }
        offsetX += 10.0f;
        if (i == 9) {
            offsetY += 10.0f;
            offsetX = 0.0f;
        }
    }
    CLOSE_DISPS(gfxCtx);
}

void LifeMeter_UpdateSizeAndBeep(GlobalContext* globalCtx) {
    InterfaceContext* interfaceCtx = &globalCtx->interfaceCtx;
    if (interfaceCtx->lifeSizeChangeDirection != 0) {
        interfaceCtx->lifeSizeChange--;
        if (interfaceCtx->lifeSizeChange <= 0) {
            interfaceCtx->lifeSizeChange = 0;
            interfaceCtx->lifeSizeChangeDirection = 0;
            if (func_801233E4(globalCtx) == 0 && (globalCtx->pauseCtx.state == 0) &&
                (globalCtx->pauseCtx.debugState == 0) && LifeMeter_IsCritical() && func_801690CC(globalCtx) == 0) {
                play_sound(NA_SE_SY_HITPOINT_ALARM);
            }
        }
    } else {
        interfaceCtx->lifeSizeChange += 1;
        if ((s32)interfaceCtx->lifeSizeChange >= 0xA) {
            interfaceCtx->lifeSizeChange = 0xA;
            interfaceCtx->lifeSizeChangeDirection = 1;
        }
    }
}

bool LifeMeter_IsCritical(void) {
    s16 criticalThreshold;
    if (gSaveContext.healthCapacity <= 0x50) {
        criticalThreshold = 0x10;
    } else if (gSaveContext.healthCapacity <= 0xA0) {
        criticalThreshold = 0x18;
    } else if (gSaveContext.healthCapacity <= 0xF0) {
        criticalThreshold = 0x20;
    } else {
        criticalThreshold = 0x2C;
    }

    if ((criticalThreshold >= gSaveContext.health) && (gSaveContext.health > 0)) {
        return 1;
    }
    return 0;
}
